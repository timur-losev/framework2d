#ifndef Signaling_h__
#define Signaling_h__

#include "Prec.h"
#include "CLogger.h"
#include "EdCommon.h"
#include <boost/any.hpp>
#include <boost/noncopyable.hpp>

#define BAD_CAST_MESSAGE\
    LogMessage(LOG_ERR, e.what() << " From call = "<< DebugName() << " key = " << key)

class Signaling: public boost::noncopyable
{
protected:
    typedef std::map<size_t, boost::any> SignaturesMap_t;
    SignaturesMap_t                      m_Signatures;
public:

    virtual const char* DebugName() const = 0;

    void AttachOn(size_t key, boost::function<void (void)> signature)
    {
        APP_API_ASSERT(!IsAttached(key));
        m_Signatures[key] = signature;
    }

    template<class A0>
    void AttachOn(size_t key, boost::function<void (A0)> signature)
    {
        APP_API_ASSERT(!IsAttached(key));
        m_Signatures[key] = signature;
    }

    template<class A0, class A1>
    void AttachOn(size_t key, boost::function<void (A0, A1)> signature)
    {
        APP_API_ASSERT(!IsAttached(key));
        m_Signatures[key] = signature;
    }

    template<class A0, class A1, class A2>
    void AttachOn(size_t key, boost::function<void (A0, A1, A2)> signature)
    {
        APP_API_ASSERT(!IsAttached(key));
        m_Signatures[key] = signature;
    }

    template<class A0, class A1, class A2, class A3>
    void AttachOn(size_t key, boost::function<void (A0, A1, A2, A3)> signature)
    {
        APP_API_ASSERT(!IsAttached(key));
        m_Signatures[key] = signature;
    }

