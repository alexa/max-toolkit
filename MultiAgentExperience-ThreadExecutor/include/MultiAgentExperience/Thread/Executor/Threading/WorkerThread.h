/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/
#ifndef MULTI_AGENT_EXPERIENCE_THREADING_THREADEXECUTOR_WORKERTHREAD_H_
#define MULTI_AGENT_EXPERIENCE_THREADING_THREADEXECUTOR_WORKERTHREAD_H_

#include <atomic>
#include <condition_variable>
#include <functional>
#include <list>
#include <string>
#include <thread>
#include <iostream>

namespace multiAgentExperience {
namespace thread {
namespace executor {
namespace threading {

/**
 * NOTE : This implementation has been picked up from : https://tiny.amazon.com/1hnia515v/codeamazpackCtdlblobmastUtil
 *        and might need to be moved to the "MultiAgentExperience-Testable-Device-Agent-API"
 *        package in the future
 *
 * Executes work on a single thread. Stays alive sleeping while there is no work to be done.
 */
class WorkerThread {
public:
    /**
     * Construct a worker thread.
     */
    WorkerThread();

    /**
     * Destruct a worker thread.
     */
    ~WorkerThread();

    /**
     * Perform work on this worker thread until the work is complete or cancel is called.
     *
     * @param workFunc the work function, which shall be called repeatedly while the workFunc returns true or until
     *     cancel() is called.
     */
    void run(std::function<bool()> workFunc);

    /**
     * Cancel currently running work. If work is not running, the call has no effect.
     */
    void cancel();

    /**
     * Return the moniker for the worker thread.
     * @return the worker thread moniker.
     */
    std::string getMoniker() const;

private:
    /**
     * method for running thread.
     */
    void runInternal();

    /// The thread moniker for the worker thread.
    const std::string m_moniker;

    /// Flag indicating the thread is stopping.
    std::atomic<bool> m_stop;

    /// Flag indicating the work should be cancelled
    std::atomic<bool> m_cancel;

    /// The thread on which to perform work.
    std::thread m_thread;

    /// The worker function.
    std::function<bool()> m_workerFunc;

    /// Mutex for protecting the condition.
    std::mutex m_mutex;

    /// Condition variable for waking the thread.
    std::condition_variable m_workReady;
};

} // threading
} // executor
} // thread
} // multiAgentExperience

#endif // MULTI_AGENT_EXPERIENCE_THREADING_THREADEXECUTOR_WORKERTHREAD_H_