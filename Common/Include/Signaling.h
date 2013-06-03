/*
* Singnaling.h
*
*  Created on:
*      Author: void
*/

#ifndef Signaling_h__
#define Signaling_h__

#include "Noncopyable.h"
#include "Any.h"
#include "Logger.h" //Warning: Logger must be created!
#include <functional>

//#include "Sigslot2.h"

namespace Common {

#define BAD_CAST_MESSAGE\
    LogMessage(LOG_ERR, e.what() << " From call = "<< DebugName() << " key = " << key)

class Signaling: /*public HasSlots, */public Noncopyable
{
protected:
    typedef std::map<size_t, Any> SignaturesMap_t;
    SignaturesMap_t               m_Signatures;
public:

    virtual const char* DebugName() const = 0;


    void AttachOn(size_t key, std::function<void ()> signature)
    {
        APP_API_ASSERT(!IsAttached(key));
        m_Signatures[key] = signature;
    }

    template<typename A0>
    void AttachOn(size_t key, std::function<void (A0)> signature)
    {
        APP_API_ASSERT(!IsAttached(key));
        m_Signatures[key] = signature;
    }

    template<class A0, class A1>
    void AttachOn(size_t key, std::function<void (A0, A1)> signature)
    {
        APP_API_ASSERT(!IsAttached(key));
        m_Signatures[key] = signature;
    }

    template<class A0, class A1, class A2>
    void AttachOn(size_t key, std::function<void (A0, A1, A2)> signature)
    {
        APP_API_ASSERT(!IsAttached(key));
        m_Signatures[key] = signature;
    }

    template<class A0, class A1, class A2, class A3>
    void AttachOn(size_t key, std::function<void (A0, A1, A2, A3)> signature)
    {
        APP_API_ASSERT(!IsAttached(key));
        m_Signatures[key] = signature;
    }

    template<class A0, class A1, class A2, class A3, class A4>
    void AttachOn(size_t key, std::function<void (A0, A1, A2, A3, A4)> signature)
    {
        APP_API_ASSERT(!IsAttached(key));
        m_Signatures[key] = signature;
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5>
    void AttachOn(size_t key, std::function<void (A0, A1, A2, A3, A4, A5)> signature)
    {
        APP_API_ASSERT(!IsAttached(key));
        m_Signatures[key] = signature;
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5, class A6>
    void AttachOn(size_t key, std::function<void (A0, A1, A2, A3, A4, A5, A6)> signature)
    {
        APP_API_ASSERT(!IsAttached(key));
        m_Signatures[key] = signature;
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    void AttachOn(size_t key, std::function<void (A0, A1, A2, A3, A4, A5, A6, A7)> signature)
    {
        APP_API_ASSERT(!IsAttached(key));
        m_Signatures[key] = signature;
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    void AttachOn(size_t key, std::function<void (A0, A1, A2, A3, A4, A5, A6, A7, A8)> signature)
    {
        APP_API_ASSERT(!IsAttached(key));
        m_Signatures[key] = signature;
    }

    bool_t IsAttached(size_t key)
    {
        return m_Signatures.find(key) != m_Signatures.end();
    }

    void  RemoveLink(size_t key)
    {
        SignaturesMap_t::iterator iter = m_Signatures.find(key);
        if (iter != m_Signatures.end())
            m_Signatures.erase(iter);
    }

public:

    void CallBack(size_t key)
    {
        SignaturesMap_t::iterator it = m_Signatures.find(key);

        if(it == m_Signatures.end())
        {
            //LogMessage(LOG_WARNING, "Impossible to do call by key = [" << key << "]. Host:[" << DebugName() << "]");
            return;
        }

        typedef std::function<void (void)> func_t;
        try
        {
            func_t f = Common::any_cast<func_t>(it->second);
            f();
        }
        catch(Common::bad_any_cast& e)
        {
            BAD_CAST_MESSAGE;
            return;
        }
    }

#ifdef _MSC_VER
    template<typename Args0>
    void CallBack(size_t key, Args0 arg0)
    {
        SignaturesMap_t::iterator it = m_Signatures.find(key);

        if(it == m_Signatures.end())
        {
            //LogMessage(LOG_WARNING, "Impossible to do call by key = [" << key << "]");
            return;
        }

        typedef std::function<void (Args0)> func_t;
        try
        {
            func_t f = Common::any_cast<func_t>(it->second);
            f(arg0);
        }
        catch(Common::bad_any_cast& e)
        {
            BAD_CAST_MESSAGE;
            return;
        }
    }

    template<typename Args0, typename Args1>
    void CallBack(size_t key, Args0 arg0, Args1 arg1)
    {
        SignaturesMap_t::iterator it = m_Signatures.find(key);

        if(it == m_Signatures.end())
        {
            //LogMessage(LOG_WARNING, "Impossible to do call by key = [" << key << "]");
            return;
        }

        typedef std::function<void (Args0, Args1)> func_t;
        try
        {
            func_t f = Common::any_cast<func_t>(it->second);
            f(arg0, arg1);
        }
        catch(Common::bad_any_cast& e)
        {
            BAD_CAST_MESSAGE;
            return;
        }
    }

    template<typename Args0, typename Args1, typename Args2>
    void CallBack(size_t key, Args0 arg0, Args1 arg1, Args2 arg2)
    {
        SignaturesMap_t::iterator it = m_Signatures.find(key);

        if(it == m_Signatures.end())
        {
            //LogMessage(LOG_WARNING, "Impossible to do call by key = [" << key << "]");
            return;
        }

        typedef std::function<void (Args0, Args1, Args2)> func_t;
        try
        {
            func_t f = Common::any_cast<func_t>(it->second);
            f(arg0, arg1, arg2);
        }
        catch(Common::bad_any_cast& e)
        {
            BAD_CAST_MESSAGE;
            return;
        }
    }

    template<typename Args0, typename Args1, typename Args2, typename Args3>
    void CallBack(size_t key, Args0 arg0, Args1 arg1, Args2 arg2, Args3 arg3)
    {
        SignaturesMap_t::iterator it = m_Signatures.find(key);

        if(it == m_Signatures.end())
        {
            //LogMessage(LOG_WARNING, "Impossible to do call by key = [" << key << "]");
            return;
        }

        typedef std::function<void (Args0, Args1, Args2, Args3)> func_t;
        try
        {
            func_t f = Common::any_cast<func_t>(it->second);
            f(arg0, arg1, arg2, arg3);
        }
        catch(Common::bad_any_cast& e)
        {
            BAD_CAST_MESSAGE;
            return;
        }
    }

    template<typename Args0, typename Args1, typename Args2, typename Args3, typename Args4>
    void CallBack(size_t key, Args0 arg0, Args1 arg1, Args2 arg2, Args3 arg3, Args4 arg4)
    {
        SignaturesMap_t::iterator it = m_Signatures.find(key);

        if(it == m_Signatures.end())
        {
            //LogMessage(LOG_WARNING, "Impossible to do call by key = [" << key << "]");
            return;
        }

        typedef std::function<void (Args0, Args1, Args2, Args3, Args4)> func_t;
        try
        {
            func_t f = Common::any_cast<func_t>(it->second);
            f(arg0, arg1, arg2, arg3, arg4);
        }
        catch(Common::bad_any_cast& e)
        {
            BAD_CAST_MESSAGE;
            return;
        }
    }
#else
    template<typename ... Args>
    void CallBack(size_t key, Args... args)
    {
        SignaturesMap_t::iterator it = m_Signatures.find(key);

        if(it == m_Signatures.end())
        {
            //LogMessage(LOG_WARNING, "Impossible to do call by key = [" << key << "]. Host:[" << DebugName() << "]");
            return;
        }

        typedef std::function<void (Args...)> func_t;
        try
        {
            func_t f = Common::any_cast<func_t>(it->second);
            f(args...);
        }
        catch(Common::bad_any_cast& e)
        {
            BAD_CAST_MESSAGE;
            return;
        }
    }
#endif

};

#undef BAD_CAST_MESSAGE

} //Common

#endif // Signaling_h__
