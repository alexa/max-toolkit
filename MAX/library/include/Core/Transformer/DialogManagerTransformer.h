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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGMANAGERTRANSFORMER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGMANAGERTRANSFORMER_H_

#include <memory>
#include <mutex>
#include <unordered_map>

#include <MultiAgentExperience/Dialog/DialogManagerInterface.h>
#include <MultiAgentExperience/Dialog/DialogRequestInterface.h>

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
        std::shared_ptr<multiAgentExperience::dialog::ListeningHandlerInterface> listeningHandler,
        std::shared_ptr<multiAgentExperience::dialog::ThinkingHandlerInterface> thinkingHandler,
        std::shared_ptr<multiAgentExperience::dialog::SpeakingHandlerInterface> speakingHandler) override;
    void removeAllHandlers() override;
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
