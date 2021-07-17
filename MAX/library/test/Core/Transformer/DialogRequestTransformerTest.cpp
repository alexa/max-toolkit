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

#include "Core/Transformer/DialogRequestTransformer.h"

#include "Core/Transformer/CombinedDialogStateHandlersLifecycleFactory.h"
#include "Core/Transformer/DialogLifecycleTransformer.h"
#include "Core/Transformer/DialogControllerTransformerFactory.h"
#include "Core/Transformer/DialogStateHandlerRegistry.h"

#include <gmock/gmock.h>
#include <memory>

#include "Control/Mocks/MockControlInvokerFactory.h"

#include "Mocks/MockDialogRequestInterface.h"
#include "Mocks/MockExperienceManagerInterface.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {
namespace test {

using namespace multiAgentExperience::dialog::test;
using testing::_;

class DialogRequestTransformerTest : public ::testing::Test {
protected:
    std::shared_ptr<MockDialogRequestInterface> m_mockDialogRequestInterface;
    std::shared_ptr<DialogRequestTransformer> m_dialogRequestTransformer;

    virtual void SetUp() override {
        m_mockDialogRequestInterface = std::make_shared<testing::StrictMock<MockDialogRequestInterface>>();
        auto experienceManager =
            std::make_shared<testing::NiceMock<multiAgentExperience::experience::test::MockExperienceManager>>();
        auto dialogStateHandlerRegistry = std::make_shared<DialogStateHandlerRegistry>();
        auto dialogLifecycleFactory = std::make_shared<CombinedDialogStateHandlersLifecycleFactory>(
            dialogStateHandlerRegistry, experienceManager);

        auto controlFactory = std::make_shared<testing::NiceMock<control::test::MockControlInvokerFactory>>();
        auto dialogControllerTransformerFactory =
            std::make_shared<transformer::DialogControllerTransformerFactory>(controlFactory);

        auto dialogLifecycleTransformer = std::make_shared<DialogLifecycleTransformer>(
            multiAgentExperience::actor::ActorId("test"),
            m_mockDialogRequestInterface,
            dialogLifecycleFactory,
            dialogControllerTransformerFactory);

        m_dialogRequestTransformer = std::make_shared<DialogRequestTransformer>(dialogLifecycleTransformer);
    }
};

TEST_F(DialogRequestTransformerTest, test_on_granted_does_nothing) {
    m_dialogRequestTransformer->onGranted();
}

TEST_F(DialogRequestTransformerTest, test_on_denied_denies_a_dialog_request) {
    EXPECT_CALL(*m_mockDialogRequestInterface, onDenied(_));
    m_dialogRequestTransformer->onDenied();
}

}  // namespace test
}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
