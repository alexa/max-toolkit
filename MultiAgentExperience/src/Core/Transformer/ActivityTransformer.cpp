/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Core/Transformer/ActivityTransformer.h"

#include <sstream>

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Activity/ActivityManager.h"
#include "Core/Transformer/ActivityControllerTransformer.h"
#include "Core/Transformer/ControlRegistryTransformer.h"
#include "Core/Transformer/TransformerUtils.h"
#include "Experience/ExperienceController.h"
#include "MultiAgentExperience/Activity/ActivityHandlerInterface.h"

#include "Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

static const std::string MODULE_TAG("ActivityTransformer");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ActivityTransformer::ActivityTransformer(
    const actor::ActorId& actorId,
    std::shared_ptr<multiAgentExperience::library::activity::ActivityManager> activityManager,
    std::shared_ptr<multiAgentExperience::activity::ActivityHandlerInterface> activityHandlerInterface,
    std::shared_ptr<multiAgentExperience::experience::ExperienceControllerInterface> experienceControl) :
        m_actorId(actorId),
        m_wasGranted{false},
        m_activityManager{activityManager},
        m_controlRegistryInterface{nullptr},
        m_activityHandlerInterface{activityHandlerInterface},
        m_experienceControlInterface{experienceControl} {
}

void ActivityTransformer::associateActivityIdWithExperienceController(std::size_t id) {
    auto transformedExperienceController =
        std::dynamic_pointer_cast<multiAgentExperience::library::experience::ExperienceController>(m_experienceControlInterface);

    std::stringstream ss;
    ss << "ExperienceControllerInterface::setExperienceControllerActivityId called. details:"
       << " activityId=" << id;
    LX(DEBUG0, ss.str());
    transformedExperienceController->setExperienceControllerActivityId(id);
}

void ActivityTransformer::onControlRegistryAvailable(
    std::shared_ptr<multiAgentExperience::library::control::ControlRegistry> controlRegistry) {
    // this is critical, without this value for the id, activities cannot be unscheduled.
    m_controlRegistryInterface = std::make_shared<ControlRegistryTransformer>(getID(), controlRegistry);
}

void ActivityTransformer::onForeground() {
    // We expect an Activity to only receive MixingBehavior::PRIMARY, when it is foregrounded
    updateFocus(multiAgentExperience::activity::ActivityFocus::FOREGROUND,
                multiAgentExperience::library::activity::MixingBehavior::UNRESTRICTED);
}

void ActivityTransformer::onBackground(activity::MixingBehavior behavior) {
    updateFocus(multiAgentExperience::activity::ActivityFocus::BACKGROUND, behavior);
}

void ActivityTransformer::onStop() {
    LX(DEBUG0, "ExperienceControllerInterface::invalidate called.");
    m_experienceControlInterface->invalidate();
    if (m_wasGranted) {
        LX(DEBUG0, "ActivityHandlerInterface::onStop called");
        m_activityHandlerInterface->onStop();
    }
}

void ActivityTransformer::updateFocus(
    multiAgentExperience::activity::ActivityFocus focus,
    multiAgentExperience::library::activity::MixingBehavior behavior) {
    if (!m_wasGranted) {
        m_wasGranted = true;
        auto id = getID();
        std::weak_ptr<multiAgentExperience::library::activity::ActivityManager> activityManagerWeak = m_activityManager;
        auto stopCallback = [activityManagerWeak, id]() {
            if (auto activityManager = activityManagerWeak.lock()) {
                activityManager->finish(id);
            }
        };
        auto activityController = std::make_shared<ActivityControllerTransformer>(stopCallback);

        LX(DEBUG0, "ActivityHandlerInterface::onGranted called");
        m_activityHandlerInterface->onGranted(
            activityController, m_controlRegistryInterface, m_experienceControlInterface);
    }

    // Propagate the focus state and the MixingBehavior back to the Agent
    std::stringstream ss;
    ss << "ActivityHandlerInterface::onFocusStateChange called. details:"
       << " focus=" << multiAgentExperience::library::utils::toString(focus)
       << " mixingBehavior=" << multiAgentExperience::library::utils::toString(behavior);
    LX(DEBUG0, ss.str());
    m_activityHandlerInterface->onFocusStateChange(
        focus,
        TransformerUtils::convertInternalMixingBehaviorToPublicMixingBehavior(behavior));
}

actor::ActorId ActivityTransformer::getActorId() const {
    return m_actorId;
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
