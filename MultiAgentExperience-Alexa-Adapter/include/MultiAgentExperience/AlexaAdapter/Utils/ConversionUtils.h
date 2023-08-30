/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_UTILS_CONVERSIONUTILS_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_UTILS_CONVERSIONUTILS_H

#include <iostream>

#include <AVSCommon/AVS/ContentType.h>
#include <AVSCommon/SDKInterfaces/ExternalFocusMediatorCallbackInterface.h>
#include <AVSCommon/Utils/Logger/Logger.h>

#include <MultiAgentExperience/Activity/ActivityFocus.h>
#include <MultiAgentExperience/Activity/ActivityType.h>
#include <MultiAgentExperience/Activity/MixabilityType.h>
#include <MultiAgentExperience/Activity/MixingBehavior.h>

#include "MultiAgentExperience/AlexaAdapter/Dialog/DialogState.h"
#include "MultiAgentExperience/AlexaAdapter/Alexa/AlexaChannelNames.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace utils {

static const std::string TAG("ConversionUtils");
#define LX(event) alexaClientSDK::avsCommon::utils::logger::LogEntry(TAG, event)

inline ::multiAgentExperience::activity::ActivityType convertChannelNameToActivityType(const std::string& channelName) {
    if (channelName == alexa::AlexaChannelNames::COMMUNICATIONS) {
        return ::multiAgentExperience::activity::ActivityType::COMMUNICATION;
    } else if (channelName == alexa::AlexaChannelNames::ALERTS) {
        return ::multiAgentExperience::activity::ActivityType::ALERTS;
    } else if (channelName == alexa::AlexaChannelNames::NOTIFICATION) {
        return ::multiAgentExperience::activity::ActivityType::NOTIFICATIONS;
    } else if (channelName == alexa::AlexaChannelNames::CONTENT) {
        return ::multiAgentExperience::activity::ActivityType::CONTENT;
    } else {
        // TODO:: this is not right
        return ::multiAgentExperience::activity::ActivityType::CONTENT;
    }
}

inline ::multiAgentExperience::activity::MixabilityType
convertContentTypeToMixabilityType(alexaClientSDK::avsCommon::avs::ContentType contentType) {
    switch (contentType) {
        case alexaClientSDK::avsCommon::avs::ContentType::MIXABLE:
            return ::multiAgentExperience::activity::MixabilityType::MIXABLE_RESTRICTED;
        case alexaClientSDK::avsCommon::avs::ContentType::NONMIXABLE:
            return ::multiAgentExperience::activity::MixabilityType::NONMIXABLE;
        case alexaClientSDK::avsCommon::avs::ContentType::NUM_CONTENT_TYPE:
        case alexaClientSDK::avsCommon::avs::ContentType::UNDEFINED:
        default:
            //TODO something
            return ::multiAgentExperience::activity::MixabilityType::MIXABLE_UNRESTRICTED;
    }
}

inline alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusState
convertActivityFocusToExternalFocusState(::multiAgentExperience::activity::ActivityFocus focus) {
    switch(focus) {
        case ::multiAgentExperience::activity::ActivityFocus::FOREGROUND:
            return alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusState::FOREGROUND;
        case ::multiAgentExperience::activity::ActivityFocus::BACKGROUND:
        default: //TODO on default;
            return alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalFocusState::BACKGROUND;
    }
}

inline alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalMixingBehavior
convertMixingBehaviorToExternalMixingBehavior(::multiAgentExperience::activity::MixingBehavior mixingBehavior) {
    switch (mixingBehavior) {
        case ::multiAgentExperience::activity::MixingBehavior::MUST_ATTENUATE:
            ACSDK_DEBUG3(LX("MixingBehavior::MUST_ATTENUATE"));
            return alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalMixingBehavior::MAY_DUCK;
        case ::multiAgentExperience::activity::MixingBehavior::MUST_PAUSE:
            ACSDK_DEBUG3(LX("MixingBehavior::MUST_PAUSE"));
            return alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalMixingBehavior::MUST_PAUSE;
        case ::multiAgentExperience::activity::MixingBehavior::UNRESTRICTED:
            ACSDK_DEBUG3(LX("MixingBehavior::UNRESTRICTED"));
            //TODO: review whether undefined works in this or not. We should not have a immediate use case for UNRESTRICTED, but we should support it.
            return alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalMixingBehavior::UNDEFINED;
        default:
            ACSDK_DEBUG3(LX("default"));
            return alexaClientSDK::avsCommon::sdkInterfaces::ExternalFocusMediatorCallbackInterface::ExternalMixingBehavior::UNDEFINED;
    }
}

} // namespace utils
} // namespace multiAgentExperience
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_UTILS_CONVERSIONUTILS_H
