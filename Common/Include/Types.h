/*
-------------------------------------------------------------------------------
    General Purpose Utility Library, should be kept dependency free.
    Unless the dependency can be compiled along with this library.

    Copyright (c) 2009-2010 Charlie C.
-------------------------------------------------------------------------------
  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#ifndef _Types_h_
#define _Types_h_

#include "Defs.h"

#define _UT_CACHE_LIMIT 999


template <typename T> INL void    utSwap(T &a, T &b)                              { T t(a); a = b; b = t; }
template <typename T> INL T       utMax(const T &a, const T &b)                   { return a < b ? b : a; }
template <typename T> INL T       utMin(const T &a, const T &b)                   { return a < b ? a : b; }
template <typename T> INL T       utClamp(const T &v, const T &a, const T &b)     { return v < a ? a : v > b ? b : v; }


// List iterator access.
template <typename T>
class utListIterator
{
public:

	typedef typename T::Pointer Iterator;

	typedef typename T::ReferenceType ValueType;
	typedef typename T::ConstReferenceType ConstValueType;


protected:

	mutable Iterator m_iterator;
	mutable Iterator m_cur;


public:

	utListIterator() : m_iterator(0), m_cur(0) {}

	utListIterator(Iterator first) : m_iterator(first), m_cur(first) {}
	utListIterator(T &v) : m_iterator(v.begin()), m_cur(v.begin()) { }
	~utListIterator() {}

	INL bool hasMoreElements(void) const {  return m_cur != 0;  }


	INL void next(void) const
	{
		APP_API_ASSERT(hasMoreElements());
		m_cur = m_cur->getNext();
	}


	INL ValueType getNext(void)
	{
		APP_API_ASSERT(hasMoreElements());

		ValueType ret = m_cur->getLink();
		m_cur = m_cur->getNext();
		return ret;
	}

	INL ConstValueType getNext(void) const
	{
		APP_API_ASSERT(hasMoreElements());

		ValueType ret = m_cur->getLink();
		m_cur = m_cur->getNext();
		return ret;
	}

	INL ValueType      peekNext(void)       { APP_API_ASSERT(hasMoreElements()); return m_cur->getLink(); }
	INL ConstValueType peekNext(void) const { APP_API_ASSERT(hasMoreElements()); return m_cur->getLink(); }

    INL ValueType operator*() { return peekNext(); }
    INL ConstValueType operator*() const { return peekNext(); }
    INL utListIterator<T>& operator++()
    {
        next();
        return *this;
    }

    INL utListIterator<T> operator++ (int)
    {
        utListIterator<T> tmp = *this;
        ++(*this);
        return tmp;
    }

    INL bool_t operator ==(const utListIterator<T>&      other) const { return m_cur == other.m_cur; }
    INL bool_t operator !=(const utListIterator<T>&      other) const { return m_cur != other.m_cur; }
};


template <typename T>
class utListReverseIterator
{
public:

	typedef typename T::Pointer Iterator;
	typedef typename T::ReferenceType ValueType;
	typedef typename T::ConstReferenceType ConstValueType;

protected:

	mutable Iterator    m_iterator;
	mutable Iterator    m_cur;


public:
	utListReverseIterator() : m_iterator(0), m_cur(0) {}

	utListReverseIterator(Iterator last) : m_iterator(last), m_cur(last) {}
	utListReverseIterator(T &v) : m_iterator(v.end()), m_cur(v.end()) {}


	~utListReverseIterator() {}


	INL bool hasMoreElements(void) const { return m_cur != 0; }


	INL void next(void) const
	{
		APP_API_ASSERT(hasMoreElements());

		m_cur = m_cur->getPrev();
	}

	INL ValueType getNext(void)
	{
		APP_API_ASSERT(hasMoreElements());

		ValueType ret = m_cur->getLink();
		m_cur = m_cur->getPrev();
		return ret;
	}

	INL ConstValueType getNext(void) const
	{
		APP_API_ASSERT(hasMoreElements());

		ValueType ret = m_cur->getLink();
		m_cur = m_cur->getPrev();
		return ret;
	}

	INL ValueType      peekNext(void)        { APP_API_ASSERT(hasMoreElements()); return m_cur->getLink(); }
	INL ConstValueType peekNext(void) const  { APP_API_ASSERT(hasMoreElements()); return m_cur->getLink(); }

    INL ValueType operator*() { return peekNext(); }
    INL ConstValueType operator*() const { return peekNext(); }

    INL utListReverseIterator<T> & operator++()
    {
        next();
        return *this;
    }

    INL utListReverseIterator<T>& operator++ (int)
    {
        utListReverseIterator<T> tmp = *this;
        ++(*this);
        return tmp;
    }
};

template <typename T>
class utListClass
{
public:
	typedef T             *ValueType;
	typedef const T       *ConstValueType;
	typedef T             *Pointer;
	typedef T             *ReferenceType;
	typedef const T       *ConstReferenceType;

	typedef utListIterator<utListClass<T> >              Iterator;
	typedef utListReverseIterator<utListClass<T> >       ReverseIterator;

	// Const access
	typedef const utListIterator<utListClass<T> >        ConstIterator;
	typedef const utListReverseIterator<utListClass<T> > ConstReverseIterator;

	class Link
	{
	protected:
		T *m_next;
		T *m_prev;
		friend class utListClass;

	public:

		Link() : m_next(0), m_prev(0) {}
		~Link() {}

		INL T *getNext(void) {return m_next;}
		INL T *getPrev(void) {return m_prev;}
		INL T *getLink(void) { return (T *)this; }
	};


public:

	utListClass() : m_first(0), m_last(0), m_size(0) {}

	~utListClass() { clear(); }

	void clear(void)
	{
		m_first = m_last = 0;
		m_size = 0;
	}

	void push_back(ValueType v)
	{
		v->m_prev = m_last;
		if (m_last) m_last->m_next = v;
		if (!m_first) m_first = v;
		m_last = v;
		m_size ++;
	}

	void push_front(ValueType v)
	{
		v->m_next = m_first;
		if (m_first) m_first->m_prev = v;
		if (!m_last) m_last = v;
		m_first = v;
		m_size ++;
	}

	void insert(ValueType from, ValueType v)
	{
		m_size ++;
		if (!m_first)
		{
			m_first = m_last = v;
			return;
		}

		if (from == 0)
		{
			// add to back
			v->m_prev = m_last;
			if (m_last) m_last->m_next = v;
			if (!m_first) m_first = v;
			m_last = v;
			return;
		}

		if (m_last == from) m_last = v;

		v->m_next = from->m_next;
		from->m_next = v;
		if (v->m_next) v->m_next->m_prev = v;
		v->m_prev = from;
	}

	ValueType find(ValueType v)
	{
		ValueType node = m_first;
		while (node)
		{
			if (node == v) return node;
			node = node->m_next;
		}
		return 0;
	}

	ValueType at(uint_t index)
	{
		APP_API_ASSERT(index < m_size);
		size_t i = 0;
		ValueType node = m_first;
		while (node)
		{
			if (i == index) break;
			node = node->m_next;
			i++;
		}
		APP_API_ASSERT(node);
		return node;
	}

	ConstValueType at(size_t index) const
	{
		APP_API_ASSERT(index < m_size);
		size_t i = 0;
		ValueType node = m_first;
		while (node)
		{
			if (i == index) break;
			node = node->m_next;
			i++;
		}
		APP_API_ASSERT(node);
		return node;
	}

	ValueType erase(ValueType v)
	{
		if (!v || m_size == 0)
			return 0;
		if (v->m_next) v->m_next->m_prev = v->m_prev;
		if (v->m_prev) v->m_prev->m_next = v->m_next;
		if (m_last == v) m_last = v->m_prev;
		if (m_first == v) m_first = v->m_next;
		m_size -= 1;
		return v;
	}

	INL ValueType pop_back(void)          { return erase(end()); }
	INL ValueType pop_front(void)         { return erase(begin()); }

	INL bool empty(void) const            { return m_size == 0; }
	INL size_t size(void)const            { return m_size; }

	INL ValueType begin(void)             { APP_API_ASSERT(m_first); return m_first; }
	INL ValueType end(void)               { APP_API_ASSERT(m_last); return m_last; }
	INL ConstValueType begin(void) const  { APP_API_ASSERT(m_first); return m_first; }
	INL ConstValueType end(void) const    { APP_API_ASSERT(m_last); return m_last; }


	INL Iterator              iterator(void)               { return m_first ? Iterator(m_first) : Iterator(); }
	INL ReverseIterator       reverseIterator(void)        { return m_last ? ReverseIterator(m_last) : ReverseIterator(); }
	INL ConstIterator         iterator(void) const         { return m_first ? ConstIterator(m_first) : ConstIterator(); }
	INL ConstReverseIterator  reverseIterator(void) const  { return m_last ? ConstReverseIterator(m_last) : ConstReverseIterator(); }


protected:

	T *m_first;
	T *m_last;
	size_t m_size;
};

template <typename T>
class utList
{
public:

	class Link
	{
	protected:
		Link     *next;
		Link     *prev;
		friend class utList;

	public:

		Link() : next(0), prev(0) {}
		Link(const T &v) : next(0), prev(0), link(v) {}


		INL Link  *getNext(void)  {return next;}
		INL Link  *getPrev(void)  {return prev;}
		INL T     &getLink(void)  {return link;}
		T link;
	};

	typedef Link              *Pointer;
	typedef const Link        *ConstPointer;
	typedef T                  ValueType;
	typedef const T            ConstValueType;
	typedef T                 &ReferenceType;
	typedef const T           &ConstReferenceType;


	typedef utListIterator<utList<T> >        Iterator;
	typedef utListReverseIterator<utList<T> > ReverseIterator;
	typedef const utListIterator<utList<T> >  ConstIterator;
	typedef const utListIterator<utList<T> >  ConstReverseIterator;


public:
	utList() : m_first(0), m_last(0), m_size(0) {}
	~utList() { clear(); }

	void clear(void)
	{
		Link *node = m_first;
		while (node)
		{
			Link *temp = node;
			node = node->next;
			delete temp;
		}
		m_first = m_last = 0;
		m_size = 0;
	}

	INL void push_back(const T &v)
	{
		Link *link = new Link(v);
		link->prev = m_last;
		if (m_last) m_last->next = link;
		if (!m_first) m_first = link;
		m_last = link;
		m_size ++;
	}

	INL void push_front(const T &v)
	{
		Link *link = new Link(v);
		link->next = m_first;
		if (m_first) m_first->prev = link;
		if (!m_last) m_last = link;
		m_first = link;
		m_size ++;
	}

	Pointer find(const T &v)
	{
		Link *node = m_first;
		while (node)
		{
			if (node->link == v) return node;
			node = node->next;
		}
		return 0;
	}

	ReferenceType at(size_t index)
	{
		APP_API_ASSERT(index < m_size);
		size_t i = 0;
		Link *node = m_first;
		while (node)
		{
			if (i == index) break;
			node = node->next;
			i++;
		}
		APP_API_ASSERT(node);
		return node->link;
	}

	ConstReferenceType at(size_t index) const
	{
		APP_API_ASSERT(index < m_size);
		size_t i = 0;
		Link *node = m_first;
		while (node)
		{
			if (i == index) break;
			node = node->next;
			i++;
		}
		APP_API_ASSERT(node);
		return node->link;
	}

	Pointer link_at(size_t index)
	{
		size_t i = 0;
		Link *node = m_first;
		while (node)
		{
			if (i == index) return node;
			node = node->next;
			i++;
		}
		return 0;
	}

	void erase(Pointer link)
	{
		if (!link || m_size == 0)
			return;
		if (link->next) link->next->prev = link->prev;
		if (link->prev) link->prev->next = link->next;
		if (m_last == link) m_last = link->prev;
		if (m_first == link) m_first = link->next;

		m_size -= 1;
		delete link;
		if (m_size == 0)
			clear();
	}

	void erase(const T &v)
	{
		Pointer fnd = find(v);
		if (fnd)
			erase(fnd);
	}
    
    Iterator erase(ConstIterator where)
    {
        erase(where.getNext());

        return Iterator(where);
    }

	void sort(bool (*cmp)(const T &a, const T &b))
	{
		size_t i, n=m_size;
		Link *a;
		bool swapped = false;
		if (n < 2 || !cmp)
			return;
		do
		{
			a = m_first;
			for (i=0; a && a->next && i<n-1; i++, a = a->next)
			{
				if (cmp(a->link, a->next->link))
				{
					swap(a, a->next);
					swapped = true;
				}
			}
			n-=1;
		}
		while (swapped && n != UT_NPOS);
	}

	INL void pop_back(void)       { erase(end()); }
	INL void pop_front(void)      { erase(begin()); }


	INL bool empty(void) const    { return m_size == 0; }
	INL size_t size(void)const    { return m_size; }

	/*INL Pointer begin(void)               { return m_first; }
	INL Pointer end(void)                 { return m_last; }
	INL ConstPointer begin(void)const     { return m_first; }
	INL ConstPointer end(void)const       { return m_last; }*/

    INL Iterator      begin()
    {
        return Iterator(m_first); 
    }

    INL Iterator      end()
    {
        return Iterator();
    }

    INL ConstIterator      begin() const
    {
        return ConstIterator(m_first); 
    }

    INL ConstIterator      end() const
    {
        return ConstIterator();
    }

	INL ReferenceType front(void)         { APP_API_ASSERT(m_first); return m_first->link; }
	INL ReferenceType back(void)          { APP_API_ASSERT(m_last); return m_last->link; }

    INL ConstReferenceType front(void)   const      { APP_API_ASSERT(m_first); return m_first->link; }
    INL ConstReferenceType back(void)    const      { APP_API_ASSERT(m_last); return m_last->link; }

	INL Iterator              iterator(void)               { return m_first ? Iterator(m_first) : Iterator(); }
	INL ReverseIterator       reverseIterator(void)        { return m_last ? ReverseIterator(m_last) : ReverseIterator(); }
	INL ConstIterator         iterator(void) const         { return m_first ? ConstIterator(m_first) : ConstIterator(); }
	INL ConstReverseIterator  reverseIterator(void) const  { return m_last ? ConstReverseIterator(m_last) : ConstReverseIterator(); }

