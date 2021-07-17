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

#include "Core/Transformer/DialogStateHandlerRegistry.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

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
