//#include "pch.h"
#include "Invoker.h"
#include <condition_variable>

namespace Common {

//#ifdef ENABLE_BOOST

static std::condition_variable CondVar;

Invoker::Invoker() : m_Created(FALSE)
{

}

Invoker::~Invoker()
{

}

bool_t Invoker::NeedInvoke() const
{
    APP_API_ASSERT(m_Created);

    if (m_Thread)
        return std::this_thread::get_id() != m_Thread->get_id();
    else if (m_ThreadId)
        return *m_ThreadId != std::this_thread::get_id();

    APP_API_ASSERT("There are no acceptable comparator for thread id" && FALSE);

    return FALSE;
}

void Invoker::BeginInvoke( InvokeFunction_t f )
{
    APP_API_ASSERT(m_Created);
    std::lock_guard<std::mutex> lock(*m_Mutex);

    m_Funcs.push(f);
}

//Must be called from secondary thread context
void Invoker::UpdateInvoker()
{
    APP_API_ASSERT(m_Created);

    std::lock_guard<std::mutex> lock(*m_Mutex);

    while(!m_Funcs.empty())
    {
		m_Funcs.front()();
        CondVar.notify_one();
		m_Funcs.pop();
    }
}

void Invoker::CreateInvoker(ThreadPtr t, MutexPtr mutex)
{
    APP_API_ASSERT(t);
    APP_API_ASSERT(mutex);

    m_Thread = t;
    m_Mutex = mutex;
    m_Created = TRUE;
}

void Invoker::CreateInvoker(ThreadPtr t)
{
    APP_API_ASSERT(t);

    m_Mutex.reset(new Mutex_t());
    m_Thread = t;
    m_Created = TRUE;
}

void Invoker::CreateInvoker()
{
    m_Thread.reset();
    m_Mutex.reset(new Mutex_t());
    m_ThreadId.reset(new ThreadId_t(std::this_thread::get_id()));
    m_Created = TRUE;
}

void Invoker::PerformCrossThreadCall( InvokeFunction_t f, Invoker* invobj, bool_t wait_until_done )
{
    APP_API_ASSERT(invobj->IsInvokerCreated());

    if (!wait_until_done)
    {
        invobj->BeginInvoke(f);
    }
    else
    {
        std::unique_lock<std::mutex> lock(*invobj->m_Mutex);
        invobj->m_Funcs.push(f);
        CondVar.wait(lock);
    }
}

//#endif //ENABLE_BOOST

} //Common