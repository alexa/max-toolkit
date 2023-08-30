/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
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
