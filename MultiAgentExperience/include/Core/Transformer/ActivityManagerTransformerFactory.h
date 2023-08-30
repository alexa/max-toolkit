/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_ACTIVITYMANAGERTRANSFORMERFACTORY_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_ACTIVITYMANAGERTRANSFORMERFACTORY_H_

#include <memory>

#include "Activity/ActivityManager.h"
#include "ActivityRequestTransformerFactory.h"
#include "ActivityManagerTransformer.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class ActivityManagerTransformerFactory {
public:
    ActivityManagerTransformerFactory(
        std::shared_ptr<multiAgentExperience::library::activity::ActivityManager> activityManager,
        std::shared_ptr<ActivityRequestTransformerFactory> requestTransformerFactory);

    std::shared_ptr<ActivityManagerTransformer> create(const multiAgentExperience::actor::ActorId& actorId);

private:
    std::shared_ptr<multiAgentExperience::library::activity::ActivityManager> m_activityManager;
    std::shared_ptr<ActivityRequestTransformerFactory> m_requestTransformerFactory;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_ACTIVITYMANAGERTRANSFORMERFACTORY_H_
