/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/Proxy/Experience/StaticExperienceManagerProxy.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace experience {

static const std::string MODULE_TAG("StaticExperienceManagerProxy");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

StaticExperienceManagerProxy::StaticExperienceManagerProxy(
    multiAgentExperience::ipc::messaging::Reference reference,
    std::shared_ptr<transport::MessageSender> sender):
        MaxIpcComponentsBaseProxy(std::move(reference), transport::MaxApiType::STATIC_EXPERIENCE_MANAGER, std::move(sender)) {}

void StaticExperienceManagerProxy::addStaticExperience(
    const ::multiAgentExperience::experience::ExperienceId& experienceId, const unsigned int priority) {
    LX(DEBUG0, "experienceId: " + experienceId.get());

    auto message = multiAgentExperience::ipc::messaging::createMessage(
      m_reference,
      models::experience::StaticExperienceManagerFunctions::ADD_STATIC_EXPERIENCE,
      multiAgentExperience::ipc::messaging::StringIntTuplePayload(experienceId.get(), priority)
    );

    m_sender->send(message);
}

void StaticExperienceManagerProxy::removeStaticExperience(
    const ::multiAgentExperience::experience::ExperienceId& experienceId) {
    LX(DEBUG0, "experienceId: " + experienceId.get());

    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::experience::StaticExperienceManagerFunctions::REMOVE_STATIC_EXPERIENCE,
        multiAgentExperience::ipc::messaging::StringPayload(experienceId.get())
    );

    m_sender->send(message);
}

void StaticExperienceManagerProxy::removeAllStaticExperiences() {
    LX(DEBUG0, "");
    auto message = multiAgentExperience::ipc::messaging::createMessage(
      m_reference,
      models::experience::StaticExperienceManagerFunctions::REMOVE_ALL_STATIC_EXPERIENCES,
      multiAgentExperience::ipc::messaging::VoidPayload()
    );

    m_sender->send(message);
}

} // namespace experience
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience