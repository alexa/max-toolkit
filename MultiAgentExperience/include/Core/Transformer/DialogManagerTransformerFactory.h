/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGMANAGERTRANSFORMERFACTORY_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGMANAGERTRANSFORMERFACTORY_H_

#include <memory>

#include "Dialog/DialogManager.h"
#include "DialogControllerTransformerFactory.h"
#include "DialogManagerTransformer.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class DialogManagerTransformerFactory {
public:
    DialogManagerTransformerFactory(
        std::shared_ptr<library::dialog::DialogManager> dialogManager,
        std::shared_ptr<library::experience::ExperienceManager> experienceManager,
        std::shared_ptr<DialogControllerTransformerFactory> dialogControllerTransformerFactory);

    std::shared_ptr<DialogManagerTransformer> create(const multiAgentExperience::actor::ActorId& actorId);

private:
    std::shared_ptr<library::dialog::DialogManager> m_dialogManager;
    std::shared_ptr<library::experience::ExperienceManager> m_experienceManager;
    std::shared_ptr<DialogControllerTransformerFactory> m_dialogControllerTransformerFactory;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGMANAGERTRANSFORMERFACTORY_H_
