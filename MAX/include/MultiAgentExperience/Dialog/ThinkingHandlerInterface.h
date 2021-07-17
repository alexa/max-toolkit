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
