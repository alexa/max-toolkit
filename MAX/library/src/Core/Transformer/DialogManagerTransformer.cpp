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

#include "Core/Transformer/DialogManagerTransformer.h"

#include "Core/Transformer/DialogRequestTransformer.h"
#include "Core/Transformer/DialogStateHandlerRegistry.h"
#include "Dialog/DialogManager.h"
#include "MultiAgentExperience/Dialog/DialogRequestInterface.h"
#include "MultiAgentExperience/Dialog/ListeningHandlerInterface.h"
#include "MultiAgentExperience/Dialog/SpeakingHandlerInterface.h"
#include "MultiAgentExperience/Dialog/ThinkingHandlerInterface.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

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
}

void DialogManagerTransformer::request(std::shared_ptr<multiAgentExperience::dialog::DialogRequestInterface> request) {
    auto dialogLifecycleTransformer = std::make_shared<DialogLifecycleTransformer>(
        m_actorId, request, m_dialogLifecycleFactory, m_dialogControllerTransformerFactory);

    auto dialogRequest = std::make_shared<DialogRequestTransformer>(dialogLifecycleTransformer);
    m_requestStore.storeTransformedRequest(request, dialogRequest);
    m_dialogManager->request(dialogRequest);
}

void DialogManagerTransformer::stop(std::shared_ptr<multiAgentExperience::dialog::DialogRequestInterface> request) {
    auto transformedID = m_requestStore.getTransformedRequestId(request);
    stop(transformedID);
    m_requestStore.cleanupTransformedRequest(request);
}

void DialogManagerTransformer::setAllHandlers(
    std::shared_ptr<multiAgentExperience::dialog::ListeningHandlerInterface> listeningHandler,
    std::shared_ptr<multiAgentExperience::dialog::ThinkingHandlerInterface> thinkingHandler,
    std::shared_ptr<multiAgentExperience::dialog::SpeakingHandlerInterface> speakingHandler) {
    m_dialogStateHandlerRegistry->setListeningHandler(listeningHandler);
    m_dialogStateHandlerRegistry->setThinkingHandler(thinkingHandler);
    m_dialogStateHandlerRegistry->setSpeakingHandler(speakingHandler);
}

void DialogManagerTransformer::removeAllHandlers() {
    m_dialogStateHandlerRegistry->removeListeningHandler();
    m_dialogStateHandlerRegistry->removeThinkingHandler();
    m_dialogStateHandlerRegistry->removeSpeakingHandler();
}

void DialogManagerTransformer::setListeningHandler(
    std::shared_ptr<multiAgentExperience::dialog::ListeningHandlerInterface> handler) {
    m_dialogStateHandlerRegistry->setListeningHandler(handler);
}

void DialogManagerTransformer::removeListeningHandler() {
    m_dialogStateHandlerRegistry->removeListeningHandler();
}

void DialogManagerTransformer::setThinkingHandler(
    std::shared_ptr<multiAgentExperience::dialog::ThinkingHandlerInterface> handler) {
    m_dialogStateHandlerRegistry->setThinkingHandler(handler);
}

void DialogManagerTransformer::removeThinkingHandler() {
    m_dialogStateHandlerRegistry->removeThinkingHandler();
}

void DialogManagerTransformer::setSpeakingHandler(
    std::shared_ptr<multiAgentExperience::dialog::SpeakingHandlerInterface> handler) {
    m_dialogStateHandlerRegistry->setSpeakingHandler(handler);
}

void DialogManagerTransformer::removeSpeakingHandler() {
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
