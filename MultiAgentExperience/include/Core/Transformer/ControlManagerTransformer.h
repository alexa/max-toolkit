/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/


#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_CONTROLMANAGERTRANSFORMER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_CONTROLMANAGERTRANSFORMER_H_

#include "MultiAgentExperience/Control/ControlManagerInterface.h"
#include "MultiAgentExperience/Actor/ActorId.h"

#include "Activity/ActivityManager.h"
#include "Control/ControlStore.h"

#include <memory>

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class ControlManagerTransformer : public multiAgentExperience::control::ControlManagerInterface {
public:
    ControlManagerTransformer(
        const multiAgentExperience::actor::ActorId id,
        std::shared_ptr<multiAgentExperience::library::control::ControlStore> controlStore,
        std::shared_ptr<multiAgentExperience::library::activity::ActivityManager> activityManager);

    void addObserver(std::weak_ptr<multiAgentExperience::control::ControlObserverInterface> observer) override;

    void clearObservers() override;

    void stopAllAlerts() override;

private:
    const multiAgentExperience::actor::ActorId m_id;
    std::shared_ptr<multiAgentExperience::library::control::ControlStore> m_controlStore;
    std::shared_ptr<multiAgentExperience::library::activity::ActivityManager> m_activityManager;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_CONTROLMANAGERTRANSFORMER_H_
