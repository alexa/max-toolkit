/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/IPC/Proxy/Experience/ExperienceControllerProxy.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace experience {

static const std::string MODULE_TAG("ExperienceControllerProxy");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ExperienceControllerProxy::ExperienceControllerProxy(
    multiAgentExperience::ipc::messaging::Reference reference,
    std::shared_ptr<transport::MessageSender> sender) :
        MaxIpcComponentsBaseProxy(std::move(reference), transport::MaxApiType::EXPERIENCE_CONTROLLER, std::move(sender)) {
}

void ExperienceControllerProxy::startExperience(const multiAgentExperience::experience::ExperienceId& experience) {
    LX(DEBUG0, "");
    auto experienceId = experience.get();
    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::experience::ExperienceControllerFunctions::START_EXPERIENCE,
        multiAgentExperience::ipc::messaging::StringPayload(experienceId)
                                                         );
    m_sender->send(message);
}

void ExperienceControllerProxy::endExperience() {
    LX(DEBUG0, "");
    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::experience::ExperienceControllerFunctions::END_EXPERIENCE,
        multiAgentExperience::ipc::messaging::VoidPayload()
                                                         );
    m_sender->send(message);
}

void ExperienceControllerProxy::invalidate() {
    LX(DEBUG0, "");
    auto message = multiAgentExperience::ipc::messaging::createMessage(
        m_reference,
        models::experience::ExperienceControllerFunctions::INVALIDATE,
        multiAgentExperience::ipc::messaging::VoidPayload()
                                                         );
    m_sender->send(message);
}

} // multiAgentExperience
} // ipc
} // proxy
} // multiAgentExperience
