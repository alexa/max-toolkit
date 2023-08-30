/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_SPEAKINGHANDLERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_SPEAKINGHANDLERINTERFACE_H_

#include <memory>

#include "MultiAgentExperience/Control/ControlRegistryInterface.h"
#include "MultiAgentExperience/Dialog/DialogControllerInterface.h"

namespace multiAgentExperience {
namespace dialog {

/**
 * A SpeakingHandlerInterface handles the lifecycle of the SPEAKING state for dialogs of an Agent.
 */
class SpeakingHandlerInterface {
public:
    /**
     * Destructor.
     */
    virtual ~SpeakingHandlerInterface() = default;

    /**
     * Called when SPEAKING state starts for the current dialog.
     *
     * @param controller - The DialogControllerInterface to control the current dialog.
     * @param controlRegistry - The Universal Device Command registry to store any active UDCs which should take action
     *                          on this dialog when in SPEAKING state.
     */
    virtual void onStartSpeaking(
        std::shared_ptr<DialogControllerInterface> controller,
        std::shared_ptr<multiAgentExperience::control::ControlRegistryInterface> controlRegistry) = 0;

    /**
     * Called when SPEAKING state stops.
     *
     * Any registered UDCs with the ControlRegistryInterface given in onStartSpeaking will be
     * automatically removed.
     *
     * Any Experiences set with the ExperienceControllerInterface.however will continue if they are not ended. They will
     * only be automatically removed when the dialog ends completely.
     */
    virtual void onStopSpeaking() = 0;
};

}  // namespace dialog
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_SPEAKINGHANDLERINTERFACE_H_
