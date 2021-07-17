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


#ifndef MULTIAGENTEXPERIENCE_CONTROLOBSERVERREFERENCEBROKENCALLBACK_H
#define MULTIAGENTEXPERIENCE_CONTROLOBSERVERREFERENCEBROKENCALLBACK_H

#include "ControlStoreObserverTransformer.h"
#include "WrappedWeakReferenceBrokenCallbackInterface.h"

#include "Control/ControlStore.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class ControlObserverReferenceBrokenCallback
        : public WrappedWeakReferenceBrokenCallbackInterface<ControlStoreObserverTransformer> {
public:
    ControlObserverReferenceBrokenCallback(
        std::shared_ptr<multiAgentExperience::library::control::ControlStore> controlStore) :
            m_controlStore{controlStore} {
    }

    void onBroken(std::shared_ptr<ControlStoreObserverTransformer> wrappingReference) override {
        if (auto store = m_controlStore.lock()) {
            store->removeObserver(wrappingReference);
        }
    }

private:
    std::weak_ptr<multiAgentExperience::library::control::ControlStore> m_controlStore;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTIAGENTEXPERIENCE_CONTROLOBSERVERREFERENCEBROKENCALLBACK_H
