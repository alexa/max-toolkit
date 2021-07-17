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

#ifndef VII_CORE_TRANSFORMER_MOCKCOMBINEDDIALOGSTATEHANDLERSFACTORY_H
#define VII_CORE_TRANSFORMER_MOCKCOMBINEDDIALOGSTATEHANDLERSFACTORY_H

#include "MultiAgentExperience/Dialog/DialogControllerInterface.h"
#include "Core/Transformer/CombinedDialogStateHandlersLifecycleFactory.h"
#include "Core/Transformer/CombinedDialogStateHandlersLifecycle.h"

#include <gmock/gmock.h>
#include <memory>

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {
namespace test {

class MockCombinedDialogStateHandlersLifecycleFactory : public CombinedDialogStateHandlersLifecycleFactory {
public:
    MockCombinedDialogStateHandlersLifecycleFactory() : CombinedDialogStateHandlersLifecycleFactory(nullptr, nullptr) {
    }

    MOCK_METHOD2(
        create,
        std::shared_ptr<CombinedDialogStateHandlersLifecycle>(
            const multiAgentExperience::actor::ActorId& id,
            std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface>));
};

}  // namespace test
}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // VII_CORE_TRANSFORMER_MOCKCOMBINEDDIALOGSTATEHANDLERSFACTORY_H
