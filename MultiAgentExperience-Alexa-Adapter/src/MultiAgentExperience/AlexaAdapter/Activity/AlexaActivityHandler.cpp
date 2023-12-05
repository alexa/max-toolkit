/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/AlexaAdapter/Activity/AlexaActivityHandler.h"

#include "AVSCommon/Utils/Logger/Logger.h"
#include "MultiAgentExperience/AlexaAdapter/Alexa/AlexaExperienceIds.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace activity {

static const std::string TAG("AlexaActivityHandler");
#define LX(event) alexaClientSDK::avsCommon::utils::logger::LogEntry(TAG, event)

void AlexaActivityHandler::onDenied()  {
    ACSDK_DEBUG5(LX(__func__));
    auto expected = false;
    if (std::atomic_compare_exchange_strong(&m_resolved, &expected, true)) {
        m_granted = false;
        m_grantedPromise->set_value(utils::FocusResult{std::errc::operation_not_permitted}); //TODO: strange clang error
        (*m_cleanupCallback)();
    }
}

void AlexaActivityHandler::onGranted(
        std::shared_ptr<::multiAgentExperience::activity::ActivityControllerInterface> activityController,
        std::shared_ptr<::multiAgentExperience::control::ControlRegistryInterface> controlRegistry,
        std::shared_ptr<::multiAgentExperience::experience::ExperienceControllerInterface> experienceController)  {
    ACSDK_DEBUG5(LX(__func__));
    switch (m_activityType) {
        case ::multiAgentExperience::activity::ActivityType::COMMUNICATION:
            experienceController->startExperience(alexa::AlexaExperienceIds::COMMUNICATIONS);
            break;
        case ::multiAgentExperience::activity::ActivityType::ALERTS:
            experienceController->startExperience(alexa::AlexaExperienceIds::ALERTS);
        case ::multiAgentExperience::activity::ActivityType::CONTENT:
            controlRegistry->update(control::createStopControl(activityController));
            break;
        default:
            break;
    }
}

void AlexaActivityHandler::onFocusStateChange(
        ::multiAgentExperience::activity::ActivityFocus focus,
        ::multiAgentExperience::activity::MixingBehavior behavior) {
    ACSDK_DEBUG5(LX(__func__));
    auto convertedFocus = utils::convertActivityFocusToExternalFocusState(focus);
    auto convertedBehavior = utils::convertMixingBehaviorToExternalMixingBehavior(behavior);
    auto finalFocus =
            alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusMediatorFocus(
                    convertedFocus,
                    convertedBehavior);
    auto expected = false;
    if (std::atomic_compare_exchange_strong(&m_resolved, &expected, true)) {
        m_granted = true;
        m_grantedPromise->set_value(utils::FocusResult{convertedFocus, convertedBehavior});
    } else if (m_granted) {
        if (auto mediatorCallbacks = m_mediatorCallbacks.lock()) {
            auto promise = mediatorCallbacks->changeFocusState(m_focusRequestId, finalFocus);
            promise.await();
        }

        //TODO: likely want to implement an edge case here, where if the focus change is rejected, stop the
        // corresponding activity with MAX. This is assumed to only happen if Alexa lost track of the activity
        // internally without informing the EFM. This is likely a bug, but we could be robust to this.
    }
}

void AlexaActivityHandler::onStop() {
    ACSDK_DEBUG5(LX(__func__));

    if (m_resolved && m_granted && !m_released) {

        /*
         * Cleanup the entries in the focusRequestBuffer (and other data structures) for the focusRequestId associated
         * with this AlexaActivityHandler object.
         *
         * We only want to clean up, if the activity was stopped by MAX. If the activity was stopped by Alexa,
         * the MAXFocusMediator::onFocusRelease will ensure clean up. If stopped by Alexa, m_released is set to true
         * and hence, this code block is not executed.
         */
        ACSDK_DEBUG5(LX(__func__).m("Invoking the CleanupCallback"));
        (*m_cleanupCallback)();

        if (auto mediatorCallbacks = m_mediatorCallbacks.lock()) {
            auto promise = mediatorCallbacks->mediatorReleaseFocus(m_focusRequestId);
            promise.await();
        }

        //TODO: Determine if there are edge cases here to handle.
    }
}

void AlexaActivityHandler::release() {
    m_released = true;
}

} // namespace activity
} // namespace multiAgentExperience
} // namespace alexaClientSDK









