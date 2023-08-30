/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Core/Transformer/CombinedDialogStateHandlersLifecycleFactory.h"

#include "Core/Transformer/CombinedDialogStateHandlersLifecycle.h"

#include "Experience/ExperienceController.h"
#include "Experience/ExperienceManager.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

CombinedDialogStateHandlersLifecycleFactory::CombinedDialogStateHandlersLifecycleFactory(
    std::shared_ptr<DialogStateHandlerRegistry> dialogStateHandlerRegistry,
    std::shared_ptr<library::experience::ExperienceManager> experienceManager) :
        m_dialogStateHandlerRegistry{dialogStateHandlerRegistry},
        m_experienceManager{experienceManager} {
}

std::shared_ptr<CombinedDialogStateHandlersLifecycle> CombinedDialogStateHandlersLifecycleFactory::create(
    const multiAgentExperience::actor::ActorId& id,
    const activity::ActivityID dialogActivityId,
    std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> dialogController) {
    auto experienceController =
        std::dynamic_pointer_cast<multiAgentExperience::library::experience::ExperienceController>(m_experienceManager->getController(id));
    experienceController->setExperienceControllerActivityId(dialogActivityId);

    return std::make_shared<CombinedDialogStateHandlersLifecycle>(
        m_dialogStateHandlerRegistry, dialogController, experienceController);
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
