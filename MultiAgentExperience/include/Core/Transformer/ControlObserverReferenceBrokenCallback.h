/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
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
