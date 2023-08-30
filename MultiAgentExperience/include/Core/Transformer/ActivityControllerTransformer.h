/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
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