protected:

	Link     *m_first;
	Link     *m_last;
	size_t    m_size;


	void swap(Link *a, Link *b)
	{
		ValueType v(a->link);
		a->link = b->link;
		b->link = v;
	}
};

template <typename T>
class utArrayIterator
{
public:

	typedef typename T::Pointer Iterator;

	// T::ValueType as reference
	typedef typename T::ReferenceType      ValueType;
	typedef typename T::ConstReferenceType ConstValueType;


protected:

	mutable Iterator   m_iterator;
	mutable size_t     m_cur;
	mutable size_t     m_capacity;


public:


	utArrayIterator() : m_iterator(0), m_cur(0), m_capacity(0) {}
	utArrayIterator(Iterator begin, size_t size) : m_iterator(begin), m_cur(0), m_capacity(size) {}
	utArrayIterator(T &v) : m_iterator(v.ptr()), m_cur(0), m_capacity(v.size()) { }

	~utArrayIterator() {}

	INL bool           hasMoreElements(void) const { return m_iterator && m_cur < m_capacity; }
	INL ValueType      getNext(void)               { APP_API_ASSERT(hasMoreElements()); return m_iterator[m_cur++];  }
	INL ConstValueType getNext(void) const         { APP_API_ASSERT(hasMoreElements()); return m_iterator[m_cur++];  }
	INL void           next(void) const            { APP_API_ASSERT(hasMoreElements()); ++m_cur; }
	INL ValueType      peekNext(void)              { APP_API_ASSERT(hasMoreElements()); return m_iterator[m_cur]; }
	INL ConstValueType peekNext(void) const        { APP_API_ASSERT(hasMoreElements()); return m_iterator[m_cur]; }

};

