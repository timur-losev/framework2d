#pragma once

#include <thread>
#include <mutex>
#include <functional>
#include <set>
#include <list>
#include <iostream>
#include "SharedPointer.h"

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

    struct ISignal : public CurrentThreadPolicy
    {
        virtual void SlotDisconnect(HasSlots * pslot) = 0;
        virtual void SlotDuplicate(const HasSlots* poldslot, HasSlots * pnewslot) = 0;

        virtual ~ISignal()
        {
        }
    } ;
    //////////////////////////////////////////////////////////////////////////

    class HasSlots : public CurrentThreadPolicy
    {
    private:
        typedef std::set<ISignal*> Senders_t;
        typedef Senders_t::const_iterator ConstIter;

        Senders_t m_Senders;
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

    template<typename... ArgumentsTypes>
    class ConnectionBase
    {
    public:

        virtual ~ConnectionBase()
        {
        }
        virtual HasSlots* GetDest() const = 0;
        virtual void Perform(ArgumentsTypes...) = 0;
        virtual ConnectionBase<ArgumentsTypes...>* Clone() = 0;
        virtual ConnectionBase<ArgumentsTypes...>* Duplicate(HasSlots* pnewdest) = 0;
    } ;

    template<> class ConnectionBase<void>
    {
    public:

        virtual ~ConnectionBase()
        {
        }
        virtual HasSlots* GetDest() const = 0;
        virtual void Perform(void) = 0;
        virtual ConnectionBase* Clone() = 0;
        virtual ConnectionBase* Duplicate(HasSlots* pnewdest) = 0;
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

    template<typename... ArgumentsTypes>
    class SignalBase : public SignalContainer<std::list<ConnectionBase<ArgumentsTypes... >> >
    {
    };

    template<> class SignalBase<void> : public SignalContainer<std::list<ConnectionBase<void >> >
    {
    };

    template<typename... ArgumentTypes>
    class Connection : public ConnectionBase<ArgumentTypes...>
    {
    public:
        typedef std::function<void (ArgumentTypes...) > Signature_t;
    protected:
        Signature_t m_Signature;
        HasSlots*   m_Target;
    public:

        Connection()
        {
        }

        Connection(const Connection& oth)
        {
            m_Signature = oth.m_Signature;
            m_Target = oth.m_Target;
        }

        Connection(const Signature_t& signature, HasSlots* target)
        {
            m_Signature = signature;
            m_Target = target;
        }

        virtual ConnectionBase<ArgumentTypes...>* Clone()
        {
            return new Connection < ArgumentTypes...>(*this);
        }

        virtual ConnectionBase<ArgumentTypes...>* Duplicate(HasSlots* pnewdest)
        {
            return nullptr;
        }

        virtual void Perform(ArgumentTypes... args)
        {
            m_Signature(args...);
        }

        virtual HasSlots* GetDest() const
        {
            return m_Target;
        }
    } ;

    template<>
    class Connection<void> : public ConnectionBase<void>
    {
    public:
        typedef std::function<void (void) > Signature_t;
    protected:
        Signature_t m_Signature;
        HasSlots*   m_Target;
    public:

        Connection()
        {
        }

        Connection(const Connection& oth)
        {
            m_Signature = oth.m_Signature;
            m_Target = oth.m_Target;
        }

        Connection(const Signature_t& signature, HasSlots* target)
        {
            m_Signature = signature;
            m_Target = target;
        }

        virtual ConnectionBase<void>* Clone()
        {
            return new Connection<void>(*this);
        }

        virtual ConnectionBase<void>* Duplicate(HasSlots* pnewdest)
        {
            return nullptr;
        }

        virtual void Perform()
        {
            m_Signature();
        }

        virtual HasSlots* GetDest() const
        {
            return m_Target;
        }
    } ;

    template<typename... ArgumentsTypes>
    class Signal : public SignalContainer<std::list<ConnectionBase<ArgumentsTypes...>* >>
    {
        typedef SignalContainer < std::list < ConnectionBase < ArgumentsTypes...>* >> Base;
        public:
        typedef std::function<void (ArgumentsTypes...) > SlotType;

        void Connect(const SlotType& signature, HasSlots * target)
        {
            LockBlock_t lock(*this);
            Connection < ArgumentsTypes...>* conn = new Connection < ArgumentsTypes...>(signature, target);
            Base::m_ConnectedSlots.push_back(conn);
            conn->GetDest()->SignalConnect(this);
        }

        void Perform(ArgumentsTypes... args)
        {
            LockBlock_t lock(*this);

            auto itNext = Base::m_ConnectedSlots.begin();
            auto it = Base::m_ConnectedSlots.begin();
            auto itEnd = Base::m_ConnectedSlots.end();

            while (it != itEnd)
            {
                itNext = it;
                ++itNext;

                (*it)->perform(args...);

                it = itNext;
            }
        }

        void operator()(ArgumentsTypes... args)
        {
            LockBlock_t lock(*this);
            auto itNext = Base::m_ConnectedSlots.begin();
            auto it = Base::m_ConnectedSlots.begin();
            auto itEnd = Base::m_ConnectedSlots.end();

            while (it != itEnd)
            {
                itNext = it;
                ++itNext;

                (*it)->Perform(args...);

                it = itNext;
            }
        }
    };

    template<>
    class Signal<void> : public SignalContainer<std::list<ConnectionBase<void>* >>
    {
        typedef SignalContainer < std::list < ConnectionBase<void>* >> Base;
        public:
        typedef std::function<void (void) > SlotType;

        void Connect(const SlotType& signature, HasSlots * target)
        {
            LockBlock_t lock(*this);
            Connection<void>* conn = new Connection<void>(signature, target);
            Base::m_ConnectedSlots.push_back(conn);
            conn->GetDest()->SignalConnect(this);
        }

        void Perform()
        {
            LockBlock_t lock(*this);

            auto itNext = Base::m_ConnectedSlots.begin();
            auto it = Base::m_ConnectedSlots.begin();
            auto itEnd = Base::m_ConnectedSlots.end();

            while (it != itEnd)
            {
                itNext = it;
                ++itNext;

                (*it)->Perform();

                it = itNext;
            }
        }

        void operator()()
        {
            LockBlock_t lock(*this);
            auto itNext = Base::m_ConnectedSlots.begin();
            auto it = Base::m_ConnectedSlots.begin();
            auto itEnd = Base::m_ConnectedSlots.end();

            while (it != itEnd)
            {
                itNext = it;
                ++itNext;

                (*it)->Perform();

                it = itNext;
            }
        }
    };
} //Common