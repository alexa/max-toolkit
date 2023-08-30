/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <MultiAgentExperience/Utils/Logger/Logger.h>
#include <MultiAgentExperience/Application/MAXBuilder.h>

#include "Application/MAX.h"

namespace multiAgentExperience {
namespace application {

MAXBuilder::MAXBuilder():
    m_highPriorityCrossAgentBargeInPolicy{HighPriorityCrossAgentBargeInPolicy::NOT_SUPPORTED},
    m_normalPriorityCrossAgentBargeInPolicy{NormalPriorityCrossAgentBargeInPolicy::NOT_SUPPORTED},
    m_activitySchedulingPolicyMap{{
        {multiAgentExperience::activity::ActivityType::COMMUNICATION, ActivitySchedulingPolicy::REPLACE},
        {multiAgentExperience::activity::ActivityType::ALERTS, ActivitySchedulingPolicy::REPLACE},
        {multiAgentExperience::activity::ActivityType::NOTIFICATIONS, ActivitySchedulingPolicy::REPLACE},
        {multiAgentExperience::activity::ActivityType::CONTENT, ActivitySchedulingPolicy::REPLACE}}} {
}

MAXBuilder& MAXBuilder::setIntegratorActorId(const actor::ActorId& integratorActorId) {
    m_integratorActorId = integratorActorId;
    return *this;
}

MAXBuilder& MAXBuilder::setLogger(std::shared_ptr<multiAgentExperience::utils::Log> logger) {
    m_logger = logger;
    return *this;
}

MAXBuilder& MAXBuilder::setLogComponentName(const std::string& logComponentName) {
    m_logComponentName = logComponentName;
    return *this;
}

MAXBuilder& MAXBuilder::withHighPriorityCrossAgentBargeIn(
    const HighPriorityCrossAgentBargeInPolicy& highPriorityCrossAgentBargeInPolicy) {
    m_highPriorityCrossAgentBargeInPolicy = highPriorityCrossAgentBargeInPolicy;
    return *this;
}

MAXBuilder& MAXBuilder::withNormalPriorityCrossAgentBargeIn(
    const NormalPriorityCrossAgentBargeInPolicy& normalPriorityCrossAgentBargeInPolicy) {
    m_normalPriorityCrossAgentBargeInPolicy = normalPriorityCrossAgentBargeInPolicy;
    return *this;
}

MAXBuilder& MAXBuilder::setActivitySchedulingPolicy(
    const multiAgentExperience::activity::ActivityType& activityType,
    const multiAgentExperience::application::ActivitySchedulingPolicy& activitySchedulingPolicy) {
    m_activitySchedulingPolicyMap[activityType] = activitySchedulingPolicy;
    return *this;
}

std::shared_ptr<multiAgentExperience::application::MAXInterface> MAXBuilder::build() {

    if (m_integratorActorId.get().empty()) {
        m_integratorActorId = multiAgentExperience::actor::ActorId("DEFAULT_INTEGRATOR_ID");
    }

    if (!m_logger) {
        m_logger = std::make_shared<multiAgentExperience::logger::Logger>();
        m_logger->setLogLevel(multiAgentExperience::utils::Log::Level::DEBUG3);
    }

    if (m_logComponentName.empty()) {
        m_logComponentName = "MAX_LIB";
    }

    multiAgentExperience::logger::setLoggerComponentName(m_logComponentName);
    multiAgentExperience::logger::setLoggerInstance(m_logger);

    return library::application::MAX::create(
        m_integratorActorId,
        m_highPriorityCrossAgentBargeInPolicy,
        m_normalPriorityCrossAgentBargeInPolicy,
        m_activitySchedulingPolicyMap);
}

}  // namespace application
}  // namespace multiAgentExperience