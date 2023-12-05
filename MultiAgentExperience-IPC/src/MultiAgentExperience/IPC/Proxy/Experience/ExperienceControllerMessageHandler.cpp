/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/Proxy/Experience/ExperienceControllerMessageHandler.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "MultiAgentExperience/IPC/Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace experience {

static const std::string MODULE_TAG("ExperienceControllerMessageHandler");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ExperienceControllerMessageHandler::ExperienceControllerMessageHandler(
    const multiAgentExperience::ipc::messaging::Reference& reference,
    std::shared_ptr<::multiAgentExperience::experience::ExperienceControllerInterface> experienceController):
        multiAgentExperience::ipc::transport::MessageHandler(reference),
        m_experienceController{std::move(experienceController)} {}

void ExperienceControllerMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::experience::ExperienceControllerFunctions,
    multiAgentExperience::ipc::messaging::StringPayload>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    if (models::experience::ExperienceControllerFunctions::START_EXPERIENCE == message.getFunction()) {
        auto experienceId = message.getPayload().m_value;
        auto experience = multiAgentExperience::experience::ExperienceId(experienceId);
        m_experienceController->startExperience(experience);
    } else {
        LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

void ExperienceControllerMessageHandler::handle(
    const multiAgentExperience::ipc::messaging::Message<models::experience::ExperienceControllerFunctions,
    multiAgentExperience::ipc::messaging::VoidPayload>& message) {
    LX(DEBUG0, ipc::utils::toString(message.getFunction()));

    if (models::experience::ExperienceControllerFunctions::END_EXPERIENCE == message.getFunction()) {
        m_experienceController->endExperience();
    } else if (models::experience::ExperienceControllerFunctions::INVALIDATE == message.getFunction()) {
        m_experienceController->invalidate();
    } else {
        LX(ERROR, "Wrong function passed: " + ipc::utils::toString(message.getFunction()));
    }
}

} // namespace experience
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience