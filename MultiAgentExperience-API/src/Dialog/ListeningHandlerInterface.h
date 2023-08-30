/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
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
     */
    virtual void onStartListening(
        std::shared_ptr<DialogControllerInterface> controller) = 0;

    /**
     * Called when LISTENING state stops.
     */
    virtual void onStopListening() = 0;
};

}  // namespace dialog
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_LISTENINGHANDLERINTERFACE_H_
