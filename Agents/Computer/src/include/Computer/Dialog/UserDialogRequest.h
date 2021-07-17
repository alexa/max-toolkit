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

#ifndef MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_DIALOG_USERDIALOGREQUEST_H_
#define MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_DIALOG_USERDIALOGREQUEST_H_

#include <MultiAgentExperience/Dialog/DialogRequestInterface.h>

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {
namespace dialog {

class UserDialogRequest : public multiAgentExperience::dialog::DialogRequestInterface {
private:
    /// @name DialogRequestInterface method overrides.
    /// @{
    void onDenied(const std::string& denialMessage) override;
    void onDialogStarted(std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> controller) override;
    void onError(const std::string& errorMessage) override;
    void onDialogStopped() override;
    /// @}
};

}  // namespace dialog
}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_DIALOG_USERDIALOGREQUEST_H_
