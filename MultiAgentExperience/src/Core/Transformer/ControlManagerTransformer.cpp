/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Core/Transformer/ControlManagerTransformer.h"

#include <sstream>

#include "Core/Transformer/ControlStoreObserverTransformer.h"
#include "Core/Transformer/ControlObserverReferenceBrokenCallback.h"

#include "Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

static const std::string MODULE_TAG("ControlManagerTransformer");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ControlManagerTransformer::ControlManagerTransformer(
    const multiAgentExperience::actor::ActorId id,
    std::shared_ptr<multiAgentExperience::library::control::ControlStore> controlStore,
    std::shared_ptr<multiAgentExperience::library::activity::ActivityManager> activityManager) :
        m_id{id},
        m_controlStore{controlStore},
        m_activityManager{activityManager} {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(id);
    LX(DEBUG0, ss.str());
}

void multiAgentExperience::library::core::transformer::ControlManagerTransformer::addObserver(
    std::weak_ptr<multiAgentExperience::control::ControlObserverInterface> observer) {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_id);
    LX(DEBUG0, ss.str());

    auto brokenReferenceCallback = std::make_shared<ControlObserverReferenceBrokenCallback>(m_controlStore);
    auto controlStoreObserver = std::make_shared<ControlStoreObserverTransformer>(observer, brokenReferenceCallback);
    m_controlStore->addObserver(controlStoreObserver);
}

void multiAgentExperience::library::core::transformer::ControlManagerTransformer::clearObservers() {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_id);
    LX(DEBUG0, ss.str());

    m_controlStore->clearObservers();
}

void multiAgentExperience::library::core::transformer::ControlManagerTransformer::stopAllAlerts() {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_id);
    LX(DEBUG0, ss.str());

    m_activityManager->stopAllAlerts();
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
