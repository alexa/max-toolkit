/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Core/Transformer/CombinedDialogStateHandlersLifecycle.h"

#include <sstream>

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Core/Transformer/DialogStateHandlerLifecycle.h"
#include "Core/Transformer/DialogStateHandlerRegistry.h"

#include "MultiAgentExperience/Dialog/SpeakingHandlerInterface.h"
#include "MultiAgentExperience/Dialog/ThinkingHandlerInterface.h"
#include "MultiAgentExperience/Experience/ExperienceControllerInterface.h"
#include "MultiAgentExperience/Dialog/ControlReceiverInterface.h"

#include "Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

const int THREE_SECONDS = 3;

static const std::string MODULE_TAG("CombinedDialogStateHandlersLifecycle");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

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
    auto controlReceiver = m_dialogStateHandlerRegistry->getControlReceiver();
    if(controlReceiver && !controls.empty()) {
        std::promise<void> continueListeningPromise;
        std::future<void> continueListeningFuture = continueListeningPromise.get_future();
        auto startListeningCallback = std::make_shared<dialog::StartListeningCallback>(std::move(continueListeningPromise));
        LX(DEBUG0, "Call to ControlReceiverInterface::onControlsReceived.");
        controlReceiver->onControlsReceived(startListeningCallback, controls);
        continueListeningFuture.wait_for(std::chrono::seconds(THREE_SECONDS));
    }

    auto listeningHandler = m_dialogStateHandlerRegistry->getListeningHandler();
    if (listeningHandler) {
        auto boundStart = std::bind(
            &multiAgentExperience::dialog::ListeningHandlerInterface::onStartListening,
            listeningHandler,
            m_dialogController);
        auto boundStop =
            std::bind(&multiAgentExperience::dialog::ListeningHandlerInterface::onStopListening, listeningHandler);
        auto candidateDialogStateLifecycle = std::make_shared<DialogStateHandlerLifecycle>(
            library::core::transformer::DialogState::createListening(), boundStart, boundStop);
        LX(DEBUG0, "Attempt to call ListeningHandlerInterface::onStartListening.");
        return tryToStartDialogState(candidateDialogStateLifecycle,
                                     multiAgentExperience::experience::commonIds::LISTENING);
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
        LX(DEBUG0, "Attempt to call ThinkingHandlerInterface::onStartThinking.");
        return tryToStartDialogState(candidateDialogStateLifecycle,
                                     multiAgentExperience::experience::commonIds::THINKING);
    }
    return false;
}

bool CombinedDialogStateHandlersLifecycle::startSpeaking(
    std::shared_ptr<multiAgentExperience::control::ControlRegistryInterface> controlRegistry) {
    auto speakingHandler = m_dialogStateHandlerRegistry->getSpeakingHandler();
    if (speakingHandler) {
        // TODO: Explore automatically cleaning up the listening or thinking Experiences.
        auto boundStart = std::bind(
            &multiAgentExperience::dialog::SpeakingHandlerInterface::onStartSpeaking,
            speakingHandler,
            m_dialogController,
            controlRegistry);
        auto boundStop =
            std::bind(&multiAgentExperience::dialog::SpeakingHandlerInterface::onStopSpeaking, speakingHandler);
        auto candidateDialogStateLifecycle = std::make_shared<DialogStateHandlerLifecycle>(
            library::core::transformer::DialogState::createSpeaking(), boundStart, boundStop);
        LX(DEBUG0, "Attempt to call SpeakingHandlerInterface::onStartSpeaking.");
        return tryToStartDialogState(candidateDialogStateLifecycle,
                                     multiAgentExperience::experience::commonIds::SPEAKING);
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
            // transitioned to a different state.
            return false;
        }
    }
    return true;
}

void CombinedDialogStateHandlersLifecycle::stop() {
    if (m_dialogController) {
        stopCurrentDialogState();
        LX(DEBUG0, "DialogControllerInterface::stop called.");
        m_dialogController->stop();
    }
}

bool CombinedDialogStateHandlersLifecycle::tryToStartDialogState(
    std::shared_ptr<DialogStateHandlerLifecycle> candidateDialogState,
    multiAgentExperience::experience::ExperienceId experienceId) {
    if (stopCurrentDialogState()) {
        m_currentDialogStateLifecycle = candidateDialogState;
        if (!experienceId.get().empty()) {
            std::stringstream ss;
            ss << "ExperienceControllerInterface::startExperience called. details:"
               << " experienceId=" << multiAgentExperience::library::utils::getObfuscatedExperienceId(experienceId);
            LX(DEBUG0, ss.str());
            m_experienceController->startExperience(experienceId);
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
