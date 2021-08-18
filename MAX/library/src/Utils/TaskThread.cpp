/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include <chrono>

#include "Utils/Threading/TaskThread.h"

namespace multiAgentExperience {
namespace library {
namespace utils {
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
        return false;
    }

    bool notRunning = false;
    if (!m_alreadyStarting.compare_exchange_strong(notRunning, true)) {
        return false;
    }

    m_startTime = std::chrono::steady_clock::now();

    m_stop = true;
    std::lock_guard<std::mutex> guard(m_mutex);
    if (m_shuttingDown) {
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
    // Reset stop flag and already starting flag.
    m_stop = false;
    m_alreadyStarting = false;

    while (!m_stop && jobRunner())
        ;
    m_threadPool->releaseWorker(std::move(m_workerThread));
}

}  // namespace threading
}  // namespace utils
}  // namespace library
}  // namespace multiAgentExperience