template <typename T>
class utArray
{
public:
	typedef T           *Pointer;
	typedef const T     *ConstPointer;

	typedef T            ValueType;
	typedef const T      ConstValueType;

	typedef T           &ReferenceType;
	typedef const T     &ConstReferenceType;

	typedef utArrayIterator<utArray<T> >       Iterator;
	typedef const utArrayIterator<utArray<T> > ConstIterator;

public:
	utArray() : m_size(0), m_capacity(0), m_data(0), m_cache(0)  {}

	utArray(const utArray<T>& o)
		: m_size(o.size()), m_capacity(0), m_data(0), m_cache(0)
	{
		reserve(m_size);
		copy(m_data, o.m_data, m_size);
	}

	~utArray() { clear(); }

	void clear(bool useCache=false)
	{
		if (!useCache)
		{
			if (m_data)
				delete []m_data;
			m_data = 0;
			m_capacity = 0;
			m_size = 0;
			m_cache = 0;
		}
		else
		{
			++m_cache;
			if (m_cache > _UT_CACHE_LIMIT )
				clear(false);
			else m_size = 0;
		}
	}

	size_t find(const T &v)
	{
		for (size_t i = 0; i < m_size; i++)
		{
			if (m_data[i] == v)
				return i;
		}
		return UT_NPOS;
	}

	INL void push_back(const T &v)
	{
		if (m_size == m_capacity)
			reserve(m_size == 0 ? 8 : m_size * 2);

		m_data[m_size] = v;
		m_size++;
	}

	INL void pop_back(void)
	{
		m_size--;
		m_data[m_size].~T();
	}


	void erase(const T &v)
	{
		erase(find(v));
	}

	void erase(size_t pos)
	{
		if (m_size > 0)
		{
			if (pos != UT_NPOS)
			{
				swap(pos, m_size-1);
				m_size--;
				m_data[m_size].~T();
			}
		}
	}

	void resize(size_t nr)
	{
		if (nr < m_size)
		{
			for (size_t i = m_size; i < nr; i++)
				m_data[i].~T();
		}
		else
		{
			if (nr > m_size)
				reserve(nr);
		}
		m_size = nr;
	}

	void resize(size_t nr, const T &fill)
	{
		if (nr < m_size)
		{
			for (size_t i = m_size; i < nr; i++)
				m_data[i].~T();
		}
		else
		{
			if (nr > m_size)
				reserve(nr);
			for (size_t i = m_size; i < nr; i++)
				m_data[i] = fill;

		}
		m_size = nr;
	}

	void reserve(size_t nr)
	{

		if (m_capacity < nr)
		{
			T *p = new T[nr];
			if (m_data != 0)
			{
				copy(p, m_data, m_size);
				delete []m_data;
			}
			m_data = p;
			m_capacity = nr;
		}
	}

	void sort(bool (*cmp)(const T &a, const T &b))
	{
		size_t i, n=m_size;
		bool swapped = false;
		if (n < 2 || !cmp)
			return;
		do
		{
			if (n-1 == UT_NPOS)
				break;
			for (i=0; /*m_data[i] && m_data[i+1] && */i<(n-1); i++)
			{
				if (cmp(m_data[i], m_data[i+1]))
				{
					swap(i, i+1);
					swapped = true;
				}
			}
			n-=1;
		}
		while (swapped && n != UT_NPOS);
	}

