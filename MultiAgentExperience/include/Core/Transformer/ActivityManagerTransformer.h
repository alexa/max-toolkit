/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_ACTIVITYMANAGERTRANSFORMER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_ACTIVITYMANAGERTRANSFORMER_H_

#include <memory>
#include <mutex>

#include <MultiAgentExperience/Activity/ActivityManagerInterface.h>
#include <MultiAgentExperience/Actor/ActorId.h>

#include "Activity/ActivityManager.h"
#include "Core/Transformer/ActivityRequestTransformerFactory.h"
#include "Core/Transformer/ActivityRequestTransformer.h"
#include "Core/Transformer/TransformedRequestStore.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class ActivityManagerTransformer : public multiAgentExperience::activity::ActivityManagerInterface {
public:
    ActivityManagerTransformer(
        const multiAgentExperience::actor::ActorId& id,
        std::shared_ptr<multiAgentExperience::library::activity::ActivityManager> activityManager,
        std::shared_ptr<ActivityRequestTransformerFactory> requestTransformerFactory);

    virtual ~ActivityManagerTransformer();

    /// @name ActivityManagerInterface method overrides.
    /// @{
    void request(std::shared_ptr<multiAgentExperience::activity::ActivityRequestInterface> request) override;
    void stop(std::shared_ptr<multiAgentExperience::activity::ActivityRequestInterface> request) override;
    /// @}

private:
    void stop(multiAgentExperience::library::activity::ActivityRequestID);

    const multiAgentExperience::actor::ActorId m_id;
    std::shared_ptr<multiAgentExperience::library::activity::ActivityManager> m_activityManager;
    std::shared_ptr<ActivityRequestTransformerFactory> m_requestTransformerFactory;

    TransformedRequestStore<
        multiAgentExperience::activity::ActivityRequestInterface,
        ActivityRequestTransformer,
        multiAgentExperience::library::activity::ActivityRequestID>
        m_requestStore;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_ACTIVITYMANAGERTRANSFORMER_H_
