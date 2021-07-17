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


#include "Core/Transformer/ControlInvokerTransformer.h"

#include "Core/Transformer/TransformerUtils.h"

#include "Utils/Logger/Logger.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

static const std::string MODULE_TAG("ControlManagerTransformer");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ControlInvokerTransformer::ControlInvokerTransformer(
    const multiAgentExperience::actor::ActorId id,
    std::shared_ptr<multiAgentExperience::library::control::ControlInvoker> invoker) :
        m_id{id},
        m_invoker{invoker} {
}

void ControlInvokerTransformer::invokeControl(const multiAgentExperience::control::ControlType& controlType) {
    LX(DEBUG3, m_id.get());
    auto controlName = TransformerUtils::convertControlTypeToControlName(controlType);
    m_invoker->invoke(controlName);
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience