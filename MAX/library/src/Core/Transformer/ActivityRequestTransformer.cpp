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

#include "Core/Transformer/ActivityRequestTransformer.h"

#include "Core/Transformer/ActivityRequestTransformerFactory.h"
#include "Core/Transformer/ActivityTransformer.h"
#include "MultiAgentExperience/Activity/ActivityHandlerInterface.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

ActivityRequestTransformer::ActivityRequestTransformer(
    library::activity::ActivityType activityType,
    std::shared_ptr<ActivityTransformer> activity,
    std::shared_ptr<multiAgentExperience::activity::ActivityHandlerInterface> activityHandlerInterface) :
        library::activity::ActivityRequest(activityType, activity),
        m_activityHandlerInterface{activityHandlerInterface} {
}

void ActivityRequestTransformer::onGranted() {
}

void ActivityRequestTransformer::onDenied() {
    m_activityHandlerInterface->onDenied();
}

void ActivityRequestTransformer::onRemoved() {
}

void ActivityRequestTransformer::onFinished() {
}

void ActivityRequestTransformer::onWaiting() {
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
