/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Core/Transformer/ActivityRequestTransformer.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Core/Transformer/ActivityRequestTransformerFactory.h"
#include "Core/Transformer/ActivityTransformer.h"
#include "MultiAgentExperience/Activity/ActivityHandlerInterface.h"


namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

static const std::string MODULE_TAG("ActivityRequestTransformer");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ActivityRequestTransformer::ActivityRequestTransformer(
    library::activity::ActivityType activityType,
    std::shared_ptr<ActivityTransformer> activity,
    std::shared_ptr<multiAgentExperience::activity::ActivityHandlerInterface> activityHandlerInterface,
    multiAgentExperience::library::activity::MixabilityType mixabilityType) :
        library::activity::ActivityRequest(activityType, activity, mixabilityType),
        m_activityHandlerInterface{activityHandlerInterface} {
}

void ActivityRequestTransformer::onGranted() {
}

void ActivityRequestTransformer::onDenied() {
    LX(DEBUG0, "ActivityHandlerInterface::onDenied called")
    m_activityHandlerInterface->onDenied();
}

void ActivityRequestTransformer::onRemoved() {
}

void ActivityRequestTransformer::onFinished() {
}

void ActivityRequestTransformer::onWaiting() {
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