	INL T &operator[](size_t idx)             { APP_API_ASSERT(idx >= 0 && idx < m_capacity); return m_data[idx]; }
	INL const T &operator[](size_t idx) const { APP_API_ASSERT(idx >= 0 && idx < m_capacity); return m_data[idx]; }
	INL T &at(size_t idx)                     { APP_API_ASSERT(idx >= 0 && idx < m_capacity); return m_data[idx]; }
	INL const T &at(size_t idx) const         { APP_API_ASSERT(idx >= 0 && idx < m_capacity); return m_data[idx]; }
	INL T &front(void)                        { APP_API_ASSERT(m_size > 0); return m_data[0]; }
	INL T &back(void)                         { APP_API_ASSERT(m_size > 0); return m_data[m_size-1]; }


	INL ConstPointer ptr(void) const          { return m_data; }
	INL Pointer      ptr(void)                { return m_data; }
	INL bool         valid(void) const        { return m_data != 0;}

	INL size_t capacity(void) const           { return m_capacity; }
	INL size_t size(void) const               { return m_size; }
	INL bool empty(void) const                { return m_size == 0;}


	INL Iterator       iterator(void)       { return m_data && m_size > 0 ? Iterator(m_data, m_size) : Iterator(); }
	INL ConstIterator  iterator(void) const { return m_data && m_size > 0 ? ConstIterator(m_data, m_size) : ConstIterator(); }

	utArray<T> &operator= (const utArray<T> &rhs)
	{
		if (this != &rhs)
		{
			clear();
			size_t os = rhs.size();
			if (os > 0)
			{
				resize(os);
				copy(m_data, rhs.m_data, os);
			}
		}

		return *this;
	}

	INL void copy(Pointer dst, ConstPointer src, size_t size)
	{
		APP_API_ASSERT(size <= m_size);
		for (size_t i = 0; i < size; i++) dst[i] = src[i];
	}

protected:

	void swap(size_t a, size_t b)
	{
		ValueType t= m_data[a];
		m_data[a] = m_data[b];
		m_data[b] = t;
	}

	size_t      m_size;
	size_t      m_capacity;
	Pointer     m_data;
	int         m_cache;
};

template <typename T>
class utStackIterator
{
public:
	typedef typename T::Pointer            Iterator;
	typedef typename T::ReferenceType      ValueType;
	typedef typename T::ConstReferenceType ConstValueType;

protected:

	mutable Iterator m_iterator;
	mutable size_t   m_top;
	const size_t     m_capacity;

public:
	utStackIterator() : m_iterator(0), m_top(0), m_capacity(0)  {}

	utStackIterator(Iterator begin, size_t top) : m_iterator(begin), m_top(top), m_capacity(top) {}
	utStackIterator(T &v) : m_iterator(v.begin()), m_top(v.itop()), m_capacity(v.itop()) {}

	~utStackIterator() {}


	INL bool hasMoreElements(void) const { return (m_iterator && m_top != 0 && m_top != UT_NPOS); }


	INL ValueType getNext(void)
	{
		APP_API_ASSERT((m_iterator && (m_top - 1) != UT_NPOS));
		--m_top;
		return m_iterator[m_top];
	}

	INL ConstValueType getNext(void) const
	{
		APP_API_ASSERT((m_iterator && (m_top - 1) != UT_NPOS));
		--m_top;
		return m_iterator[m_top];
	}


	INL void next(void) const
	{
		APP_API_ASSERT((m_iterator && (m_top - 1) != UT_NPOS));
		--m_top;
	}

	INL ValueType peekNext(void)
	{
		APP_API_ASSERT((m_iterator && (m_top - 1) != UT_NPOS));
		return m_iterator[m_top-1];
	}

	INL ConstValueType peekNext(void) const
	{
		APP_API_ASSERT((m_iterator && (m_top - 1) != UT_NPOS));
		return m_iterator[m_top-1];
	}

};

template <typename T>
class utStack
{
public:
	typedef T *Pointer;
	typedef const T *ConstPointer;

	typedef T        ValueType;
	typedef const T  ConstValueType;


	typedef T &ReferenceType;
	typedef const T &ConstReferenceType;


	typedef utStackIterator<utStack<T> >       Iterator;
	typedef const utStackIterator<utStack<T> > ConstIterator;

public:

	utStack() : m_size(0), m_capacity(0), m_top(0), m_stack(0) {}
	utStack(size_t rsp) : m_size(0), m_capacity(0), m_top(0), m_stack(0) { reserve(rsp); }


	utStack(const utStack &o) : m_size(o.m_size), m_capacity(0), m_top(o.m_top), m_stack(0)
	{
		reserve(o.m_size);
		APP_API_ASSERT(m_stack && o.m_stack);
		copy(m_stack, o.m_stack, o.m_size);
	}

	~utStack() { clear(); }

	void clear(void)
	{
		if (m_stack != 0)
		{
			delete []m_stack;
			m_stack = 0;
		}

		m_size = 0;
		m_capacity = 0;
		m_top = 0;
	}


	void push(const T &v)
	{
		APP_API_ASSERT(m_top != UT_NPOS);
		if (m_size == m_capacity)
			reserve(m_size == 0 ? 8 : m_size * 2);
		m_stack[m_top] = v;
		++m_top;
		++m_size;
	}

	INL ReferenceType pop(void)               { APP_API_ASSERT(m_top != 0); --m_size; return m_stack[--m_top]; }
	INL ReferenceType top(void)               { APP_API_ASSERT(m_top != 0); return m_stack[(m_top - 1)]; }
	INL ConstReferenceType top(void) const    { APP_API_ASSERT(m_top != 0); return m_stack[(m_top - 1)]; }

	INL ReferenceType peek(size_t offs)
	{
		APP_API_ASSERT(m_top != 0 && ((m_top - 1) - offs) != UT_NPOS);
		return m_stack[(m_top - 1)-offs];
	}

	INL ConstReferenceType peek(size_t offs) const
	{
		APP_API_ASSERT(m_top != 0 && ((m_top - 1) - offs) != UT_NPOS);
		return m_stack[(m_top - 1)-offs];
	}

	void reserve(size_t nr)
	{
		if (m_capacity < nr)
		{
			T *temp = new T[nr];
			if (m_stack)
			{
				copy(temp, m_stack, m_size);
				delete []m_stack;
			}
			m_stack = temp;
			m_capacity = nr;
		}
	}

	INL size_t capacity(void) const           { return m_capacity; }
	INL size_t size(void) const               { return m_size; }
	INL size_t itop(void) const               { return m_top; }
	INL bool empty(void) const                { return m_size == 0; }
	INL ConstPointer ptr(void) const          { return m_stack; }
	INL Pointer ptr(void)                     { return m_stack; }

