/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Core/Transformer/DialogStateHandlerRegistry.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

void DialogStateHandlerRegistry::setControlReceiver(
    std::shared_ptr<multiAgentExperience::dialog::ControlReceiverInterface> receiver) {
    if (receiver) {
        std::unique_lock<std::mutex> lock{m_registryMutex};
        m_controlReceiver = receiver;
    }
}

void DialogStateHandlerRegistry::removeControlReceiver() {
    std::unique_lock<std::mutex> lock{m_registryMutex};
    m_controlReceiver = nullptr;
}

std::shared_ptr<multiAgentExperience::dialog::ControlReceiverInterface> DialogStateHandlerRegistry::
getControlReceiver() {
    std::unique_lock<std::mutex> lock{m_registryMutex};
    return m_controlReceiver;
}

void DialogStateHandlerRegistry::setListeningHandler(
    std::shared_ptr<multiAgentExperience::dialog::ListeningHandlerInterface> handler) {
    if (handler) {
        std::unique_lock<std::mutex> lock{m_registryMutex};
        m_listeningHandler = handler;
    }
}

void DialogStateHandlerRegistry::removeListeningHandler() {
    std::unique_lock<std::mutex> lock{m_registryMutex};
    m_listeningHandler = nullptr;
}

std::shared_ptr<multiAgentExperience::dialog::ListeningHandlerInterface> DialogStateHandlerRegistry::
    getListeningHandler() {
    std::unique_lock<std::mutex> lock{m_registryMutex};
    return m_listeningHandler;
}

void DialogStateHandlerRegistry::setThinkingHandler(
    std::shared_ptr<multiAgentExperience::dialog::ThinkingHandlerInterface> handler) {
    if (handler) {
        std::unique_lock<std::mutex> lock{m_registryMutex};
        m_thinkingHandler = handler;
    }
}

void DialogStateHandlerRegistry::removeThinkingHandler() {
    std::unique_lock<std::mutex> lock{m_registryMutex};
    m_thinkingHandler = nullptr;
}

std::shared_ptr<multiAgentExperience::dialog::ThinkingHandlerInterface> DialogStateHandlerRegistry::
    getThinkingHandler() {
    std::unique_lock<std::mutex> lock{m_registryMutex};
    return m_thinkingHandler;
}

void DialogStateHandlerRegistry::setSpeakingHandler(
    std::shared_ptr<multiAgentExperience::dialog::SpeakingHandlerInterface> handler) {
    if (handler) {
        std::unique_lock<std::mutex> lock{m_registryMutex};
        m_speakingHandler = handler;
    }
}

void DialogStateHandlerRegistry::removeSpeakingHandler() {
    std::unique_lock<std::mutex> lock{m_registryMutex};
    m_speakingHandler = nullptr;
}

std::shared_ptr<multiAgentExperience::dialog::SpeakingHandlerInterface> DialogStateHandlerRegistry::
    getSpeakingHandler() {
    std::unique_lock<std::mutex> lock{m_registryMutex};
    return m_speakingHandler;
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
