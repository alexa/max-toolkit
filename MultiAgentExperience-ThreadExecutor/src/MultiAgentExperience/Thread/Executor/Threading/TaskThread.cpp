/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/
#include <chrono>

#include "MultiAgentExperience/Thread/Executor/Threading/TaskThread.h"

/// String to identify log entries originating from this file.
static const std::string MODULE_TAG("TaskThread");
#define LX(logCommand, message) std::cout << #logCommand << ":" << MODULE_TAG << ":" << __func__ << ":" << message << std::endl;

namespace multiAgentExperience {
namespace thread {
namespace executor {
namespace threading {

TaskThread::TaskThread() :
        m_shuttingDown{false},
        m_stop{false},
        m_alreadyStarting{false},
        m_threadPool{ThreadPool::getDefaultThreadPool()} {
}

TaskThread::~TaskThread() {
    for (;;) {
        {
            std::lock_guard<std::mutex> guard(m_mutex);
            if (!m_alreadyStarting || m_workerThread == nullptr) {
                m_shuttingDown = true;
                return;
            }
            // if We get here, then we obtained the mutex between TaskThread::start and TaskThread::run methods.
        }
        // Wait until the thread has begun running so we can stop safely.
        while (m_alreadyStarting) {
            std::this_thread::yield();
        }
        m_stop = true;
    }
}

bool TaskThread::start(std::function<bool()> jobRunner) {
    if (!jobRunner) {
        LX(ERROR, "startFailed, reason : invalidFunction");
        return false;
    }

    bool notRunning = false;
    if (!m_alreadyStarting.compare_exchange_strong(notRunning, true)) {
        LX(ERROR, "startFailed, reason : tooManyThreads");
        return false;
    }

    m_startTime = std::chrono::steady_clock::now();

    m_stop = true;
    std::lock_guard<std::mutex> guard(m_mutex);
    if (m_shuttingDown) {
        LX(ERROR, "startFailed, reason : shuttingDown");
        return false;
    }
    m_workerThread = m_threadPool->obtainWorker(m_moniker);

    m_moniker = m_workerThread->getMoniker();
    m_workerThread->run([this, jobRunner] {
        TaskThread::run(jobRunner);
        return false;
    });
    return true;
}

void TaskThread::run(std::function<bool()> jobRunner) {
    std::lock_guard<std::mutex> guard(m_mutex);
    LX(DEBUG3, "startThread, moniker : " + m_moniker + " duration : " + std::to_string(
            std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - m_startTime)
                    .count()));

    // Reset stop flag and already starting flag.
    m_stop = false;
    m_alreadyStarting = false;

    while (!m_stop && jobRunner());
    m_threadPool->releaseWorker(std::move(m_workerThread));
}

} // threading
} // executor
} // thread
} // multiAgentExperience