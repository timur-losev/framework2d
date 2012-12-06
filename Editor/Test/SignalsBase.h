#ifndef SignalsBase_h__
#define SignalsBase_h__


class SignalsBase
{
private:
protected:

    typedef std::map<size_t, boost::any> SignaturesMap_t;

    SignaturesMap_t m_Signatures;

public:

    SignalsBase();
    virtual ~SignalsBase();
#if 1
    void AttachOn(const std::string& key, boost::function<void (void)> signature)
    {
        m_Signatures[std::hash<std::string>()(key)] = signature;
    }

    template<class P0>
    void AttachOn(const std::string& key, boost::function<void (P0)> signature)
    {
        m_Signatures[std::hash<std::string>()(key)] = signature;
    }

    template<class P0, class P1>
    void AttachOn(const std::string& key, boost::function<void (P0, P1)> signature)
    {
        m_Signatures[std::hash<std::string>()(key)] = signature;
    }

    template<class P0, class P1, class P2>
    void AttachOn(const std::string& key, boost::function<void (P0, P1, P2)> signature)
    {
        m_Signatures[std::hash<std::string>()(key)] = signature;
    }

    template<class P0, class P1, class P2, class P3>
    void AttachOn(const std::string& key, boost::function<void (P0, P1, P2, P3)> signature)
    {
        m_Signatures[std::hash<std::string>()(key)] = signature;
    }
#endif

    void DoVoidCall(const std::string& key)
    {
        size_t hashkey = std::hash<std::string>()(key);
        SignaturesMap_t::iterator it = m_Signatures.find(hashkey);

        assert(it != m_Signatures.end() && "Impossible to do call.");

        typedef boost::function<void (void)> func_t;
        try
        {
            func_t f = boost::any_cast<func_t>(it->second);
            f();
        }
        catch(boost::bad_any_cast& e)
        {
            printf("%s", e.what());
            return;
        }
    }

    template<class P0>
    void DoVoidCall(const std::string& key, const P0& arg0)
    {
        size_t hashkey = std::hash<std::string>()(key);
        SignaturesMap_t::iterator it = m_Signatures.find(hashkey);

        assert(it != m_Signatures.end() && "Impossible to do call.");

        typedef boost::function<void (P0)> func_t;
        try
        {
            func_t f = boost::any_cast<func_t>(it->second);
            f(arg0);
        }
        catch(boost::bad_any_cast& e)
        {
            printf("%s", e.what());
            return;
        }
    }

    template<class P0, class P1>
    void DoVoidCall(const std::string& key, const P0& arg0, const P1& arg1)
    {
        size_t hashkey = std::hash<std::string>()(key);
        SignaturesMap_t::iterator it = m_Signatures.find(hashkey);

        assert(it != m_Signatures.end() && "Impossible to do call.");

        typedef boost::function<void (P0, P1)> func_t;
        try
        {
            func_t f = boost::any_cast<func_t>(it->second);
            f(arg0, arg1);
        }
        catch(boost::bad_any_cast& e)
        {
            printf("%s", e.what());
            return;
        }
    }

    template<class P0, class P1, class P2>
    void DoVoidCall(const std::string& key, const P0& arg0, const P1& arg1, const P2& arg2)
    {
        size_t hashkey = std::hash<std::string>()(key);
        SignaturesMap_t::iterator it = m_Signatures.find(hashkey);

        assert(it != m_Signatures.end() && "Impossible to do call.");

        typedef boost::function<void (P0, P1, P2)> func_t;
        try
        {
            func_t f = boost::any_cast<func_t>(it->second);
            f(arg0, arg1, arg2);
        }
        catch(boost::bad_any_cast& e)
        {
            printf("%s", e.what());
            return;
        }
    }

    template<class P0, class P1, class P2, class P3>
    void DoVoidCall(const std::string& key, const P0& arg0, const P1& arg1, const P2& arg2, const P3& arg3)
    {
        size_t hashkey = std::hash<std::string>()(key);
        SignaturesMap_t::iterator it = m_Signatures.find(hashkey);

        assert(it != m_Signatures.end() && "Impossible to do call.");

        typedef boost::function<void (P0, P1, P2, P3)> func_t;
        try
        {
            func_t f = boost::any_cast<func_t>(it->second);
            f(arg0, arg1, arg2, arg3);
        }
        catch(boost::bad_any_cast& e)
        {
            printf("%s", e.what());
            return;
        }
    }
};

#endif // SignalsBase_h__
