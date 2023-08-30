/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_COMBINEDDIALOGSTATEHANDLERSLIFECYCLE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_COMBINEDDIALOGSTATEHANDLERSLIFECYCLE_H_

#include <atomic>
#include <memory>
#include <set>

#include <MultiAgentExperience/Dialog/DialogControllerInterface.h>
#include <MultiAgentExperience/Dialog/ListeningHandlerInterface.h>
#include <MultiAgentExperience/Experience/ExperienceControllerInterface.h>

#include "DialogStateHandlerLifecycle.h"
#include "DialogStateHandlerRegistry.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

/**
 * The CombinedDialogStateHandlersLifecycle combines all DialogStateHandler lifecycles into one, to ensure their
 * lifecycles are updated correctly when transitioning between DialogStates.
 */
class CombinedDialogStateHandlersLifecycle {
public:
    CombinedDialogStateHandlersLifecycle(
        std::shared_ptr<DialogStateHandlerRegistry> dialogStateHandlerRegistry,
        std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> dialogController,
        std::shared_ptr<multiAgentExperience::experience::ExperienceControllerInterface> experienceController);

    /**
     * Starts the listening state of the dialog. If a ListeningStateHandler is not registered it returns false.
     *
     * Note: any currently active state will be stopped first.
     *
     * @param controls - The set of currently active controls.
     *
     * @return Whether or not listening was started.
     */
    bool startListening(std::set<multiAgentExperience::control::ControlType> controls);

    /**
     * Starts the thinking state of the dialog. If a ThinkingStateHandler is not registered it returns false.
     *
     * Note: any currently active state will be stopped first.
     *
     * @return Whether or not thinking was started.
     */
    bool startThinking();

    /**
     * Starts the speaking state of the dialog. If a SpeakingStateHandler is not registered it returns false.
     *
     * @param controlRegistry - The ControlRegisterInterface for this state.
     *
     * @return Whether or not speaking was started.
     */
    bool startSpeaking(std::shared_ptr<multiAgentExperience::control::ControlRegistryInterface> controlRegistry);

    /**
     * Returns whether or not the current dialog was stopped without starting a different state.
     *
     * @return whether or not the current dialog was stopped without starting a different state.
     */
    bool stopCurrentDialogState();

    /**
     * Stops the dialog completely, including any active state first.
     */
    void stop();

private:
    bool tryToStartDialogState(
        std::shared_ptr<DialogStateHandlerLifecycle> candidateDialogState,
        multiAgentExperience::experience::ExperienceId experienceId);

    std::shared_ptr<DialogStateHandlerRegistry> m_dialogStateHandlerRegistry;
    std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> m_dialogController;
    std::shared_ptr<multiAgentExperience::experience::ExperienceControllerInterface> m_experienceController;
    std::shared_ptr<DialogStateHandlerLifecycle> m_currentDialogStateLifecycle;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_COMBINEDDIALOGSTATEHANDLERSLIFECYCLE_H_
