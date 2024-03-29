/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/
#include "MultiAgentExperience/Thread/Executor/Threading/ThreadMoniker.h"
#include "MultiAgentExperience/Thread/Executor/Threading/WorkerThread.h"

namespace multiAgentExperience {
namespace thread {
namespace executor {
namespace threading {

WorkerThread::WorkerThread() :
        m_moniker{threading::ThreadMoniker::generateMoniker()},
        m_stop{false},
        m_cancel{false} {
    m_thread = std::thread{std::bind(&WorkerThread::runInternal, this)};
}

WorkerThread::~WorkerThread() {
    // We set purposely set m_stop before locking to break the loop that is running work while holding the mutex.
    m_stop = true;
    std::unique_lock<std::mutex> lock(m_mutex);
    // If we had a spurious wake at the time of setting m_stop = true above, by locking here, we ensure that the
    // m_workReady condition variable has to be waiting again (since it will have released the lock for us to acquire
    // it here. Therefore by locking and unlocking the mutex here we protect form a spurious wake, and ensure the
    // worker thread will exit allowing the thread to be joined.
    lock.unlock();
    m_workReady.notify_one();
    if (m_thread.joinable()) {
        m_thread.join();
    }
}

std::string WorkerThread::getMoniker() const {
    return m_moniker;
}

void WorkerThread::cancel() {
    m_cancel = true;
}

void WorkerThread::run(std::function<bool()> workFunc) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_cancel = false;
    m_workerFunc = move(workFunc);
    m_workReady.notify_one();
}

void WorkerThread::runInternal() {
    threading::ThreadMoniker::setThisThreadMoniker(m_moniker);
    std::unique_lock<std::mutex> lock(m_mutex);
    do {
        // If run is called before the thread starts, it will notify before we wait, so we guard against that by
        // checking if the worker function has been set before waiting.
        while (!m_workerFunc && !m_stop) {
            m_workReady.wait(lock);
        }
        while (!m_stop && !m_cancel && m_workerFunc())
            ;
        m_workerFunc = nullptr;
    } while (!m_stop);
}

} // threading
} // executor
} // thread
} // multiAgentExperience