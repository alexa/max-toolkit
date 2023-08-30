/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGMANAGERTRANSFORMER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGMANAGERTRANSFORMER_H_

#include <memory>
#include <mutex>
#include <unordered_map>

#include <MultiAgentExperience/Dialog/DialogManagerInterface.h>
#include <MultiAgentExperience/Dialog/DialogRequestInterface.h>
#include <MultiAgentExperience/Dialog/ControlReceiverInterface.h>

#include "CombinedDialogStateHandlersLifecycleFactory.h"
#include "Core/Transformer/TransformedRequestStore.h"
#include "Dialog/DialogManager.h"
#include "Dialog/DialogRequestID.h"
#include "DialogControllerTransformerFactory.h"
#include "DialogRequestTransformer.h"
#include "DialogStateHandlerRegistry.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class DialogManagerTransformer : public multiAgentExperience::dialog::DialogManagerInterface {
public:
    DialogManagerTransformer(
        const multiAgentExperience::actor::ActorId& actorId,
        std::shared_ptr<library::dialog::DialogManager> dialogManager,
        std::shared_ptr<DialogStateHandlerRegistry> dialogStateHandlerRegistry,
        std::shared_ptr<DialogControllerTransformerFactory> dialogControllerTransformerFactory,
        std::shared_ptr<CombinedDialogStateHandlersLifecycleFactory> dialogLifecycleFactory);

    /// @name DialogManagerInterface method overrides.
    /// @{
    void request(std::shared_ptr<multiAgentExperience::dialog::DialogRequestInterface> request) override;
    void stop(std::shared_ptr<multiAgentExperience::dialog::DialogRequestInterface> request) override;
    void setAllHandlers(
        std::shared_ptr<multiAgentExperience::dialog::ControlReceiverInterface> controlReceiver,
        std::shared_ptr<multiAgentExperience::dialog::ListeningHandlerInterface> listeningHandler,
        std::shared_ptr<multiAgentExperience::dialog::ThinkingHandlerInterface> thinkingHandler,
        std::shared_ptr<multiAgentExperience::dialog::SpeakingHandlerInterface> speakingHandler) override;
    void removeAllHandlers() override;
    void setControlReceiver(std::shared_ptr<multiAgentExperience::dialog::ControlReceiverInterface> receiver) override;
    void removeControlReceiver() override;
    void setListeningHandler(std::shared_ptr<multiAgentExperience::dialog::ListeningHandlerInterface> handler) override;
    void removeListeningHandler() override;
    void setThinkingHandler(std::shared_ptr<multiAgentExperience::dialog::ThinkingHandlerInterface> handler) override;
    void removeThinkingHandler() override;
    void setSpeakingHandler(std::shared_ptr<multiAgentExperience::dialog::SpeakingHandlerInterface> handler) override;
    void removeSpeakingHandler() override;
    /// @}

    multiAgentExperience::actor::ActorId getActorId() const;

private:
    void stop(library::dialog::DialogRequestID);

    const multiAgentExperience::actor::ActorId m_actorId;
    std::shared_ptr<library::dialog::DialogManager> m_dialogManager;
    std::shared_ptr<DialogStateHandlerRegistry> m_dialogStateHandlerRegistry;
    std::shared_ptr<DialogControllerTransformerFactory> m_dialogControllerTransformerFactory;
    std::shared_ptr<CombinedDialogStateHandlersLifecycleFactory> m_dialogLifecycleFactory;

    TransformedRequestStore<
        multiAgentExperience::dialog::DialogRequestInterface,
        DialogRequestTransformer,
        multiAgentExperience::library::dialog::DialogRequestID>
        m_requestStore;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

template <>
struct std::hash<multiAgentExperience::library::core::transformer::DialogManagerTransformer> {
    std::size_t operator()(multiAgentExperience::library::core::transformer::DialogManagerTransformer const&
                               dialogManagerTransformer) const noexcept {
        return std::hash<std::string>()(static_cast<string>(dialogManagerTransformer.getActorId()));
    }
};

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGMANAGERTRANSFORMER_H_
