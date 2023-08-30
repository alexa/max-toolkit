/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_UTILS_FOCUSRESULT_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_UTILS_FOCUSRESULT_H

#include <AVSCommon/SDKInterfaces/ExternalFocusMediatorCallbackInterface.h>

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace utils {

class FocusResult {
public:
    explicit FocusResult(
            const std::error_condition& error) :
            m_focusState{},
            m_mixingBehavior{},
            m_success{false},
            m_error{error} {

    }
    explicit FocusResult(
            const alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusState& focus,
            const alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalMixingBehavior& mixingBehavior) :
            m_focusState{focus},
            m_mixingBehavior{mixingBehavior},
            m_success{true},
            m_error{} {
    }

    alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusState
    getFocusState() const {
        return m_focusState;
    }
    alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalMixingBehavior
    getMixingBehavior() const {
        return m_mixingBehavior;
    };

    bool isSuccess() const {
        return m_success;
    }

    const std::error_condition &getError() const {
        return m_error;
    }

private:
    alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusState m_focusState;
    alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalMixingBehavior m_mixingBehavior;
    bool m_success;
    std::error_condition m_error;
};

} // namespace utils
} // namespace multiAgentExperience
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_UTILS_FOCUSRESULT_H
