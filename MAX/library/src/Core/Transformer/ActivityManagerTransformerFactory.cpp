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
