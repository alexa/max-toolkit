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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGREQUESTTRANSFORMER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGREQUESTTRANSFORMER_H_

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
    DialogRequestTransformer(std::shared_ptr<DialogLifecycleTransformer> dialogLifecycleTransformer);

    /// @name DialogRequest method overrides.
    /// @{
    void onGranted() override;
    void onDenied() override;
    /// @}

private:
    std::shared_ptr<DialogLifecycleTransformer> m_dialogLifecycleTransformer;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGREQUESTTRANSFORMER_H_
