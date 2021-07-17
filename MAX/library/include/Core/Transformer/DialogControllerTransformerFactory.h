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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGCONTROLLERTRANSFORMERFACTORY_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGCONTROLLERTRANSFORMERFACTORY_H_

#include <memory>

#include "Control/ControlInvokerFactory.h"
#include "DialogControllerTransformer.h"
#include "Dialog/DialogController.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class DialogControllerTransformerFactory {
public:
    DialogControllerTransformerFactory(std::shared_ptr<library::control::ControlInvokerFactory> controlInvokerFactory);

    virtual ~DialogControllerTransformerFactory() = default;

    virtual std::shared_ptr<DialogControllerTransformer> create(
        std::shared_ptr<library::dialog::DialogController> dialogController);

private:
    std::shared_ptr<library::control::ControlInvokerFactory> m_controlInvokerFactory;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGCONTROLLERTRANSFORMERFACTORY_H_
