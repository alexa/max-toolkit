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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGCONTROLLER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGCONTROLLER_H_

#include <memory>

#include "DialogState.h"
#include "DialogLifecycle.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

// TODO: Forward declare to address a circular dependency. To be addressed under VII-248.
class DialogLifecycle;

class DialogController {
public:
    DialogController(std::shared_ptr<DialogLifecycle> m_dialogLifecycle);

    void startListening();

    void startThinking();

    void startOtherState(const DialogState otherState);

    void finishDialog();

    void markUninterruptible();

private:
    std::shared_ptr<DialogLifecycle> m_dialogLifecycle;
};

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGCONTROLLER_H_
