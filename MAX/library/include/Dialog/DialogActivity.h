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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGACTIVITY_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGACTIVITY_H_

#include <memory>

#include "Activity/Activity.h"
#include "DialogLifecycle.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

class DialogActivity : public activity::Activity {
public:
    DialogActivity(std::shared_ptr<DialogLifecycle> dialog);

    /// @name Activity method overrides.
    /// @{
    void onControlRegistryAvailable(std::shared_ptr<control::ControlRegistry> controlRegistry) override;
    void onForeground() override;
    void onBackground() override;
    void onStop() override;
    /// @}

private:
    std::shared_ptr<DialogLifecycle> m_dialog;
};

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGACTIVITY_H_
