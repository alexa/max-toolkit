/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Core/Transformer/DialogManagerTransformer.h"

#include <sstream>

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Core/Transformer/DialogRequestTransformer.h"
#include "Core/Transformer/DialogStateHandlerRegistry.h"
#include "Dialog/DialogManager.h"
#include "MultiAgentExperience/Dialog/DialogRequestInterface.h"
#include "MultiAgentExperience/Dialog/ListeningHandlerInterface.h"
#include "MultiAgentExperience/Dialog/SpeakingHandlerInterface.h"
#include "MultiAgentExperience/Dialog/ThinkingHandlerInterface.h"

#include "Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

static const std::string MODULE_TAG("DialogManagerTransformer");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

DialogManagerTransformer::DialogManagerTransformer(
    const multiAgentExperience::actor::ActorId& actorId,
    std::shared_ptr<library::dialog::DialogManager> dialogManager,
    std::shared_ptr<DialogStateHandlerRegistry> dialogStateHandlerRegistry,
    std::shared_ptr<DialogControllerTransformerFactory> dialogControllerTransformerFactory,
    std::shared_ptr<CombinedDialogStateHandlersLifecycleFactory> dialogLifecycleFactory) :
        m_actorId{actorId},
        m_dialogManager{dialogManager},
        m_dialogStateHandlerRegistry{dialogStateHandlerRegistry},
        m_dialogControllerTransformerFactory{dialogControllerTransformerFactory},
        m_dialogLifecycleFactory{dialogLifecycleFactory} {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(actorId);
    LX(DEBUG0, ss.str());
}

void DialogManagerTransformer::request(std::shared_ptr<multiAgentExperience::dialog::DialogRequestInterface> request) {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_actorId)
       << " dialogBargeInPriority=" << multiAgentExperience::library::utils::toString(request->getDialogBargeInPriority());
    LX(DEBUG0, ss.str());

    auto dialogLifecycleTransformer = std::make_shared<DialogLifecycleTransformer>(
        m_actorId, request, m_dialogLifecycleFactory, m_dialogControllerTransformerFactory);

    auto dialogRequest = std::make_shared<DialogRequestTransformer>(
        dialogLifecycleTransformer,
        request->getDialogBargeInPriority());
    m_requestStore.storeTransformedRequest(request, dialogRequest);
    m_dialogManager->request(dialogRequest);
}

void DialogManagerTransformer::stop(std::shared_ptr<multiAgentExperience::dialog::DialogRequestInterface> request) {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_actorId)
       << " dialogBargeInPriority=" << multiAgentExperience::library::utils::toString(request->getDialogBargeInPriority());
    LX(DEBUG0, ss.str());

    auto transformedID = m_requestStore.getTransformedRequestId(request);
    stop(transformedID);
    m_requestStore.cleanupTransformedRequest(request);
}

void DialogManagerTransformer::setAllHandlers(
    std::shared_ptr<multiAgentExperience::dialog::ControlReceiverInterface> controlReceiver,
    std::shared_ptr<multiAgentExperience::dialog::ListeningHandlerInterface> listeningHandler,
    std::shared_ptr<multiAgentExperience::dialog::ThinkingHandlerInterface> thinkingHandler,
    std::shared_ptr<multiAgentExperience::dialog::SpeakingHandlerInterface> speakingHandler) {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_actorId);
    LX(DEBUG0, ss.str());

    m_dialogStateHandlerRegistry->setControlReceiver(controlReceiver);
    m_dialogStateHandlerRegistry->setListeningHandler(listeningHandler);
    m_dialogStateHandlerRegistry->setThinkingHandler(thinkingHandler);
    m_dialogStateHandlerRegistry->setSpeakingHandler(speakingHandler);
}

void DialogManagerTransformer::removeAllHandlers() {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_actorId);
    LX(DEBUG0, ss.str());

    m_dialogStateHandlerRegistry->removeControlReceiver();
    m_dialogStateHandlerRegistry->removeListeningHandler();
    m_dialogStateHandlerRegistry->removeThinkingHandler();
    m_dialogStateHandlerRegistry->removeSpeakingHandler();
}

void DialogManagerTransformer::setControlReceiver(
    std::shared_ptr<multiAgentExperience::dialog::ControlReceiverInterface> receiver) {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_actorId);
    LX(DEBUG0, ss.str());

    m_dialogStateHandlerRegistry->setControlReceiver(receiver);
}

void DialogManagerTransformer::removeControlReceiver() {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_actorId);
    LX(DEBUG0, ss.str());

    m_dialogStateHandlerRegistry->removeControlReceiver();
}

void DialogManagerTransformer::setListeningHandler(
    std::shared_ptr<multiAgentExperience::dialog::ListeningHandlerInterface> handler) {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_actorId);
    LX(DEBUG0, ss.str());

    m_dialogStateHandlerRegistry->setListeningHandler(handler);
}

void DialogManagerTransformer::removeListeningHandler() {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_actorId);
    LX(DEBUG0, ss.str());

    m_dialogStateHandlerRegistry->removeListeningHandler();
}

void DialogManagerTransformer::setThinkingHandler(
    std::shared_ptr<multiAgentExperience::dialog::ThinkingHandlerInterface> handler) {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_actorId);
    LX(DEBUG0, ss.str());

    m_dialogStateHandlerRegistry->setThinkingHandler(handler);
}

void DialogManagerTransformer::removeThinkingHandler() {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_actorId);
    LX(DEBUG0, ss.str());

    m_dialogStateHandlerRegistry->removeThinkingHandler();
}

void DialogManagerTransformer::setSpeakingHandler(
    std::shared_ptr<multiAgentExperience::dialog::SpeakingHandlerInterface> handler) {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_actorId);
    LX(DEBUG0, ss.str());

    m_dialogStateHandlerRegistry->setSpeakingHandler(handler);
}

void DialogManagerTransformer::removeSpeakingHandler() {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_actorId);
    LX(DEBUG0, ss.str());

    m_dialogStateHandlerRegistry->removeSpeakingHandler();
}

multiAgentExperience::actor::ActorId DialogManagerTransformer::getActorId() const {
    return m_actorId;
}

void DialogManagerTransformer::stop(multiAgentExperience::library::dialog::DialogRequestID id) {
    if (id > 0) {
        m_dialogManager->finish(id);
    }
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
