#pragma once

#include <thread>
#include <mutex>
#include <memory>

typedef std::thread Thread_t;
typedef std::mutex Mutex_t;
typedef std::shared_ptr<Thread_t> ThreadPtr;
typedef std::shared_ptr<Mutex_t> MutexPtr;
typedef Thread_t::id ThreadId_t;
typedef std::shared_ptr<ThreadId_t> ThreadIdPtr;