/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_TESTABLEDEVICE_APITYPEPROXY_H
#define MULTIAGENTEXPERIENCE_TESTABLEDEVICE_APITYPEPROXY_H

#include <utility>
#include <MultiAgentExperience/Activity/ActivityManagerInterface.h>
#include "MultiAgentExperience/IPC/Transport/MaxIpcComponentsBaseProxy.h"
#include "MultiAgentExperience/IPC/Proxy/MessageHandlerStore.h"
#include "MultiAgentExperience/IPC/Transport/MessageSender.h"


namespace multiAgentExperience {
namespace ipc {
namespace proxy {

class MessageHandlerStore;

namespace activity {
class ActivityManagerPackager {
public:
    multiAgentExperience::ipc::messaging::ReferencePayload package(
            std::shared_ptr<multiAgentExperience::activity::ActivityRequestInterface> request) {
        auto reference = multiAgentExperience::ipc::messaging::reference::createReference<
                multiAgentExperience::activity::ActivityRequestInterface
        >(request);
        auto payload = multiAgentExperience::ipc::messaging::ReferencePayload(reference);
        return payload;
    }
};

class ActivityManagerProxy : public std::enable_shared_from_this<ActivityManagerProxy>,
                             public multiAgentExperience::activity::ActivityManagerInterface,
                             public multiAgentExperience::ipc::transport::MaxIpcComponentsBaseProxy {
public:
    ActivityManagerProxy(
            multiAgentExperience::ipc::messaging::Reference reference,
            std::shared_ptr<transport::MessageSender> sender,
            std::shared_ptr<MessageHandlerStore> messageHandlerStore);

    void request(std::shared_ptr<multiAgentExperience::activity::ActivityRequestInterface> request) override;

    void stop(std::shared_ptr<multiAgentExperience::activity::ActivityRequestInterface>
                      request) override;

private:
    std::shared_ptr<MessageHandlerStore> m_messageHandlerStore;
    ActivityManagerPackager m_packager;
};

} // namespace activity
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_TESTABLEDEVICE_APITYPEPROXY_H
