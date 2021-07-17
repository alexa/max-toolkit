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


#include "Core/Transformer/ControlStoreObserverTransformer.h"

#include "Core/Transformer/TransformerUtils.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

ControlStoreObserverTransformer::ControlStoreObserverTransformer(
    std::weak_ptr<multiAgentExperience::control::ControlObserverInterface> observer,
    std::shared_ptr<WrappedWeakReferenceBrokenCallbackInterface<ControlStoreObserverTransformer>>
        weakReferenceBrokenCallback) :
        m_observer{observer},
        m_weakReferenceBrokenCallback{weakReferenceBrokenCallback} {
}

void ControlStoreObserverTransformer::onControlsUpdated(
    const std::unordered_set<multiAgentExperience::library::control::ControlName>& controlNames) {
    auto controlTypes = TransformerUtils::convertSetOfControlNamesToControlTypes(controlNames);
    if (auto observer = m_observer.lock()) {
        observer->onControlChange(controlTypes);
    } else {
        m_weakReferenceBrokenCallback->onBroken(shared_from_this());
    }
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
