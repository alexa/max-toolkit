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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGLIFECYCLETRANSFORMER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGLIFECYCLETRANSFORMER_H_

#include <atomic>
#include <memory>
#include <mutex>
#include <set>

#include <MultiAgentExperience/Dialog/DialogRequestInterface.h>

#include "CombinedDialogStateHandlersLifecycleFactory.h"
#include "Dialog/Dialog.h"
#include "Dialog/DialogController.h"
#include "DialogControllerTransformerFactory.h"
#include "DialogRequestLifecycle.h"
#include "DialogState.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

/**
 * A DialogLifecycleTransformer transforms the internal dialog lifecycle into the external dialog lifecycle.
 */
class DialogLifecycleTransformer : public library::dialog::Dialog {
public:
    DialogLifecycleTransformer(
        const multiAgentExperience::actor::ActorId& actorId,
        std::shared_ptr<multiAgentExperience::dialog::DialogRequestInterface> dialogRequest,
        std::shared_ptr<CombinedDialogStateHandlersLifecycleFactory> dialogStateLifecycleFactory,
        std::shared_ptr<DialogControllerTransformerFactory> dialogControllerTransformerFactory);

    /// @name Dialog method overrides.
    /// @{
    void onDialogStarted(std::shared_ptr<library::dialog::DialogController> dialogController) override;
    void onListening(std::unordered_set<library::control::ControlName> availableControls) override;
    void onThinking() override;
    void onOtherState(
        const library::dialog::DialogState otherState,
        std::shared_ptr<library::control::ControlRegistry> controlRegistry,
        std::shared_ptr<library::control::ControlInvoker> controlInvoker) override;
    void onDialogFinished() override;
    /// @}

    void onGranted();

    void onDenied();

    int getId() const;

private:
    void sendErrorMessageForMissingState(const DialogState& dialogState);

    const std::atomic_int m_id;
    const multiAgentExperience::actor::ActorId m_actorId;
    std::shared_ptr<DialogRequestLifecycle> m_dialogRequestLifecycle;
    std::shared_ptr<CombinedDialogStateHandlersLifecycleFactory> m_dialogStateLifecycleFactory;
    std::shared_ptr<DialogControllerTransformerFactory> m_dialogControllerTransformerFactory;
    std::shared_ptr<CombinedDialogStateHandlersLifecycle> m_dialogStatesLifecycle;
    std::mutex m_lifecycleMutex;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

template <>
struct std::hash<multiAgentExperience::library::core::transformer::DialogLifecycleTransformer> {
    std::size_t operator()(const multiAgentExperience::library::core::transformer::DialogLifecycleTransformer&
                               dialogLifecycleTransformer) const noexcept {
        return dialogLifecycleTransformer.getId();
    }
};

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGLIFECYCLETRANSFORMER_H_
