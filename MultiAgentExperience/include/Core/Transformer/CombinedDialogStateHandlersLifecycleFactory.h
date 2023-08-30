/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_COMBINEDDIALOGSTATEHANDLERSLIFECYCLEFACTORY_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_COMBINEDDIALOGSTATEHANDLERSLIFECYCLEFACTORY_H_

#include <memory>

#include <MultiAgentExperience/Dialog/DialogControllerInterface.h>
#include <MultiAgentExperience/Actor/ActorId.h>

#include "Activity/ActivityID.h"
#include "CombinedDialogStateHandlersLifecycle.h"
#include "DialogStateHandlerRegistry.h"
#include "Experience/ExperienceManager.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class CombinedDialogStateHandlersLifecycleFactory {
public:
    CombinedDialogStateHandlersLifecycleFactory(
        std::shared_ptr<DialogStateHandlerRegistry> dialogStateHandlerRegistry,
        std::shared_ptr<library::experience::ExperienceManager> experienceManager);

    virtual ~CombinedDialogStateHandlersLifecycleFactory() = default;

    virtual std::shared_ptr<CombinedDialogStateHandlersLifecycle> create(
        const multiAgentExperience::actor::ActorId& id,
        const activity::ActivityID dialogActivityId,
        std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> dialogController);

private:
    std::shared_ptr<DialogStateHandlerRegistry> m_dialogStateHandlerRegistry;
    std::shared_ptr<library::experience::ExperienceManager> m_experienceManager;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_COMBINEDDIALOGSTATEHANDLERSLIFECYCLEFACTORY_H_