	INL Iterator      iterator(void)       { return m_stack && m_size > 0 ? Iterator(m_stack, m_size) : Iterator(); }
	INL ConstIterator iterator(void) const { return m_stack && m_size > 0 ? ConstIterator(m_stack, m_size) : ConstIterator(); }


protected:


	INL void copy(Pointer dest, const Pointer src, size_t nr)
	{
		size_t i;
		for (i = 0; i < nr; i++)
			dest[i] = src[i];
	}

	size_t  m_size;
	size_t  m_capacity;
	size_t  m_top;
	Pointer m_stack;
};

template <typename T>
class utHashTableIterator
{
public:

	typedef typename T::Pointer        Iterator;
	typedef typename T::Entry          &Pair;
	typedef typename T::ConstEntry     &ConstPair;

	typedef typename T::ReferenceKeyType         KeyType;
	typedef typename T::ReferenceValueType       ValueType;
	typedef typename T::ConstReferenceKeyType    ConstKeyType;
	typedef typename T::ConstReferenceValueType  ConstValueType;

protected:

	mutable Iterator m_iterator;
	mutable size_t   m_cur;
	const size_t     m_capacity;


public:
	utHashTableIterator() : m_iterator(0), m_cur(0), m_capacity(0)  {}
	utHashTableIterator(Iterator begin, size_t size) : m_iterator(begin), m_cur(0), m_capacity(size) { }
	utHashTableIterator(T &v) : m_iterator(v.ptr()), m_cur(0), m_capacity(v.size()) {}

	~utHashTableIterator() {}

	INL bool      hasMoreElements(void) const  { return (m_iterator && m_cur < m_capacity); }
	INL Pair      getNext(void)                { APP_API_ASSERT(hasMoreElements()); return m_iterator[m_cur++];}
	INL ConstPair getNext(void) const          { APP_API_ASSERT(hasMoreElements()); return m_iterator[m_cur++];}
	INL void      next(void) const             { APP_API_ASSERT(hasMoreElements()); ++m_cur; }


	INL Pair      peekNext(void)               { APP_API_ASSERT(hasMoreElements()); return m_iterator[m_cur]; }
	INL KeyType   peekNextKey(void)            { APP_API_ASSERT(hasMoreElements()); return m_iterator[m_cur].first;}
	INL ValueType peekNextValue(void)          { APP_API_ASSERT(hasMoreElements()); return m_iterator[m_cur].second; }

	INL ConstPair      peekNext(void)  const     { APP_API_ASSERT(hasMoreElements()); return m_iterator[m_cur]; }
	INL ConstKeyType   peekNextKey(void) const   { APP_API_ASSERT(hasMoreElements()); return m_iterator[m_cur].first;}
	INL ConstValueType peekNextValue(void) const { APP_API_ASSERT(hasMoreElements()); return m_iterator[m_cur].second; }
};



// magic numbers from http://www.isthe.com/chongo/tech/comp/fnv/
#define _UT_INITIAL_FNV  0x9E3779B1
#define _UT_INITIAL_FNV2 0x9E3779B9
#define _UT_MULTIPLE_FNV 0x1000193
#define _UT_TWHASH(key)         \
        key += ~(key << 15);    \
        key ^=  (key >> 10);    \
        key +=  (key << 3);     \
        key ^=  (key >> 6);     \
        key += ~(key << 11);    \
        key ^=  (key >> 16);

class utCharHashKey
{
protected:
	char *m_key;
	mutable UThash m_hash;

public:
	utCharHashKey() : m_key(0), m_hash(UT_NPOS) {}
	utCharHashKey(char *k) : m_key(k), m_hash(UT_NPOS) {hash();}
	utCharHashKey(const char *k) : m_key(const_cast<char *>(k)), m_hash(UT_NPOS) {}

	// Copy constructor
	utCharHashKey(const utCharHashKey &k) : m_key(k.m_key), m_hash(k.m_hash) {}

	INL const char *key(void) const {return m_key;}

	UThash hash(void) const
	{
		if (!m_key) return UT_NPOS;

		// use cached hash
		if (m_hash != UT_NPOS) return m_hash;

		// Fowler / Noll / Vo (FNV) Hash
		m_hash = (UThash)_UT_INITIAL_FNV;
		for (int i = 0; m_key[i]; i++)
		{
			m_hash = m_hash ^(m_key[i]);    // xor  the low 8 bits
			m_hash = m_hash * _UT_MULTIPLE_FNV;  // multiply by the magic number
		}
		return m_hash;
	}

	INL bool operator== (const utCharHashKey &v) const    {return hash() == v.hash();}
	INL bool operator!= (const utCharHashKey &v) const    {return hash() != v.hash();}
	INL bool operator== (const UThash &v) const           {return hash() == v;}
	INL bool operator!= (const UThash &v) const           {return hash() != v;}
};

class utIntHashKey
{
protected:
	int m_key;
public:
	utIntHashKey() : m_key(0) {}
	utIntHashKey(int k) : m_key(k) {}
	utIntHashKey(const utIntHashKey &k) : m_key(k.m_key) {}

	INL int key(void)  const  { return m_key; }
	INL UThash  hash(void) const  { return static_cast<UThash>(m_key) * _UT_INITIAL_FNV; }

	INL bool operator== (const utIntHashKey &v) const {return hash() == v.hash();}
	INL bool operator!= (const utIntHashKey &v) const {return hash() != v.hash();}
	INL bool operator== (const UThash &v) const       {return hash() == v;}
	INL bool operator!= (const UThash &v) const       {return hash() != v;}
};

class utPointerHashKey
{
protected:
	void *m_key;

public:
	utPointerHashKey() : m_key(0) {}
	utPointerHashKey(void *k) : m_key(k) {}
	utPointerHashKey(const utPointerHashKey &k) : m_key(k.m_key) {}

	INL void          *key(void)       {return m_key;}
	INL const void    *key(void) const {return m_key;}


	INL UThash hash(void) const
	{
		UThash key = static_cast<UThash>(reinterpret_cast<UTuintPtr>(m_key));
		_UT_TWHASH(key);
		return key;
	}


	INL bool operator== (const utPointerHashKey &v) const {return hash() == v.hash();}
	INL bool operator!= (const utPointerHashKey &v) const {return hash() != v.hash();}
	INL bool operator== (const UThash &v) const           {return hash() == v;}
	INL bool operator!= (const UThash &v) const           {return hash() != v;}
};

template<typename Key, typename Value>
struct utHashEntry
{
	Key    first;
	Value  second;

