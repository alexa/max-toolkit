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

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_LISTENINGHANDLERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_LISTENINGHANDLERINTERFACE_H_

#include <memory>
#include <set>

#include "MultiAgentExperience/Control/Control.h"
#include "MultiAgentExperience/Dialog/DialogControllerInterface.h"

namespace multiAgentExperience {
namespace dialog {

/**
 * A ListeningHandlerInterface handles the lifecycle of the LISTENING state for dialogs of an Agent.
 */
class ListeningHandlerInterface {
public:
    /**
     * Destructor.
     */
    virtual ~ListeningHandlerInterface() = default;

    /**
     * Called when LISTENING state starts for the current dialog.
     *
     * Note: The 'listening' Experience is automatically set for the Agent when entering LISTENING state.
     *
     * @param controller - The DialogControllerInterface to control the current dialog.
     * @param controls - A set of the currently available Universal Device Commands for the user to take action on.
     */
    virtual void onStartListening(
        std::shared_ptr<DialogControllerInterface> controller,
        std::set<multiAgentExperience::control::ControlType> controls) = 0;

    /**
     * Called when LISTENING state stops.
     */
    virtual void onStopListening() = 0;
};

}  // namespace dialog
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_LISTENINGHANDLERINTERFACE_H_
