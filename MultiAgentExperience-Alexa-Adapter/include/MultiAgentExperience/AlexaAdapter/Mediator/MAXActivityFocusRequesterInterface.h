/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_MAXACTIVITYFOCUSREQUESTERINTERFACE_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_MAXACTIVITYFOCUSREQUESTERINTERFACE_H

#include <future>
#include <map>
#include <memory>

#include <AVSCommon/Utils/Threading/Executor.h>

#include "MultiAgentExperience/AlexaAdapter/Utils/FocusResult.h"
#include "MultiAgentExperience/AlexaAdapter/Mediator/MAXFocusMediatorCleanupCallback.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace mediator {

class MAXActivityFocusRequesterInterface {
public:
    virtual ~MAXActivityFocusRequesterInterface() = default;

    virtual void initialize(
        const std::weak_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface>& mediatorCallbacks,
        const std::shared_ptr<alexa::AlexaFocusRequestBuffer>& focusRequestBuffer,
        const std::shared_ptr<avsCommon::utils::threading::Executor>& executor) = 0;

    virtual void request(
        const alexaClientSDK::avsCommon::avs::FocusRequest& focusRequest,
        std::shared_ptr<std::promise<utils::FocusResult>> promise,
        std::shared_ptr<MAXFocusMediatorCleanupCallback> cleanupCallback) = 0;

    virtual void stopRequest(const std::string& focusRequestId) = 0;
};

} // namespace mediator
} // namespace multiAgentExperience
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_MAXACTIVITYFOCUSREQUESTERINTERFACE_H