    template<class A0, class A1, class A2, class A3, class A4>
    void AttachOn(size_t key, boost::function<void (A0, A1, A2, A3, A4)> signature)
    {
        APP_API_ASSERT(!IsAttached(key));
        m_Signatures[key] = signature;
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5>
    void AttachOn(size_t key, boost::function<void (A0, A1, A2, A3, A4, A5)> signature)
    {
        APP_API_ASSERT(!IsAttached(key));
        m_Signatures[key] = signature;
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5, class A6>
    void AttachOn(size_t key, boost::function<void (A0, A1, A2, A3, A4, A5, A6)> signature)
    {
        APP_API_ASSERT(!IsAttached(key));
        m_Signatures[key] = signature;
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    void AttachOn(size_t key, boost::function<void (A0, A1, A2, A3, A4, A5, A6, A7)> signature)
    {
        APP_API_ASSERT(!IsAttached(key));
        m_Signatures[key] = signature;
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    void AttachOn(size_t key, boost::function<void (A0, A1, A2, A3, A4, A5, A6, A7, A8)> signature)
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

protected:

    void CallBack(size_t key)
    {
        SignaturesMap_t::iterator it = m_Signatures.find(key);

        if(it == m_Signatures.end())
        {
            LogMessage(LOG_WARNING, "Impossible to do call by key = [" << key << "]");
            return;
        }

        typedef boost::function<void (void)> func_t;
        try
        {
            func_t f = boost::any_cast<func_t>(it->second);
            f();
        }
        catch(boost::bad_any_cast& e)
        {
            BAD_CAST_MESSAGE;
            return;
        }
    }

    template<class A0>
    void CallBack(size_t key, const A0& arg0)
    {
        SignaturesMap_t::iterator it = m_Signatures.find(key);

        if(it == m_Signatures.end())
        {
            LogMessage(LOG_WARNING, "Impossible to do call by key = [" << key << "]");
            return;
        }

        typedef boost::function<void (A0)> func_t;
        try
        {
            func_t f = boost::any_cast<func_t>(it->second);
            f(arg0);
        }
        catch(boost::bad_any_cast& e)
        {
            BAD_CAST_MESSAGE;
            return;
        }
    }

    template<class A0, class A1>
    void CallBack(size_t key, const A0& arg0, const A1& arg1)
    {
        SignaturesMap_t::iterator it = m_Signatures.find(key);

        if(it == m_Signatures.end())
        {
            LogMessage(LOG_WARNING, "Impossible to do call by key = [" << key << "]");
            return;
        }

        typedef boost::function<void (A0, A1)> func_t;
        try
        {
            func_t f = boost::any_cast<func_t>(it->second);
            f(arg0, arg1);
        }
        catch(boost::bad_any_cast& e)
        {
            BAD_CAST_MESSAGE;
            return;
        }
    }

    template<class A0, class A1, class A2>
    void CallBack(size_t key, const A0& arg0, const A1& arg1, const A2& arg2)
    {
        SignaturesMap_t::iterator it = m_Signatures.find(key);

        if(it == m_Signatures.end())
        {
            LogMessage(LOG_WARNING, "Impossible to do call by key = [" << key << "]");
            return;
        }

        typedef boost::function<void (A0, A1, A2)> func_t;
        try
        {
            func_t f = boost::any_cast<func_t>(it->second);
            f(arg0, arg1, arg2);
        }
        catch(boost::bad_any_cast& e)
        {
            BAD_CAST_MESSAGE;
            return;
        }
    }

    template<class A0, class A1, class A2, class A3>
    void CallBack(size_t key, const A0& arg0, const A1& arg1, const A2& arg2, const A3& arg3)
    {
        SignaturesMap_t::iterator it = m_Signatures.find(key);

        if(it == m_Signatures.end())
        {
            LogMessage(LOG_WARNING, "Impossible to do call by key = [" << key << "]");
            return;
        }

        typedef boost::function<void (A0, A1, A2, A3)> func_t;
        try
        {
            func_t f = boost::any_cast<func_t>(it->second);
            f(arg0, arg1, arg2, arg3);
        }
        catch(boost::bad_any_cast& e)
        {
            BAD_CAST_MESSAGE;
            return;
        }
    }

    template<class A0, class A1, class A2, class A3, class A4>
    void CallBack(size_t key, const A0& arg0, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4)
    {
        SignaturesMap_t::iterator it = m_Signatures.find(key);

        if(it == m_Signatures.end())
        {
            LogMessage(LOG_WARNING, "Impossible to do call by key = [" << key << "]");
            return;
        }

        typedef boost::function<void (A0, A1, A2, A3, A4)> func_t;
        try
        {
            func_t f = boost::any_cast<func_t>(it->second);
            f(arg0, arg1, arg2, arg3, arg4);
        }
        catch(boost::bad_any_cast& e)
        {
            BAD_CAST_MESSAGE;
            return;
        }
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5>
    void CallBack(size_t key, const A0& arg0, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5)
    {
        SignaturesMap_t::iterator it = m_Signatures.find(key);

        if(it == m_Signatures.end())
        {
            LogMessage(LOG_WARNING, "Impossible to do call by key = [" << key << "]");
            return;
        }

        typedef boost::function<void (A0, A1, A2, A3, A4, A5)> func_t;
        try
        {
            func_t f = boost::any_cast<func_t>(it->second);
            f(arg0, arg1, arg2, arg3, arg4, arg5);
        }
        catch(boost::bad_any_cast& e)
        {
            BAD_CAST_MESSAGE;
            return;
        }
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5, class A6>
    void CallBack(size_t key, const A0& arg0, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6)
    {
        SignaturesMap_t::iterator it = m_Signatures.find(key);

        if(it == m_Signatures.end())
        {
            LogMessage(LOG_WARNING, "Impossible to do call by key = [" << key << "]");
            return;
        }

        typedef boost::function<void (A0, A1, A2, A3, A4, A5, A6)> func_t;
        try
        {
            func_t f = boost::any_cast<func_t>(it->second);
            f(arg0, arg1, arg2, arg3, arg4, arg5, arg6);
        }
        catch(boost::bad_any_cast& e)
        {
            BAD_CAST_MESSAGE;
            return;
        }
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    void CallBack(size_t key, const A0& arg0, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6, const A7& arg7)
    {
        SignaturesMap_t::iterator it = m_Signatures.find(key);

        if(it == m_Signatures.end())
        {
            LogMessage(LOG_WARNING, "Impossible to do call by key = [" << key << "]");
            return;
        }

        typedef boost::function<void (A0, A1, A2, A3, A4, A5, A6, A7)> func_t;
        try
        {
            func_t f = boost::any_cast<func_t>(it->second);
            f(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7);
        }
        catch(boost::bad_any_cast& e)
        {
            BAD_CAST_MESSAGE;
            return;
        }
    }

    template<class A0, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    void CallBack(size_t key, const A0& arg0, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6, const A7& arg7, const A8& arg8)
    {
        SignaturesMap_t::iterator it = m_Signatures.find(key);

        if(it == m_Signatures.end())
        {
            LogMessage(LOG_WARNING, "Impossible to do call by key = [" << key << "]");
            return;
        }

        typedef boost::function<void (A0, A1, A2, A3, A4, A5, A6, A7, A8)> func_t;
        try
        {
            func_t f = boost::any_cast<func_t>(it->second);
            f(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8);
        }
        catch(boost::bad_any_cast& e)
        {
            BAD_CAST_MESSAGE;
            return;
        }
    }

    Signaling() {}
    virtual ~Signaling() {};
};

#undef BAD_CAST_MESSAGE

#endif // Signaling_h__
