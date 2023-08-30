/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_THINKINGHANDLERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_THINKINGHANDLERINTERFACE_H_

#include <memory>

#include "MultiAgentExperience/Dialog/DialogControllerInterface.h"

namespace multiAgentExperience {
namespace dialog {

/**
 * A ThinkingHandlerInterface handles the lifecycle of the THINKING state for dialogs of an Agent.
 */
class ThinkingHandlerInterface {
public:
    /**
     * Destructor.
     */
    virtual ~ThinkingHandlerInterface() = default;

    /**
     * Called when THINKING state starts for the current dialog.
     *
     * Note: The 'thinking' Experience is automatically set for the Agent when entering THINKING state.
     *
     * @param controller - The DialogControllerInterface to control the current dialog.
     */
    virtual void onStartThinking(std::shared_ptr<DialogControllerInterface> controller) = 0;

    /**
     * Called when THINKING state stops.
     */
    virtual void onStopThinking() = 0;
};

}  // namespace dialog
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_THINKINGHANDLERINTERFACE_H_
