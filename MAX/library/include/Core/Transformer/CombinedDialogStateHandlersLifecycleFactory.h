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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_COMBINEDDIALOGSTATEHANDLERSLIFECYCLEFACTORY_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_COMBINEDDIALOGSTATEHANDLERSLIFECYCLEFACTORY_H_

#include <memory>

#include <MultiAgentExperience/Dialog/DialogControllerInterface.h>
#include <MultiAgentExperience/Actor/ActorId.h>

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
