/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ACTIVITY_ALEXAACTIVITYHANDLER_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ACTIVITY_ALEXAACTIVITYHANDLER_H

#include <AVSCommon/SDKInterfaces/ExternalFocusMediatorInterface.h>
#include <AVSCommon/Utils/Threading/Executor.h>
#include <MultiAgentExperience/Activity/ActivityHandlerInterface.h>

#include <future>
#include <utility>
#include <vector>

#include "MultiAgentExperience/AlexaAdapter/Mediator/MAXFocusMediatorCleanupCallback.h"
#include "MultiAgentExperience/AlexaAdapter/Control/StopControlFactory.h"
#include "MultiAgentExperience/AlexaAdapter/Utils/ConversionUtils.h"
#include "MultiAgentExperience/AlexaAdapter/Utils/FocusResult.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace activity {

class AlexaActivityHandler : public ::multiAgentExperience::activity::ActivityHandlerInterface {
public:
    AlexaActivityHandler(
            ::multiAgentExperience::activity::ActivityType activityType,
            std::string focusRequestId,
            std::shared_ptr<std::promise<utils::FocusResult>> grantedPromise,
            std::weak_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface> mediatorCallbacks,
            std::shared_ptr<mediator::MAXFocusMediatorCleanupCallback> cleanupCallback) :
            m_activityType{activityType},
            m_focusRequestId{std::move(focusRequestId)},
            m_resolved{false},
            m_released{false},
            m_granted{false},
            m_grantedPromise{std::move(grantedPromise)},
            m_mediatorCallbacks{std::move(mediatorCallbacks)},
            m_executor{},
            m_cleanupCallback{std::move(cleanupCallback)} {
    }

    void onDenied() final;

    void onGranted(
            std::shared_ptr<::multiAgentExperience::activity::ActivityControllerInterface> activityController,
            std::shared_ptr<::multiAgentExperience::control::ControlRegistryInterface> controlRegistry,
            std::shared_ptr<::multiAgentExperience::experience::ExperienceControllerInterface> experienceController) final;

    void onFocusStateChange(
            ::multiAgentExperience::activity::ActivityFocus focus,
            ::multiAgentExperience::activity::MixingBehavior behavior) final;

    void onStop() final;

    void release();

private:
    ::multiAgentExperience::activity::ActivityType m_activityType;
    std::string m_focusRequestId;
    std::atomic_bool m_resolved;
    std::atomic_bool m_released;
    bool m_granted;
    std::shared_ptr<std::promise<utils::FocusResult>> m_grantedPromise;
    std::weak_ptr<alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface> m_mediatorCallbacks;
    alexaClientSDK::avsCommon::utils::threading::Executor m_executor;
    std::shared_ptr<mediator::MAXFocusMediatorCleanupCallback> m_cleanupCallback;
};

} // namespace activity
} // namespace multiAgentExperience
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ACTIVITY_ALEXAACTIVITYHANDLER_H
