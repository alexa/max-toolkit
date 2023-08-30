/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGCONTROLLERTRANSFORMER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGCONTROLLERTRANSFORMER_H_

#include <atomic>
#include <memory>
#include <string>

#include <MultiAgentExperience/Dialog/DialogControllerInterface.h>

#include "Control/ControlInvokerFactory.h"
#include "Dialog/DialogController.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class DialogControllerTransformer : public multiAgentExperience::dialog::DialogControllerInterface {
public:
    DialogControllerTransformer(
        std::shared_ptr<library::control::ControlInvokerFactory> controlInvokerFactory,
        std::shared_ptr<library::dialog::DialogController> dialogController);

    /// @name DialogControllerInterface method overrides.
    /// @{
    void startListening() override;
    void startThinking() override;
    void startSpeaking() override;
    void invokeControlAndStartSpeaking(const multiAgentExperience::control::ControlType& controlType) override;
    void stop() override;
    void stopAndInvokeControl(const multiAgentExperience::control::ControlType& controlType) override;
    /// @}

private:
    enum class ControllerLifecycleState { STARTED, STOPPED };

    void markUninterruptible();
    void invokeControl(const multiAgentExperience::control::ControlType& controlType);

    bool stopInternal();
    bool trySwitchState(ControllerLifecycleState from, const ControllerLifecycleState& to);
    inline bool isStarted();

    std::atomic<ControllerLifecycleState> m_controllerLifecycleState;
    std::shared_ptr<library::control::ControlInvokerFactory> m_controlInvokerFactory;
    std::shared_ptr<library::dialog::DialogController> m_dialogController;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGCONTROLLERTRANSFORMER_H_
