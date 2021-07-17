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

#include "Activity/FocusManager/InterruptModel.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

std::shared_ptr<InterruptModel> InterruptModel::create() {
    return std::make_shared<InterruptModel>();
}

MixingBehavior InterruptModel::getMixingBehavior(
    const std::string& lowPrioChannel,
    ContentType lowPrioContentType,
    const std::string& highPrioChannel,
    ContentType highPrioContentType) const {
    return MixingBehavior::MUST_PAUSE;
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
