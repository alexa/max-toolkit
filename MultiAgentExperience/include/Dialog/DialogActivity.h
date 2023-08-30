/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGACTIVITY_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGACTIVITY_H_

#include <memory>

#include "Activity/Activity.h"
#include "Activity/FocusManager/MixingBehavior.h"
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
    void onBackground(multiAgentExperience::library::activity::MixingBehavior behavior) override;
    void onStop() override;
    actor::ActorId getActorId() const override;
    /// @}

private:
    std::shared_ptr<DialogLifecycle> m_dialog;
};

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGACTIVITY_H_
