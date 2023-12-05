/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Common/OnCompletionCallback.h"

static const std::string MODULE_TAG("OnCompletionCallback");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

namespace multiAgentExperience {
namespace library {
namespace common {

void OnCompletionCallback::wait() {
    LX(DEBUG3, "");
    m_promise.get_future().wait();
}

bool OnCompletionCallback::isCallbackExecuted() {
    LX(DEBUG3, "");
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_isCallbackExecuted;
}

void OnCompletionCallback::completed() {
    LX(DEBUG3, "");
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        if (m_isCallbackExecuted) {
            LX(DEBUG3, "Callback already executed");
            return;
        }
        m_isCallbackExecuted = true;
    }
    m_promise.set_value();
}

}  // namespace common
}  // namespace library
}  // namespace multiAgentExperience