	utHashEntry() {}
	utHashEntry(const Key &k, const Value &v) : first(k), second(v) {}
	INL const utHashEntry &operator=(const utHashEntry &rhs)
	{
		first = rhs.first;
		second = rhs.second;
		return *this;
	}
	INL bool operator==(const utHashEntry &rhs) const
	{
		return first == rhs.first && second == rhs.second;
	}
};

#define _UT_UTHASHTABLE_HASH(key)   ((key.hash() & (m_capacity - 1)))
#define _UT_UTHASHTABLE_HKHASH(key) ((hk & (m_capacity - 1)))
// Initial table size
#define _UT_UTHASHTABLE_INIT     32
#define _UT_UTHASHTABLE_EXPANSE  (m_size * 2)

// Force power of two table size.
#define _UT_UTHASHTABLE_FORCE_POW2 1
#define _UT_UTHASHTABLE_STAT       0
#define _UT_UTHASHTABLE_STAT_ALLOC 0


#if _UT_UTHASHTABLE_FORCE_POW2 == 1
#define _UT_UTHASHTABLE_POW2(x) \
	--x; x |= x >> 16; x |= x >> 8; x |= x >> 4; \
	x |= x >> 2; x |= x >> 1; ++x;

#define _UT_UTHASHTABLE_IS_POW2(x) (x && !((x-1) & x))
#endif


#if _UT_UTHASHTABLE_STAT == 1
# include <stdio.h>
# include <typeinfo>
#endif


template < typename Key, typename Value>
class utHashTable
{
public:
	typedef utHashEntry<Key, Value>        Entry;
	typedef const utHashEntry<Key, Value>  ConstEntry;

	typedef Entry  *EntryArray;
	typedef size_t *IndexArray;


	typedef Key            KeyType;
	typedef Value          ValueType;

	typedef const Key      ConstKeyType;
	typedef const Value    ConstValueType;

	typedef Value          &ReferenceValueType;
	typedef const Value    &ConstReferenceValueType;

	typedef Key            &ReferenceKeyType;
	typedef const Key      &ConstReferenceKeyType;

	typedef EntryArray Pointer;
	typedef const Entry *ConstPointer;


	typedef utHashTableIterator<utHashTable<Key, Value> > Iterator;
	typedef const utHashTableIterator<utHashTable<Key, Value> > ConstIterator;


public:

	utHashTable()
		:    m_size(0), m_capacity(0), m_lastPos(UT_NPOS),
		     m_iptr(0), m_nptr(0), m_bptr(0), m_cache(0)
	{
	}

	utHashTable(size_t capacity)
		:    m_size(0), m_capacity(0), m_lastPos(UT_NPOS),
		     m_iptr(0), m_nptr(0), m_bptr(0), m_cache(0)
	{
	}

	utHashTable(const utHashTable &rhs)
		:    m_size(0), m_capacity(0), m_lastPos(UT_NPOS),
		     m_iptr(0), m_nptr(0), m_bptr(0), m_cache(0)
	{
		doCopy(rhs);
	}

	~utHashTable() { clear(); }

	utHashTable<Key, Value> &operator = (const utHashTable<Key, Value> &rhs)
	{
		if (this != &rhs)
			doCopy(rhs);
		return *this;
	}

	void clear(bool useCache = false)
	{
		if (!useCache)
		{
			m_size = m_capacity = 0;
			m_lastKey = UT_NPOS;
			m_lastPos = UT_NPOS;
			m_cache = 0;

			delete [] m_bptr;
			delete [] m_iptr;
			delete [] m_nptr;
			m_bptr = 0; m_iptr = 0; m_nptr = 0;
		}
		else
		{
			++m_cache;
			if (m_cache > _UT_CACHE_LIMIT)
				clear(false);
			else
			{
				m_size = 0;
				m_lastKey = UT_NPOS;
				m_lastPos = UT_NPOS;


				size_t i;

				// Must zero
				for (i=0; i<m_capacity; ++i)
				{
					m_iptr[i] = UT_NPOS;
					m_nptr[i] = UT_NPOS;
				}
			}
		}

	}
	Value              &at(size_t i)                    { APP_API_ASSERT(m_bptr && i >= 0 && i < m_size); return m_bptr[i].second; }
	Value              &operator [](size_t i)           { APP_API_ASSERT(m_bptr && i >= 0 && i < m_size); return m_bptr[i].second; }
	const Value        &at(size_t i)const               { APP_API_ASSERT(m_bptr && i >= 0 && i < m_size); return m_bptr[i].second; }
	const Value        &operator [](size_t i) const     { APP_API_ASSERT(m_bptr && i >= 0 && i < m_size); return m_bptr[i].second; }
	Key                &keyAt(size_t i)                 { APP_API_ASSERT(m_bptr && i >= 0 && i < m_size); return m_bptr[i].first; }
	const Key          &keyAt(size_t i)const            { APP_API_ASSERT(m_bptr && i >= 0 && i < m_size); return m_bptr[i].first; }


	// Find and cache key
	Value* get(const Key &key)
	{
		if (!m_bptr || m_size == 0)
			return (Value*)0;


		UThash hr = key.hash();

		if (m_lastKey != hr)
		{
			size_t i = find(key);
			if (i == UT_NPOS) return (Value*)0;


			APP_API_ASSERT(i >=0 && i < m_size);

			m_lastKey = hr;
			m_lastPos = i;
		}

		return &m_bptr[m_lastPos].second;
	}


	Value*         operator [](const Key &key)       { return get(key); }
	const Value*   operator [](const Key &key) const { return get(key); }

	size_t find(const Key &key) const
	{
		if (m_capacity == 0 || m_capacity == UT_NPOS || m_size == 0)
			return UT_NPOS;

		size_t hk = key.hash();

		// Short cut.
		if (m_lastPos != UT_NPOS && m_lastKey == hk)
			return m_lastPos;


		UThash hr = _UT_UTHASHTABLE_HKHASH(hk);

		APP_API_ASSERT(m_bptr && m_iptr && m_nptr);

		size_t fh = m_iptr[hr];
		while (fh != UT_NPOS && (key != m_bptr[fh].first))
			fh = m_nptr[fh];


		if (fh != UT_NPOS)
		{
			m_lastKey = hk;
			m_lastPos = fh;

			APP_API_ASSERT(fh >= 0  && fh < m_size);
		}
		return fh;
	}



	void erase(const Key &key) {remove(key);}

