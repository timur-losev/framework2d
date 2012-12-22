#ifndef Invoker_h__
#define Invoker_h__

#include <AppApi.h>
#include "ThreadBase.h"

namespace Common {

class Invoker
{
private:
    typedef std::function<void (void)>      InvokeFunction_t;
    std::queue<InvokeFunction_t>            m_Funcs;
    bool_t                                  m_Created;
protected:
    ThreadPtr                               m_Thread;
    ThreadIdPtr                             m_ThreadId;
    MutexPtr                                m_Mutex;
protected:

    Invoker();
    virtual ~Invoker();

    bool_t                                  NeedInvoke() const;
    void                                    BeginInvoke(InvokeFunction_t f);
    void                                    UpdateInvoker();

public:
    static void                             PerformCrossThreadCall(InvokeFunction_t f, Invoker* invobj, bool_t wait_until_done);

public:
    void                                    CreateInvoker(ThreadPtr t, MutexPtr mutex); //deprecated
    void                                    CreateInvoker(ThreadPtr t);
    void                                    CreateInvoker();
    bool_t                                  IsInvokerCreated() const { return m_Created; }
    INL ThreadPtr                           Thread() { return m_Thread; }
    INL MutexPtr                            Mutex() { return m_Mutex; }
};

} //Common

#endif // Invoker_h__
