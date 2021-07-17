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


#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_CONTROL_CONTROLSTOREOBSERVERTRANSFORMER_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_CONTROL_CONTROLSTOREOBSERVERTRANSFORMER_H_

#include <unordered_set>
#include "Control/ControlStoreObserverInterface.h"

#include "MultiAgentExperience/Control/ControlObserverInterface.h"

#include "WrappedWeakReferenceBrokenCallbackInterface.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class ControlStoreObserverTransformer
        : public multiAgentExperience::library::control::ControlStoreObserverInterface
        , public std::enable_shared_from_this<ControlStoreObserverTransformer> {
public:
    ControlStoreObserverTransformer(
        std::weak_ptr<multiAgentExperience::control::ControlObserverInterface> observer,
        std::shared_ptr<WrappedWeakReferenceBrokenCallbackInterface<ControlStoreObserverTransformer>>
            weakReferenceBrokenCallback);
    void onControlsUpdated(
        const std::unordered_set<multiAgentExperience::library::control::ControlName>& controlNames) override;

private:
    std::weak_ptr<multiAgentExperience::control::ControlObserverInterface> m_observer;
    std::shared_ptr<WrappedWeakReferenceBrokenCallbackInterface<ControlStoreObserverTransformer>>
        m_weakReferenceBrokenCallback;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_CONTROL_CONTROLSTOREOBSERVERTRANSFORMER_H_