	void remove(const Key &key)
	{
		UThash hash, lhash;
		size_t index, pindex, findex;

		findex = find(key);
		if (findex == UT_NPOS || m_capacity == 0 || m_size == 0)
			return;

		m_lastKey = UT_NPOS;
		m_lastPos = UT_NPOS;
		APP_API_ASSERT(m_bptr && m_iptr && m_nptr);


		hash = _UT_UTHASHTABLE_HASH(key);

		index  = m_iptr[hash];
		pindex = UT_NPOS;
		while (index != findex)
		{
			pindex = index;
			index = m_nptr[index];
		}

		if (pindex != UT_NPOS)
		{
			APP_API_ASSERT(m_nptr[pindex] == findex);
			m_nptr[pindex] = m_nptr[findex];
		}
		else
			m_iptr[hash] = m_nptr[findex];

		size_t lindex = m_size - 1;
		if (lindex == findex)
		{
			--m_size;
			m_bptr[m_size].~Entry();
			return;
		}

		lhash = _UT_UTHASHTABLE_HASH(m_bptr[lindex].first);
		index  = m_iptr[lhash];
		pindex = UT_NPOS;
		while (index != lindex)
		{
			pindex = index;
			index = m_nptr[index];
		}

		if (pindex != UT_NPOS)
		{
			APP_API_ASSERT(m_nptr[pindex] == lindex);
			m_nptr[pindex] = m_nptr[lindex];
		}
		else
			m_iptr[lhash] = m_nptr[lindex];

		m_bptr[findex] = m_bptr[lindex];
		m_nptr[findex] = m_iptr[lhash];
		m_iptr[lhash] = findex;

		--m_size;
		m_bptr[m_size].~Entry();
		return;
	}

	bool insert(const Key &key, const Value &val)
	{
		if (find(key) != UT_NPOS)
			return false;

		if (m_size == m_capacity)
			reserve(m_size == 0 ? _UT_UTHASHTABLE_INIT : _UT_UTHASHTABLE_EXPANSE);

		const UThash hr = _UT_UTHASHTABLE_HASH(key);

		APP_API_ASSERT(m_bptr && m_iptr && m_nptr);
		m_bptr[m_size] = Entry(key, val);
		m_nptr[m_size] = m_iptr[hr];
		m_iptr[hr] = m_size;

		++m_size;
		return true;
	}


	INL Pointer ptr(void)             { return m_bptr; }
	INL ConstPointer ptr(void) const  { return m_bptr; }
	INL bool valid(void) const        { return m_bptr != 0;}


	INL size_t size(void) const       { return m_size; }
	INL size_t capacity(void) const   { return capacity; }
	INL bool empty(void) const        { return m_size == 0; }


	Iterator        iterator(void)       { return m_bptr && m_size > 0 ? Iterator(m_bptr, m_size) : Iterator(); }
	ConstIterator   iterator(void) const { return m_bptr && m_size > 0 ? ConstIterator(m_bptr, m_size) : ConstIterator(); }


	void reserve(size_t nr)
	{
		if (m_capacity < nr && nr != UT_NPOS)
			rehash(nr);
	}

#if _UT_UTHASHTABLE_STAT == 1

	void report(void) const
	{
		if (m_capacity == 0 || m_capacity == UT_NPOS || m_size == 0)
			return;

		APP_API_ASSERT(m_bptr && m_iptr && m_nptr);


		size_t min_col= m_size, max_col = 0;
		size_t i, tot=0, avg = 0;
		for (i=0; i<m_size; ++i)
		{
			Key &key = m_bptr[i].first;

			UThash hr = _UT_UTHASHTABLE_HASH(key);

			size_t nr = 0;

			size_t fh = m_iptr[hr];
			while (fh != UT_NPOS && (key != m_bptr[fh].first))
			{
				fh = m_nptr[fh];
				nr++;
			}

			if (nr < min_col)
				min_col = nr;
			if (nr > max_col)
				max_col = nr;

			tot += nr;
			avg += nr ? 1 : 0;
		}

#if _UT_UTHASHTABLE_FORCE_POW2 == 1
		printf("Results using forced power of 2 expansion.\n\n");
#else
		printf("Results using unaltered expansion.\n\n");
#endif
		printf("\tTotal number of collisions %i for a table of size %i.\n\t\tusing (%s)\n", tot, m_size, typeid(Key).name());
		printf("\tThe minimum number of collisions per key: %i\n", min_col);
		printf("\tThe maximum number of collisions per key: %i\n", max_col);

		int favr = (int)(100.f * ((float)avg / (float)m_size));
		printf("\tThe average number of key collisions: %i\n\n", favr);

		if (tot == 0)
			printf("\nCongratulations lookup is 100%% linear!\n\n");
		else if (favr >  35)
			printf("\nImprove your hash function!\n\n");
	}
#endif



private:

	void doCopy(const utHashTable<Key, Value> &rhs)
	{
		if (rhs.empty())
			clear();
		else if (rhs.valid())
		{
			reserve(rhs.m_capacity);

			size_t i, b;
			m_size     = rhs.m_size;
			m_capacity = rhs.m_capacity;

			b = m_size > 0 ? m_size - 1 : 0;

			// Zero i & n (from end of buffer)
			for (i=b; i<m_capacity; ++i)
				m_nptr[i] = m_iptr[i] = UT_NPOS;

			for (i=0; i<m_size; ++i)
			{
				m_bptr[i] = rhs.m_bptr[i];
				m_iptr[i] = rhs.m_iptr[i];
				m_nptr[i] = rhs.m_nptr[i];
			}
		}

	}

	template<typename ArrayType>
	void reserveType(ArrayType **old, size_t nr, bool cpy=false)
	{
		size_t i;
		ArrayType *nar = new ArrayType[nr];
		if ((*old)!= 0)
		{
			if (cpy)
			{
				const ArrayType *oar = (*old);
				for (i = 0; i < m_size; i++) nar[i] = oar[i];
			}
			delete [](*old);
		}
		(*old) = nar;
	}


	void rehash(size_t nr)
	{
#if _UT_UTHASHTABLE_FORCE_POW2

		if (!_UT_UTHASHTABLE_IS_POW2(nr))
		{
			_UT_UTHASHTABLE_POW2(nr);
		}

#if _UT_UTHASHTABLE_STAT_ALLOC == 1
		printf("Expanding tables: %i\n", nr);
#endif
		APP_API_ASSERT(_UT_UTHASHTABLE_IS_POW2(nr));


#else

#if _UT_UTHASHTABLE_STAT_ALLOC == 1
		printf("Expanding tables: %i\n", nr);
#endif

#endif

		reserveType<Entry>(&m_bptr, nr, true);
		reserveType<size_t>(&m_iptr, nr);
		reserveType<size_t>(&m_nptr, nr);

		m_capacity = nr;
		APP_API_ASSERT(m_bptr && m_iptr && m_nptr);


		size_t i, h;
		for (i=0; i<m_capacity; ++i)
			m_iptr[i] = m_nptr[i] = UT_NPOS;

		for (i = 0; i < m_size; i++)
		{
			h = _UT_UTHASHTABLE_HASH(m_bptr[i].first);
			m_nptr[i] = m_iptr[h];
			m_iptr[h] = i;
		}
	}



