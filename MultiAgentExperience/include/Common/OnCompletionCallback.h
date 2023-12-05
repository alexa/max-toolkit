/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_COMMON_ONCOMPLETIONCALLBACK_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_COMMON_ONCOMPLETIONCALLBACK_H_

#include <MultiAgentExperience/Common/OnCompletionCallbackInterface.h>

#include <future>

namespace multiAgentExperience {
namespace library {
namespace common {

class OnCompletionCallback : public multiAgentExperience::common::OnCompletionCallbackInterface {
public:
    OnCompletionCallback():
        m_isCallbackExecuted{false} {
    }

    /// Waits until the promise @c m_promise is executed by the agent via the @c completed method
    void wait();

    /// Utility method to know if the callback was executed
    bool isCallbackExecuted();

    /// @name OnCompletionCallbackInterface method overrides.
    /// @{
    void completed() override;
    /// @}

private:
    /// The promise that should be set by the receiver of the @c OnCompletionCallback
    std::promise<void> m_promise;

    /// Indicates whether the callback was executed by the agent
    bool m_isCallbackExecuted;

    /// Mutex to serialize access to @c m_isCallbackExecuted
    std::mutex m_mutex;
};

}  // namespace common
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_COMMON_ONCOMPLETIONCALLBACK_H_
