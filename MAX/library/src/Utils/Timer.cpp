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

#include "Utils/Timing/Timer.h"

namespace multiAgentExperience {
namespace library {
namespace utils {
namespace timing {

Timer::Timer() : m_running(false), m_stopping(false) {
}

Timer::~Timer() {
    stop();
}

void Timer::stop() {
    {
        std::lock_guard<std::mutex> waitLock(m_waitMutex);
        if (m_running) {
            m_stopping = true;
        }
        m_waitCondition.notify_all();
    }

    std::lock_guard<std::mutex> joinLock(m_joinMutex);
    if (std::this_thread::get_id() != m_thread.get_id() && m_thread.joinable()) {
        m_thread.join();
    }
}

bool Timer::isActive() const {
    return m_running;
}

bool Timer::activate() {
    return !m_running.exchange(true);
}

}  // namespace timing
}  // namespace utils
}  // namespace library
}  // namespace multiAgentExperience