	size_t m_size, m_capacity;
	mutable size_t m_lastPos;
	mutable size_t m_lastKey;

	IndexArray m_iptr;
	IndexArray m_nptr;
	EntryArray m_bptr;
	size_t m_cache;
};




INL UThash gkHash(int v)
{
	utIntHashKey hk(v);
	return hk.hash();
}


INL UThash gkHash(const char *v)
{
	utCharHashKey hk(v);
	return hk.hash();
}



INL UThash gkHash(void *v)
{
	utPointerHashKey hk(v);
	return hk.hash();
}

template <typename T>
class utHashSetIterator
{
public:

	typedef typename T::Pointer         Iterator;
	typedef typename T::ValueType       &ValueType;
	typedef typename T::ConstValueType  &ConstValueType;


protected:

	mutable Iterator m_iterator;
	mutable size_t   m_cur;
	const size_t     m_capacity;


public:
	utHashSetIterator() : m_iterator(0), m_cur(0), m_capacity(0)  {}
	utHashSetIterator(Iterator begin, size_t size) : m_iterator(begin), m_cur(0), m_capacity(size) { }
	utHashSetIterator(T &t) : m_iterator(t.ptr()), m_cur(0), m_capacity(t.size()) { }
	~utHashSetIterator() {}

	INL bool             hasMoreElements(void) const  { return (m_iterator && m_cur < m_capacity); }
	INL ValueType        getNext(void)                { APP_API_ASSERT(hasMoreElements()); return m_iterator[m_cur++].second;}
	INL ConstValueType   getNext(void) const          { APP_API_ASSERT(hasMoreElements()); return m_iterator[m_cur++].second;}
	INL void             next(void) const             { APP_API_ASSERT(hasMoreElements()); ++m_cur; }
	INL ValueType        peekNext(void)               { APP_API_ASSERT(hasMoreElements()); return m_iterator[m_cur].second; }
	INL ConstValueType   peekNext(void) const         { APP_API_ASSERT(hasMoreElements()); return m_iterator[m_cur].second; }
};

template<typename T>
class utHashSet
{
public:

	class THashKey
	{
	protected:
		T m_key;
		mutable UThash m_cache;
	public:
		THashKey() : m_key(T()), m_cache(UT_NPOS) {}
		THashKey(const T &k) : m_key(k), m_cache(UT_NPOS) {}
		THashKey(const THashKey &k) : m_key(k.m_key), m_cache(k.m_cache) {}

		INL UThash hash(void) const
		{
			if (m_cache != UT_NPOS) return m_cache;
			m_cache = gkHash(m_key);
			return m_cache;

		}
		INL bool operator== (const THashKey &v) const     {return hash() == v.hash();}
		INL bool operator!= (const THashKey &v) const     {return hash() != v.hash();}
		INL bool operator== (const UThash &v) const       {return hash() == v;}
		INL bool operator!= (const UThash &v) const       {return hash() != v;}
	};


	typedef utHashTable<THashKey, T>               Hash;
	typedef typename Hash::Pointer                 Pointer;
	typedef typename Hash::ConstPointer            ConstPointer;
	typedef typename Hash::ValueType               ValueType;
	typedef typename Hash::ConstValueType          ConstValueType;
	typedef utHashSetIterator<utHashSet<T> >       Iterator;
	typedef const utHashSetIterator<utHashSet<T> > ConstIterator;

public:


	utHashSet() {}
	utHashSet(const utHashSet &oth) : m_table(oth) {}
	~utHashSet() {m_table.clear();}


	void clear(bool useCache=false)
	{
		m_table.clear(useCache);
	}

	bool insert(const T &v)
	{
		return m_table.insert(v, v);
	}

	void erase(const T &v)
	{
		m_table.remove(v);
	}


	size_t find(const T &v) { return m_table.find(v); }


	INL T       &operator[](size_t idx)        { APP_API_ASSERT(idx >= 0 && idx < size()); return m_table.at(idx); }
	INL const T &operator[](size_t idx) const  { APP_API_ASSERT(idx >= 0 && idx < size()); return m_table.at(idx); }
	INL T       &at(size_t idx)                { APP_API_ASSERT(idx >= 0 && idx < size()); return m_table.at(idx); }
	INL const T &at(size_t idx) const          { APP_API_ASSERT(idx >= 0 && idx < size()); return m_table.at(idx); }

	INL size_t size(void)  const              { return m_table.size(); }
	INL bool   empty(void) const              { return m_table.empty();}
	INL Pointer      ptr(void)                { return m_table.ptr();}
	INL ConstPointer ptr(void) const          { return m_table.ptr();}

	INL Iterator       iterator(void)       {return empty() ? Iterator() : Iterator(m_table.ptr(), m_table.size());}
	INL ConstIterator  iterator(void) const
	{
		return empty() ? ConstIterator() :
		       ConstIterator(const_cast<Pointer>(m_table.ptr()), m_table.size());
	}


	utHashSet<T>& operator=(const utHashSet<T>& rhs)
	{
		if (this != &rhs)
			m_table = rhs.m_table;
		return *this;
	}


#if _UT_UTHASHTABLE_STAT == 1
	void report(void) const { m_table.report(); }
#endif

private:

	Hash m_table;

};

// Extended pair
template <class Tx, class Ty>
class FPair: public std::pair<Tx, Ty>
{
public:

	FPair(Tx tx, Ty ty): std::pair<Tx, Ty>(tx, ty) {}

	FPair& operator=(const FPair& oth)
	{
		this->first = oth.first;
		this->second = oth.second;

		return *this;
	}
};

template<class _Ty1,
class _Ty2> inline
	FPair<_Ty1, _Ty2> make_pair(_Ty1 _Val1, _Ty2 _Val2)
{	// return pair composed from arguments
	return (FPair<_Ty1, _Ty2>(_Val1, _Val2));
}

typedef std::string FString;
#    define FArray std::vector
#    define FList utList
#    define FMap std::map
#    define FStack std::stack
#    define FOstream std::ostream

#endif//_utTypes_h_
