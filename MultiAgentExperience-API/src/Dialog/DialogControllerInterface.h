/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_DIALOGCONTROLLERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_DIALOGCONTROLLERINTERFACE_H_

#include <string>

#include "MultiAgentExperience/Control/Control.h"

namespace multiAgentExperience {
namespace dialog {

/**
 * DialogControllerInterface is used to take action on the current dialog. This includes starting different dialog
 * states, stopping the dialog, and invoking Universal Device Commands during some state changes.
 * A DialogControllerInterface is no longer usable after it is stopped.
 */
class DialogControllerInterface {
public:
    /**
     * Destructor.
     */
    virtual ~DialogControllerInterface() = default;

    /**
     * Starts the LISTENING state of the dialog.
     */
    virtual void startListening() = 0;

    /**
     * Starts the THINKING state of the dialog.
     */
    virtual void startThinking() = 0;

    /**
     * Starts the SPEAKING state of the dialog.
     */
    virtual void startSpeaking() = 0;

    /**
     * Invokes a Universal Device Command (if it is valid) before starting SPEAKING.
     *
     * @param controlType - The type of Universal Device Command to invoke. If it is not a control which is available
     *                      then the invocation does nothing but SPEAKING is still started.
     */
    virtual void invokeControlAndStartSpeaking(const multiAgentExperience::control::ControlType& controlType) = 0;

    /**
     * Stops the dialog immediately. Once stopped the DialogControllerInterface cannot be used to enter any other dialog
     * state.
     */
    virtual void stop() = 0;

    /**
     * Stops the dialog immediately and then invokes a Universal Device Command (if it is valid).  Once stopped the
     * DialogControllerInterface cannot be used to enter any other dialog state.
     *
     * @param controlType - The type of Universal Device Command to invoke. If it is not a control which is available
     *                      then the invocation does nothing but SPEAKING is still started.
     */
    virtual void stopAndInvokeControl(const multiAgentExperience::control::ControlType& controlType) = 0;
};

}  // namespace dialog
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_DIALOGCONTROLLERINTERFACE_H_
