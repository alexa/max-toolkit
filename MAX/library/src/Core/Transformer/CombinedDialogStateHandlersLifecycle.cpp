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

#include "Core/Transformer/CombinedDialogStateHandlersLifecycle.h"

#include "Control/Control.h"
#include "Core/Transformer/DialogStateHandlerLifecycle.h"
#include "Core/Transformer/DialogStateHandlerRegistry.h"

#include "MultiAgentExperience/Dialog/SpeakingHandlerInterface.h"
#include "MultiAgentExperience/Dialog/ThinkingHandlerInterface.h"
#include "MultiAgentExperience/Experience/ExperienceControllerInterface.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

CombinedDialogStateHandlersLifecycle::CombinedDialogStateHandlersLifecycle(
    std::shared_ptr<DialogStateHandlerRegistry> dialogStateHandlerRegistry,
    std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> dialogController,
    std::shared_ptr<multiAgentExperience::experience::ExperienceControllerInterface> experienceController) :
        m_dialogStateHandlerRegistry{dialogStateHandlerRegistry},
        m_dialogController{dialogController},
        m_experienceController{experienceController} {
}

bool CombinedDialogStateHandlersLifecycle::startListening(
    std::set<multiAgentExperience::control::ControlType> controls) {
    auto listeningHandler = m_dialogStateHandlerRegistry->getListeningHandler();
    if (listeningHandler) {
        auto boundStart = std::bind(
            &multiAgentExperience::dialog::ListeningHandlerInterface::onStartListening,
            listeningHandler,
            m_dialogController,
            controls);
        auto boundStop =
            std::bind(&multiAgentExperience::dialog::ListeningHandlerInterface::onStopListening, listeningHandler);
        auto candidateDialogStateLifecycle = std::make_shared<DialogStateHandlerLifecycle>(
            library::core::transformer::DialogState::createListening(), boundStart, boundStop);
        return tryToStartDialogState(candidateDialogStateLifecycle, "listening");
    }
    return false;
}

bool CombinedDialogStateHandlersLifecycle::startThinking() {
    auto thinkingHandler = m_dialogStateHandlerRegistry->getThinkingHandler();
    if (thinkingHandler) {
        auto boundStart = std::bind(
            &multiAgentExperience::dialog::ThinkingHandlerInterface::onStartThinking,
            thinkingHandler,
            m_dialogController);
        auto boundStop =
            std::bind(&multiAgentExperience::dialog::ThinkingHandlerInterface::onStopThinking, thinkingHandler);
        auto candidateDialogStateLifecycle = std::make_shared<DialogStateHandlerLifecycle>(
            library::core::transformer::DialogState::createThinking(), boundStart, boundStop);
        return tryToStartDialogState(candidateDialogStateLifecycle, "thinking");
    }
    return false;
}

bool CombinedDialogStateHandlersLifecycle::startSpeaking(
    std::shared_ptr<multiAgentExperience::control::ControlRegistryInterface> controlRegistry) {
    auto speakingHandler = m_dialogStateHandlerRegistry->getSpeakingHandler();
    if (speakingHandler) {
        // TODO: Explore automatically cleaning up the listening or thinking Experiences under VII-289.
        auto boundStart = std::bind(
            &multiAgentExperience::dialog::SpeakingHandlerInterface::onStartSpeaking,
            speakingHandler,
            m_dialogController,
            m_experienceController,
            controlRegistry);
        auto boundStop =
            std::bind(&multiAgentExperience::dialog::SpeakingHandlerInterface::onStopSpeaking, speakingHandler);
        auto candidateDialogStateLifecycle = std::make_shared<DialogStateHandlerLifecycle>(
            library::core::transformer::DialogState::createSpeaking(), boundStart, boundStop);
        return tryToStartDialogState(candidateDialogStateLifecycle);
    }
    return false;
}

bool CombinedDialogStateHandlersLifecycle::stopCurrentDialogState() {
    if (m_currentDialogStateLifecycle) {
        auto expectedState = m_currentDialogStateLifecycle->getDialogState();
        m_currentDialogStateLifecycle->stop();
        auto currentState = m_currentDialogStateLifecycle->getDialogState();
        if (currentState != expectedState) {
            // TODO: log a warning that transition to a state was abandoned as stopping the previous one
            // transitioned to a different state first under VII-290.
            return false;
        }
    }
    return true;
}

void CombinedDialogStateHandlersLifecycle::stop() {
    if (m_dialogController) {
        stopCurrentDialogState();
        m_dialogController->stop();
    }
}

bool CombinedDialogStateHandlersLifecycle::tryToStartDialogState(
    std::shared_ptr<DialogStateHandlerLifecycle> candidateDialogState,
    const std::string& experienceName) {
    if (stopCurrentDialogState()) {
        m_currentDialogStateLifecycle = candidateDialogState;
        if (!experienceName.empty()) {
            m_experienceController->startExperience(experience::ExperienceId(experienceName));
        }
        m_currentDialogStateLifecycle->start();
        return true;
    }
    return false;
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
