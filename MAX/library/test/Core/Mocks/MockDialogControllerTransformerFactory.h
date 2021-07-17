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

#ifndef VII_CORE_TRANSFORMER_MOCKDIALOGCONTROLLERTRANSFORMERFACTORY_H
#define VII_CORE_TRANSFORMER_MOCKDIALOGCONTROLLERTRANSFORMERFACTORY_H

#include "Core/Transformer/DialogControllerTransformerFactory.h"
#include "Core/Transformer/DialogControllerTransformer.h"

#include "Dialog/DialogController.h"

#include <gmock/gmock.h>
#include <memory>

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {
namespace test {

class MockDialogControllerTransformerFactory : public DialogControllerTransformerFactory {
public:
    MockDialogControllerTransformerFactory() : DialogControllerTransformerFactory(nullptr) {
    }
    MOCK_METHOD1(create, std::shared_ptr<DialogControllerTransformer>(std::shared_ptr<dialog::DialogController>));
};

}  // namespace test
}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // VII_CORE_TRANSFORMER_MOCKDIALOGCONTROLLERTRANSFORMERFACTORY_H
