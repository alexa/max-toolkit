/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_API_CONTROLRECEIVERINTERFACE_H
#define MULTIAGENTEXPERIENCE_API_CONTROLRECEIVERINTERFACE_H

#include <memory>
#include <set>

#include "MultiAgentExperience/Control/Control.h"
#include "MultiAgentExperience/Dialog/StartListeningCallback.h"

namespace multiAgentExperience {
namespace dialog {

/**
 * A ControlReceiverInterface is used to request ControlTypes that are available before start of ListeningState.
 */
class ControlReceiverInterface {
public:
    /**
     * Destructor.
     */
    virtual ~ControlReceiverInterface() = default;

    /**
     * Called when LISTENING state starts for the current dialog.
     * The caller waits for maximum of 3s before moving on.
     * If in case, the StartListeningCallback is not called within this timeout, the call moves
     * onto ListeningHandlerInterface::onStartListening.
     *
     * Note: The 'listening' Experience is automatically set for the Agent when entering LISTENING state.
     *
     * @param startListeningCallback - callback to be used when processing is done on the sent controls.
     * @param controls - A set of the currently available Universal Device Commands for the user to take action on.
     */
    virtual void onControlsReceived(
        std::shared_ptr<StartListeningCallback> startListeningCallback,
        std::set<multiAgentExperience::control::ControlType> controls) = 0;
};

}  // namespace dialog
}  // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_API_CONTROLRECEIVERINTERFACE_H
