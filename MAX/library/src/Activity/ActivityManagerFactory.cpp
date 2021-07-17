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

#include "Activity/ActivityManagerFactory.h"

#include "Activity/ActivityManager.h"
#include "Activity/CurrentActivities.h"
#include "Activity/CurrentActivityRequests.h"
#include "Activity/FocusManagerActivityChannels.h"
#include "Activity/FocusManager/FocusManager.h"
#include "Activity/LoggingActivityTracker.h"
#include "Control/Control.h"
#include "Control/ControlRegistryFactory.h"
#include "Control/ControlStore.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

std::shared_ptr<ActivityManager> ActivityManagerFactory::create(
    std::shared_ptr<control::ControlRegistryFactory> controlRegistryFactory,
    const bool async) {
    auto executor = std::make_shared<multiAgentExperience::library::utils::threading::Executor>(async);
    auto loggingActivityTracker = std::make_shared<LoggingActivityTracker>();
    auto focusManager = std::make_shared<FocusManager>(
        FocusManagerActivityChannels::getChannelConfigurations(), executor, loggingActivityTracker);
    auto currentActivityRequests = std::make_shared<CurrentActivityRequests>();
    auto currentActivities = std::make_shared<CurrentActivities>();
    auto activityChannels = std::make_shared<FocusManagerActivityChannels>(
        focusManager, currentActivityRequests, currentActivities, controlRegistryFactory);

    return std::make_shared<ActivityManager>(activityChannels, currentActivityRequests);
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
