#pragma once

#include <thread>
#include <mutex>
#include <functional>
#include <set>
#include <list>
#include <iostream>

namespace Common
{
    //Thread policies

    class  MultiThreadGlobal
    {
    private:

        std::mutex& GetMutex()
        {
            static std::mutex mut;
            return mut;
        }
        bool m_IsLocked;
    public:

        MultiThreadGlobal() : m_IsLocked(false)
        {
        }

        ~MultiThreadGlobal()
        {
            unlock();
        }

        void lock()
        {
            if (GetMutex().try_lock())
                m_IsLocked = true;
            //std::cout << "mutex try_lock failed. be aware." << std::endl;
        }

        void unlock()
        {
            if (m_IsLocked)
                GetMutex().unlock();
            m_IsLocked = false;
        }
    } ;

    class MultiThreadLocal
    {
    private:
        std::mutex m_Mutex;
    public:

        MultiThreadLocal()
        {
        }

        ~MultiThreadLocal()
        {
            unlock();
        }

        void lock()
        {
            m_Mutex.lock();
        }

        void unlock()
        {
            m_Mutex.unlock();
        }
    } ;

    typedef MultiThreadGlobal CurrentThreadPolicy;
    typedef std::lock_guard<CurrentThreadPolicy> LockBlock_t;

    class HasSlots;

    struct ISignal
    {
        virtual void SlotDisconnect(HasSlots * pslot) = 0;
        virtual void SlotDuplicate(const HasSlots* poldslot, HasSlots * pnewslot) = 0;

        virtual ~ISignal()
        {
        }

    } ;
    //////////////////////////////////////////////////////////////////////////

    class HasSlots
    {
    private:
        typedef std::set<ISignal*> Senders_t;
        typedef Senders_t::const_iterator ConstIter;

        Senders_t m_Senders;
        CurrentThreadPolicy m_ThreadPolicy;
    public:

        HasSlots()
        {
        }

        HasSlots(const HasSlots& oth);

        void                    SignalConnect(ISignal* sender);
        void                    SignalDisconnect(ISignal* sender);

        virtual                 ~HasSlots();

        void                    DisconnectAll();
    } ;


    template<class Signature>
    class ConnectionBase
    {
    public:

        virtual ~ConnectionBase()
        {
        }
        virtual HasSlots* GetDest() const = 0;
#define _ALLOCATE_PERFORM( \
        TEMPLATE_LIST, PADDING_LIST, LIST, COMMA, X1, X2, X3, X4) \
        template <LIST(_CLASS_TYPE)> \
        virtual void Perform(LIST(_TYPE_REFREF_ARG)) = 0;

        virtual ConnectionBase<Signature>* Clone() = 0;
        virtual ConnectionBase<Signature>* Duplicate(HasSlots* pnewdest) = 0;
    } ;

    template<typename SlotsContainer>
    class SignalContainer : public ISignal
    {
    private:
    protected:
        typedef SlotsContainer SlotsContainer_t;

        SlotsContainer_t    m_ConnectedSlots;
        typedef typename SlotsContainer_t::iterator Iterator;
    public:

        SignalContainer()
        {
        }

        SignalContainer(const SignalContainer& oth)
        {
            LockBlock_t lock(*this);

            for (auto& con : oth.m_ConnectedSlots)
            {
                con->GetDest()->SignalConnect(this);
                m_ConnectedSlots.push_back(con->Clone());
            }
        }

        SlotsContainer_t& ConnectedSlots()
        {
            return m_ConnectedSlots;
        }

        virtual ~SignalContainer()
        {
            DisconnectAll();
        }

        void DisconnectAll()
        {
            LockBlock_t lock(*this);

            for (auto & con : m_ConnectedSlots)
            {
                con->GetDest()->SignalDisconnect(this);
                delete con;
            }

            m_ConnectedSlots.clear();
        }

        void Disconnect(HasSlots* pclass)
        {
            LockBlock_t lock(*this);
            int i = 0;

            for (auto& con : m_ConnectedSlots)
            {
                if (con->GetDest() == pclass)
                {
                    delete con;
                    Iterator it;
                    std::advance(it, i);
                    m_ConnectedSlots.erase(it);
                    pclass->SignalDisconnect(this);
                    return;
                }
                ++i;
            }
        }

        void SlotDisconnect(HasSlots* pslot)
        {
            LockBlock_t lock(*this);

            Iterator it = m_ConnectedSlots.begin();
            Iterator itEnd = m_ConnectedSlots.end();

            while (it != itEnd)
            {
                Iterator itNext = it;
                ++itNext;

                if ((*it)->GetDest() == pslot)
                {
                    m_ConnectedSlots.erase(it);
                    //			delete *it;
                }

                it = itNext;
            }
        }

        void SlotDuplicate(const HasSlots* oldtarget, HasSlots* newtarget)
        {
            LockBlock_t lock(*this);

            for (auto& con : m_ConnectedSlots)
            {
                if (con->GetDest() == oldtarget)
                {
                    m_ConnectedSlots.push_back(con->Duplicate(newtarget));
                }
            }
        }
    } ;

    template <class Signature>
    class SignalBase : public SignalContainer<std::list<ConnectionBase<Signature>*>>
    {};



}//Common