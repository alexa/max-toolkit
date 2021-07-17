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

#include "Core/Transformer/DialogManagerTransformerFactory.h"

#include "Core/Transformer/CombinedDialogStateHandlersLifecycleFactory.h"
#include "Core/Transformer/DialogManagerTransformer.h"
#include "Core/Transformer/DialogStateHandlerRegistry.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

DialogManagerTransformerFactory::DialogManagerTransformerFactory(
    std::shared_ptr<library::dialog::DialogManager> dialogManager,
    std::shared_ptr<library::experience::ExperienceManager> experienceManager,
    std::shared_ptr<DialogControllerTransformerFactory> dialogControllerTransformerFactory) :
        m_dialogManager{dialogManager},
        m_experienceManager{experienceManager},
        m_dialogControllerTransformerFactory{dialogControllerTransformerFactory} {
}

std::shared_ptr<DialogManagerTransformer> DialogManagerTransformerFactory::create(
    const multiAgentExperience::actor::ActorId& actorId) {
    auto dialogStateHandlerRegistry = std::make_shared<DialogStateHandlerRegistry>();

    auto dialogLifecycleFactory =
        std::make_shared<CombinedDialogStateHandlersLifecycleFactory>(dialogStateHandlerRegistry, m_experienceManager);
    return std::make_shared<DialogManagerTransformer>(
        actorId,
        m_dialogManager,
        dialogStateHandlerRegistry,
        m_dialogControllerTransformerFactory,
        dialogLifecycleFactory);
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
