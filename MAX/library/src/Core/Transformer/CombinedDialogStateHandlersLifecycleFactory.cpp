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

#include "Core/Transformer/CombinedDialogStateHandlersLifecycleFactory.h"

#include "Core/Transformer/CombinedDialogStateHandlersLifecycle.h"

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
    std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> dialogController) {
    return std::make_shared<CombinedDialogStateHandlersLifecycle>(
        m_dialogStateHandlerRegistry, dialogController, m_experienceManager->getController(id));
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
