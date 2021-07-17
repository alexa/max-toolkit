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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOG_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOG_H_

#include <memory>
#include <unordered_set>

#include "DialogState.h"
#include "DialogController.h"
#include "Control/ControlInvoker.h"
#include "Control/ControlRegistry.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

// TODO: Forward declare to address a circular dependency. To be addressed under VII-248.
class DialogController;

class Dialog {
public:
    virtual ~Dialog() = default;

    virtual void onDialogStarted(std::shared_ptr<DialogController> dialogController) = 0;

    virtual void onListening(std::unordered_set<library::control::ControlName> availableControls) = 0;

    virtual void onThinking() = 0;

    virtual void onOtherState(
        const DialogState otherState,
        std::shared_ptr<library::control::ControlRegistry> controlRegistry,
        std::shared_ptr<library::control::ControlInvoker> controlInvoker) = 0;

    virtual void onDialogFinished() = 0;
};

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOG_H_
