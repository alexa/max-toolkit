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


#include "Core/Transformer/ControlManagerTransformer.h"

#include "Core/Transformer/ControlStoreObserverTransformer.h"
#include "Core/Transformer/ControlObserverReferenceBrokenCallback.h"

#include "Utils/Logger/Logger.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

static const std::string MODULE_TAG("ControlManagerTransformer");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ControlManagerTransformer::ControlManagerTransformer(
    const multiAgentExperience::actor::ActorId id,
    std::shared_ptr<multiAgentExperience::library::control::ControlStore> controlStore) :
        m_id{id},
        m_controlStore{controlStore} {
}

void multiAgentExperience::library::core::transformer::ControlManagerTransformer::addObserver(
    std::weak_ptr<multiAgentExperience::control::ControlObserverInterface> observer) {
    LX(DEBUG3, m_id.get());
    auto brokenReferenceCallback = std::make_shared<ControlObserverReferenceBrokenCallback>(m_controlStore);
    auto controlStoreObserver = std::make_shared<ControlStoreObserverTransformer>(observer, brokenReferenceCallback);
    m_controlStore->addObserver(controlStoreObserver);
}

void multiAgentExperience::library::core::transformer::ControlManagerTransformer::clearObservers() {
    LX(DEBUG3, m_id.get());
    m_controlStore->clearObservers();
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
