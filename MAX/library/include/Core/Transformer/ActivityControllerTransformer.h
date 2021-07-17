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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_ACTIVITYCONTROLLERTRANSFORMER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_ACTIVITYCONTROLLERTRANSFORMER_H_

#include <functional>

#include <MultiAgentExperience/Activity/ActivityControllerInterface.h>

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class ActivityControllerTransformer : public multiAgentExperience::activity::ActivityControllerInterface {
public:
    ActivityControllerTransformer(std::function<void()> stopCallback);

    /// @name ActivityControllerInterface method overrides.
    /// @{
    void stop() override;
    /// @}

private:
    std::function<void()> m_stopCallback;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_ACTIVITYCONTROLLERTRANSFORMER_H_
