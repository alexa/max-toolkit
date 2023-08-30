/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/


#include "Core/Transformer/ControlStoreObserverTransformer.h"

#include <sstream>

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Core/Transformer/TransformerUtils.h"

#include "Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

static const std::string MODULE_TAG("ControlStoreObserverTransformer");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

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
        std::stringstream ss;
        ss << "ControlObserverInterface::onControlChange called. details:"
           << " controlTypes=" << multiAgentExperience::library::utils::toString(controlTypes);
        LX(DEBUG0, ss.str());
        observer->onControlChange(controlTypes);
    } else {
        m_weakReferenceBrokenCallback->onBroken(shared_from_this());
    }
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
