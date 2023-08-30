/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_COMMON_CALLBACKDISPATCHER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_COMMON_CALLBACKDISPATCHER_H_

#include <atomic>
#include <future>

#include "OnCompletionCallback.h"

namespace multiAgentExperience {
namespace library {
namespace common {

/**
 * The CallbackDispatcher is responsible for passing a callback to an agent via some function. It then waits
 * for the agent to execute or ignore the callback.
 *
 * @tparam CallbackType The type of the callback
 */
template <typename CallbackType>
class CallbackDispatcher {
public:
    /**
     * Invokes the method @c function on the object @c object and passes a callback along with variable number of
     * arguments. This should be invoked only once per object.
     *
     * @tparam Object The object on which the function is to be invoked.
     * @tparam Function The function to be invoked. This function must accept a callback of type @c CallbackType.
     * @tparam Args Variable number of arguments, which can be passed to @c function.
     */
    template <typename Object, typename Function, typename... Args>
    void operator()(Object object, Function function, Args... args) {
        auto expected = false;

        // Set to true, if false
        if (!std::atomic_compare_exchange_strong(&m_isCallbackDispatched, &expected, true)) {
            // Callback is already dispatched.
            return;
        }

        auto callback = std::make_shared<CallbackType>();

        /// The weak pointer to the callback is saved, so that it may be waited on in @c waitForCallback
        m_weakCallback = callback;

        (*object.*function)(callback, std::forward<Args>(args)...);
    }

    /**
     * @brief Waits for the callback to be executed by the agent.
     *
     * @details We only wait for the callback to be executed, if the weak pointer to the callback has not expired.
     * If expired, it implies that the callback was ignored by the agent, and we do not need to wait anymore.
     */
    void waitForCallback() {
        if (auto callback = m_weakCallback.lock()) {
            callback->wait();
        }
    }

private:
    /// The weak pointer to the callback
    std::weak_ptr<CallbackType> m_weakCallback;

    /// Indicates if the callback has been sent across.
    std::atomic<bool> m_isCallbackDispatched = {false};
};

}  // namespace common
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_COMMON_CALLBACKDISPATCHER_H_
