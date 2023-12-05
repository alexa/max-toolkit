/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_DIALOGREQUESTINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_DIALOGREQUESTINTERFACE_H_

#include <memory>
#include <string>

#include "DialogBargeInPriority.h"
#include "DialogControllerInterface.h"
#include "MultiAgentExperience/Utils/HashableInterface.h"

namespace multiAgentExperience {
namespace dialog {

/**
 * DialogRequestInterface contains callbacks for a dialog request's lifecycle. Each request is either denied or started,
 * and any request which is started is also stopped. Following these lifecycle callbacks allows Agents to interact with
 * any other multi-agent experiences.
 */
class DialogRequestInterface : public utils::HashableInterface {
public:

    /**
     * Destructor.
     */
    virtual ~DialogRequestInterface() = default;

    /**
     * The request to start a dialog was denied. A denied request is not recoverable and should be dropped.
     *
     * @param denialMessage - A message explaining the cause of denial.
     */
    virtual void onDenied(const std::string& denialMessage) = 0;

    /**
     * The request to start a dialog succeeded and the dialog is started. The provided DialogControllerInterface can
     * be used to control the state of the dialog.
     *
     * @param controller - The controller for this dialog.
     */
    virtual void onDialogStarted(std::shared_ptr<DialogControllerInterface> controller) = 0;

    /**
     * There was an error during the lifecycle of the dialog.
     *
     * @param errorMessage - A message explaining the cause of the error.
     */
    virtual void onError(const std::string& errorMessage) = 0;

    /**
     * A previously started dialog was stopped. This is called whether or not the dialog was stopped by the Agent which
     * requested the dialog, or some other multi-agent experience interrupted it. All registered Universal Device
     * Commands, Experiences, or other multi-agent features associated with the dialog will be automatically cleaned up.
     */
    virtual void onDialogStopped() = 0;

    /**
     * @return The barge-in priority of the requested dialog.
     */
    virtual DialogBargeInPriority getDialogBargeInPriority() const = 0;
};

}  // namespace dialog
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_DIALOGREQUESTINTERFACE_H_
