/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_ACTIVITYTRANSFORMER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_ACTIVITYTRANSFORMER_H_

#include <memory>

#include <MultiAgentExperience/Activity/ActivityFocus.h>
#include <MultiAgentExperience/Activity/ActivityHandlerInterface.h>
#include <MultiAgentExperience/Actor/ActorId.h>
#include <MultiAgentExperience/Control/ControlRegistryInterface.h>
#include <MultiAgentExperience/Experience/ExperienceControllerInterface.h>

#include "Activity/ActivityManager.h"
#include "Control/ControlRegistry.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class ActivityTransformer : public multiAgentExperience::library::activity::Activity {
public:
    ActivityTransformer(
        const actor::ActorId& actorId,
        std::shared_ptr<multiAgentExperience::library::activity::ActivityManager> activityManager,
        std::shared_ptr<multiAgentExperience::activity::ActivityHandlerInterface> activityHandlerInterface,
        std::shared_ptr<multiAgentExperience::experience::ExperienceControllerInterface> experienceControl);

    /// @name Activity method overrides.
    /// @{
    void onControlRegistryAvailable(std::shared_ptr<library::control::ControlRegistry> controlRegistry) override;
    void onForeground() override;
    void onBackground(multiAgentExperience::library::activity::MixingBehavior behavior) override;
    void onStop() override;
    actor::ActorId getActorId() const override;
    /// @}

    void associateActivityIdWithExperienceController(std::size_t id);

private:
    void updateFocus(
        multiAgentExperience::activity::ActivityFocus focus,
        multiAgentExperience::library::activity::MixingBehavior behavior);

    bool m_wasGranted;
    const actor::ActorId m_actorId;
    std::weak_ptr<multiAgentExperience::library::activity::ActivityManager> m_activityManager;
    std::shared_ptr<multiAgentExperience::control::ControlRegistryInterface> m_controlRegistryInterface;
    std::shared_ptr<multiAgentExperience::activity::ActivityHandlerInterface> m_activityHandlerInterface;
    std::shared_ptr<multiAgentExperience::experience::ExperienceControllerInterface> m_experienceControlInterface;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_ACTIVITYTRANSFORMER_H_
