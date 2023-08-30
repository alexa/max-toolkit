/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Core/Transformer/ActivityManagerTransformerFactory.h"

#include "Core/Transformer/ActivityManagerTransformer.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

ActivityManagerTransformerFactory::ActivityManagerTransformerFactory(
    std::shared_ptr<multiAgentExperience::library::activity::ActivityManager> activityManager,
    std::shared_ptr<ActivityRequestTransformerFactory> requestTransformerFactory) :
        m_activityManager{activityManager},
        m_requestTransformerFactory{requestTransformerFactory} {
}

std::shared_ptr<ActivityManagerTransformer> ActivityManagerTransformerFactory::create(
    const multiAgentExperience::actor::ActorId& actorId) {
    return std::make_shared<ActivityManagerTransformer>(actorId, m_activityManager, m_requestTransformerFactory);
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
