/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGREQUESTTRANSFORMER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGREQUESTTRANSFORMER_H_

#include <MultiAgentExperience/Dialog/DialogBargeInPriority.h>

#include "Dialog/DialogRequest.h"
#include "DialogLifecycleTransformer.h"

/**
 * The DialogRequestTransformer provides a DialogRequest for the internal DialogManager. It forwards the requests
 * lifecycle to be handled by the DialogLifecycleTransformer.
 */
namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class DialogRequestTransformer : public library::dialog::DialogRequest {
public:
    DialogRequestTransformer(
        std::shared_ptr<DialogLifecycleTransformer> dialogLifecycleTransformer,
        const multiAgentExperience::dialog::DialogBargeInPriority& dialogBargeInPriority);

    /// @name DialogRequest method overrides.
    /// @{
    void onGranted() override;
    void onDenied() override;
    multiAgentExperience::actor::ActorId getActorId() const override;
    /// @}

private:
    std::shared_ptr<DialogLifecycleTransformer> m_dialogLifecycleTransformer;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGREQUESTTRANSFORMER_H_
