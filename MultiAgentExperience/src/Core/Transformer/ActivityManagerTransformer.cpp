/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Core/Transformer/ActivityManagerTransformer.h"

#include <sstream>

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Core/Transformer/TransformerUtils.h"
#include "Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

static const std::string MODULE_TAG("ActivityManagerTransformer");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ActivityManagerTransformer::ActivityManagerTransformer(
    const multiAgentExperience::actor::ActorId& id,
    std::shared_ptr<multiAgentExperience::library::activity::ActivityManager> activityManager,
    std::shared_ptr<ActivityRequestTransformerFactory> requestTransformerFactory) :
        m_id{id},
        m_activityManager{activityManager},
        m_requestTransformerFactory{requestTransformerFactory} {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(id);
    LX(DEBUG0, ss.str());
}

ActivityManagerTransformer::~ActivityManagerTransformer() {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_id);
    LX(DEBUG0, ss.str());
    m_activityManager->clearActivitiesForActor(m_id);
}

void ActivityManagerTransformer::request(
    std::shared_ptr<multiAgentExperience::activity::ActivityRequestInterface> request) {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_id)
       << " activityType=" << multiAgentExperience::library::utils::toString(request->getType())
       << " mixabilityType=" << multiAgentExperience::library::utils::toString(request->getMixabilityType());
    LX(DEBUG0, ss.str());

    auto activityRequestTransformer = m_requestTransformerFactory->create(m_id, request);
    m_requestStore.storeTransformedRequest(request, activityRequestTransformer);
    m_activityManager->request(activityRequestTransformer);
}

void ActivityManagerTransformer::stop(
    std::shared_ptr<multiAgentExperience::activity::ActivityRequestInterface> request) {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_id)
       << " activityType=" << multiAgentExperience::library::utils::toString(request->getType())
       << " mixabilityType=" << multiAgentExperience::library::utils::toString(request->getMixabilityType());
    LX(DEBUG0, ss.str());

    auto transformedID = m_requestStore.getTransformedRequestId(request);
    stop(transformedID);
    m_requestStore.cleanupTransformedRequest(request);
}

void ActivityManagerTransformer::stop(multiAgentExperience::library::activity::ActivityRequestID id) {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_id)
       << " activityRequestId=" << id;
    LX(DEBUG0, ss.str());

    if (id > 0) {
        m_activityManager->finish(id);
    } else {
        LX(ERROR, "ActivityRequestId <= 0, unable to stop activity.");
    }
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
