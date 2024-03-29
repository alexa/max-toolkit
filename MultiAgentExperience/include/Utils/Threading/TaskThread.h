/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_UTILS_THREADING_TASKTHREAD_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_UTILS_THREADING_TASKTHREAD_H_

#include <atomic>
#include <chrono>
#include <functional>
#include <string>
#include <thread>

#include "ThreadPool.h"
#include "WorkerThread.h"

namespace multiAgentExperience {
namespace library {
namespace utils {
namespace threading {

/**
 * A TaskThread executes in sequence until no more tasks exists.
 *
 * @note It's the caller responsibility to restart the @c TaskThread if jobRunner returns false.
 */
class TaskThread {
public:
    /**
     * Constructs a TaskThread to run tasks on a single thread. This does not start the thread.
     */
    TaskThread();

    /**
     * Destructs the TaskThread.
     */
    ~TaskThread();

    /**
     * Start executing tasks from the given job runner. The task thread will keep running until @c jobRunner
     * returns @c false or @c start gets called again.
     *
     * @param jobRunner Function that should execute jobs. The function should return @c true if there's more tasks
     * to be executed.
     * @return @c true if it succeeds to start the new jobRunner thread; @c false if it fails.
     */
    bool start(std::function<bool()> jobRunner);

private:
    /**
     * Run the @c jobRunner until it returns @c false or @c m_stop is set to true.
     *
     * @param jobRunner Function that should execute the next job. The function should return @c true if a new job
     * still exists.
     */
    void run(std::function<bool()> jobRunner);

    /// The monotonic start time of the thread.
    std::chrono::steady_clock::time_point m_startTime;

    /// Mutex for protecting the worker thread.
    std::mutex m_mutex;

    /// Flag for when the thread pool is shutting down.
    bool m_shuttingDown;

    /// Flag used by the new thread to ensure that the old thread will exit once the current job ends.
    std::atomic_bool m_stop;

    /// Flag used to indicate that there is a new job starting.
    std::atomic_bool m_alreadyStarting;

    /// The task thread moniker.
    std::string m_moniker;

    /// ThreadPool to use for obtaining threads.
    std::shared_ptr<ThreadPool> m_threadPool;

    /// The worker thread to run tasks on.
    std::unique_ptr<WorkerThread> m_workerThread;
};

}  // namespace threading
}  // namespace utils
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_UTILS_THREADING_TASKTHREAD_H_
