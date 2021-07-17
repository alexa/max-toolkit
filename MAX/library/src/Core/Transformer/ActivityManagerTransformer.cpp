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

#include "Core/Transformer/ActivityManagerTransformer.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

ActivityManagerTransformer::ActivityManagerTransformer(
    const multiAgentExperience::actor::ActorId& id,
    std::shared_ptr<multiAgentExperience::library::activity::ActivityManager> activityManager,
    std::shared_ptr<ActivityRequestTransformerFactory> requestTransformerFactory) :
        m_id{id},
        m_activityManager{activityManager},
        m_requestTransformerFactory{requestTransformerFactory} {
}

void ActivityManagerTransformer::request(
    std::shared_ptr<multiAgentExperience::activity::ActivityRequestInterface> request) {
    auto activityRequestTransformer = m_requestTransformerFactory->create(m_id, request);
    m_requestStore.storeTransformedRequest(request, activityRequestTransformer);
    m_activityManager->request(activityRequestTransformer);
}

void ActivityManagerTransformer::stop(
    std::shared_ptr<multiAgentExperience::activity::ActivityRequestInterface> request) {
    auto transformedID = m_requestStore.getTransformedRequestId(request);
    stop(transformedID);
    m_requestStore.cleanupTransformedRequest(request);
}

void ActivityManagerTransformer::stop(multiAgentExperience::library::activity::ActivityRequestID id) {
    if (id > 0) {
        m_activityManager->finish(id);
    }
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
