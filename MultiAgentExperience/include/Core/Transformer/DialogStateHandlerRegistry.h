/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGSTATEHANDLERREGISTRY_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGSTATEHANDLERREGISTRY_H_

#include <memory>
#include <mutex>
#include <unordered_map>

#include <MultiAgentExperience/Dialog/ListeningHandlerInterface.h>
#include <MultiAgentExperience/Dialog/ThinkingHandlerInterface.h>
#include <MultiAgentExperience/Dialog/SpeakingHandlerInterface.h>
#include <MultiAgentExperience/Dialog/ControlReceiverInterface.h>

namespace multiAgentExperience {

namespace library {
namespace core {
namespace transformer {

class DialogStateHandlerRegistry {
public:
    void setControlReceiver(std::shared_ptr<multiAgentExperience::dialog::ControlReceiverInterface> receiver);

    void removeControlReceiver();

    std::shared_ptr<multiAgentExperience::dialog::ControlReceiverInterface> getControlReceiver();

    void setListeningHandler(std::shared_ptr<multiAgentExperience::dialog::ListeningHandlerInterface> handler);

    void removeListeningHandler();

    std::shared_ptr<multiAgentExperience::dialog::ListeningHandlerInterface> getListeningHandler();

    void setThinkingHandler(std::shared_ptr<multiAgentExperience::dialog::ThinkingHandlerInterface> handler);

    void removeThinkingHandler();

    std::shared_ptr<multiAgentExperience::dialog::ThinkingHandlerInterface> getThinkingHandler();

    void setSpeakingHandler(std::shared_ptr<multiAgentExperience::dialog::SpeakingHandlerInterface> handler);

    void removeSpeakingHandler();

    std::shared_ptr<multiAgentExperience::dialog::SpeakingHandlerInterface> getSpeakingHandler();

private:
    std::mutex m_registryMutex;
    std::shared_ptr<multiAgentExperience::dialog::ControlReceiverInterface> m_controlReceiver;
    std::shared_ptr<multiAgentExperience::dialog::ListeningHandlerInterface> m_listeningHandler;
    std::shared_ptr<multiAgentExperience::dialog::ThinkingHandlerInterface> m_thinkingHandler;
    std::shared_ptr<multiAgentExperience::dialog::SpeakingHandlerInterface> m_speakingHandler;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGSTATEHANDLERREGISTRY_H_
