/*
 * File:   Sigslot2_adaptive_gcc.h
 * Author: timur.losev@gmail.com
 *
 * Created on December 12, 2012, 10:08 PM
 */

#ifndef SIGSLOT2_ADAPTIVE_GCC_H
#    define	SIGSLOT2_ADAPTIVE_GCC_H

#    include <thread>
#    include <mutex>
#    include <functional>
#    include <set>
#    include <list>
#    include <iostream>

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

        virtual ConnectionBase<Signature>* Clone() = 0;
        virtual ConnectionBase<Signature>* Duplicate(HasSlots* pnewdest) = 0;
        virtual Signature& GetSignature() = 0;
    } ;

    template<typename SlotsContainer>
    class SignalContainer : public ISignal
    {
    private:
    protected:
        typedef SlotsContainer SlotsContainer_t;

        CurrentThreadPolicy m_ThreadPolicy;
        SlotsContainer_t    m_ConnectedSlots;
        typedef typename SlotsContainer_t::iterator Iterator;
    public:

        SignalContainer()
        {
        }

        SignalContainer(const SignalContainer& oth)
        {
            LockBlock_t lock(m_ThreadPolicy);

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
            LockBlock_t lock(m_ThreadPolicy);

            for (auto & con : m_ConnectedSlots)
            {
                con->GetDest()->SignalDisconnect(this);
                delete con;
            }

            m_ConnectedSlots.clear();
        }

        void Disconnect(HasSlots* pclass)
        {
            LockBlock_t lock(m_ThreadPolicy);
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
            LockBlock_t lock(m_ThreadPolicy);

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
            LockBlock_t lock(m_ThreadPolicy);

            for (auto& con : m_ConnectedSlots)
            {
                if (con->GetDest() == oldtarget)
                {
                    m_ConnectedSlots.push_back(con->Duplicate(newtarget));
                }
            }
        }
    } ;

    template<class Signature>
    class Connection : public ConnectionBase<Signature>
    {
    public:
        typedef Signature Signature_t;
    protected:
        Signature_t m_Signature;
        HasSlots*   m_Target;
    public:

        Connection()
        {
        }

        Connection(const Connection& oth):
        m_Signature(oth.m_Signature),
        m_Target(oth.m_Target)
        {
        }

        Connection(const Signature_t& signature, HasSlots* target):
        m_Signature(signature),
        m_Target(target)
        {
        }

        virtual ConnectionBase<Signature>* Clone()
        {
            return new Connection <Signature > (*this);
        }

        virtual ConnectionBase<Signature>* Duplicate(HasSlots* pnewdest)
        {
            return nullptr;
        }

        virtual Signature& GetSignature()
        {
            return m_Signature;
        }

        virtual HasSlots* GetDest() const
        {
            return m_Target;
        }
    } ;

    template<class Signature>
    class Signal : public SignalContainer<std::list<ConnectionBase<Signature>* >>
    {
        private:
        typedef SignalContainer < std::list < ConnectionBase<Signature>* >> Base;
        typedef Connection <Signature> Connection_t;
        protected:
        public:

        typedef Signature Signature_t;

        void Connect(const Signature_t& signature, HasSlots * target)
        {
            LockBlock_t lock(Base::m_ThreadPolicy);
            Connection_t* conn = new Connection_t(signature, target);
            Base::m_ConnectedSlots.push_back(conn);
            conn->GetDest()->SignalConnect(this);
        }

        //template<typename... Args>
                void Perform(/*Args... args*/)
        {
            LockBlock_t lock(Base::m_ThreadPolicy);

            auto itNext = Base::m_ConnectedSlots.begin();
            auto it = Base::m_ConnectedSlots.begin();
            auto itEnd = Base::m_ConnectedSlots.end();

            while (it != itEnd)
            {
                itNext = it;
                ++itNext;

                (*it)->GetSignature()(/*args...*/);

                it = itNext;
            }
        }

        /*template<typename... Args>
                void operator()(Args... args)
        {
            Perform(args...);
        }*/
    };
} //Common

#endif	/* SIGSLOT2_ADAPTIVE_GCC_H */

