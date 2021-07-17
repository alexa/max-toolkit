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

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_SPEAKINGHANDLERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_SPEAKINGHANDLERINTERFACE_H_

#include <memory>

#include "MultiAgentExperience/Control/ControlRegistryInterface.h"
#include "MultiAgentExperience/Dialog/DialogControllerInterface.h"
#include "MultiAgentExperience/Experience/ExperienceControllerInterface.h"

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
     * @param experienceController - The ExperienceControlInterface to add an Experience for the Agent.
     * @param controlRegistry - The Universal Device Command registry to store any active UDCs which should take action
     *                          on this dialog when in SPEAKING state.
     */
    virtual void onStartSpeaking(
        std::shared_ptr<DialogControllerInterface> controller,
        std::shared_ptr<multiAgentExperience::experience::ExperienceControllerInterface> experienceController,
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
