/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
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
