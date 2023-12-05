/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/Proxy/Experience/StaticExperienceManagerMessageHandler.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace experience {

static const std::string MODULE_TAG("StaticExperienceManagerMessageHandler");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

StaticExperienceManagerMessageHandler::StaticExperienceManagerMessageHandler(
    const multiAgentExperience::ipc::messaging::Reference& reference,
    std::shared_ptr<::multiAgentExperience::experience::StaticExperienceManagerInterface> staticExperienceManager):
        multiAgentExperience::ipc::transport::MessageHandler(reference),
        m_staticExperienceManager{std::move(staticExperienceManager)} {}

void StaticExperienceManagerMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::experience::StaticExperienceManagerFunctions,
    multiAgentExperience::ipc::messaging::StringIntTuplePayload>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    if (models::experience::StaticExperienceManagerFunctions::ADD_STATIC_EXPERIENCE == message.getFunction()) {
        auto experienceId = multiAgentExperience::experience::ExperienceId(message.getPayload().m_value1);
        unsigned int priority = message.getPayload().m_value2;

        m_staticExperienceManager->addStaticExperience(experienceId, priority);
    } else {
        LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

void StaticExperienceManagerMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::experience::StaticExperienceManagerFunctions,
    multiAgentExperience::ipc::messaging::StringPayload>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    if (models::experience::StaticExperienceManagerFunctions::REMOVE_STATIC_EXPERIENCE == message.getFunction()) {
        auto experienceId = multiAgentExperience::experience::ExperienceId(message.getPayload().m_value);
        m_staticExperienceManager->removeStaticExperience(experienceId);
    } else {
        LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

void StaticExperienceManagerMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::experience::StaticExperienceManagerFunctions,
    multiAgentExperience::ipc::messaging::VoidPayload>& message){
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    if (models::experience::StaticExperienceManagerFunctions::REMOVE_ALL_STATIC_EXPERIENCES == message.getFunction()) {
        m_staticExperienceManager->removeAllStaticExperiences();
    } else {
        LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

} // namespace experience
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience