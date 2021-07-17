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

#include "Activity/FocusManagerActivityChannels.h"

#include "Activity/ActivityChannels.h"
#include "Activity/ActivityRequestID.h"
#include "Activity/ActivityRequestLifecycle.h"
#include "Activity/ChannelToActivityObserver.h"
#include "Activity/CurrentActivityRequests.h"
#include "Activity/FocusManager/FocusManager.h"
#include "Control/ControlPriority.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

static control::ControlPriority convertActivityTypeToControlPriority(const ActivityType& activityType) {
    switch (activityType) {
        case ActivityType::DIALOG:
            return control::ControlPriority::DIALOG;
        case ActivityType::COMMUNICATIONS:
            return control::ControlPriority::COMMUNICATIONS;
        case ActivityType::ALERTS:
            return control::ControlPriority::ALERTS;
        case ActivityType::CONTENT:
            return control::ControlPriority::CONTENT;
        default:
            return control::ControlPriority::DEVICE;
    }
}

FocusManagerActivityChannels::FocusManagerActivityChannels(
    std::shared_ptr<FocusManager> focusManager,
    std::shared_ptr<CurrentActivityRequests> activityRequests,
    std::shared_ptr<CurrentActivities> currentActivities,
    std::shared_ptr<control::ControlRegistryFactory> controlRegistryFactory) :
        m_channelRecordsMutex(),
        m_focusManager(focusManager),
        m_currentActivityRequests(activityRequests),
        m_currentActivities(currentActivities),
        m_controlRegistryFactory(controlRegistryFactory) {
}

bool FocusManagerActivityChannels::add(std::shared_ptr<ActivityRequestLifecycle> activityRequest) {
    ActivityRequestID id = activityRequest->getID();
    auto channelName = getChannelForActivityType(activityRequest->getActivityType());
    auto controlPriority = convertActivityTypeToControlPriority(activityRequest->getActivityType());
    auto observer = std::make_shared<ChannelToActivityObserver>(
        m_currentActivityRequests, m_currentActivities, controlPriority, m_controlRegistryFactory, id);

    {
        std::unique_lock<std::mutex> lock(m_channelRecordsMutex);
        auto record = std::make_shared<ChannelRecord>(channelName, observer);
        m_channelRecords.insert(std::make_pair(id, record));
    }

    return m_focusManager->acquireChannel(channelName, observer, std::to_string(id));
}

void FocusManagerActivityChannels::remove(const ActivityRequestID activityRequestId) {
    m_currentActivityRequests->finish(activityRequestId);
    std::shared_ptr<ChannelRecord> record;
    {
        std::unique_lock<std::mutex> lock(m_channelRecordsMutex);
        auto activityRequestEntry = m_channelRecords.find(activityRequestId);
        if (activityRequestEntry != m_channelRecords.end()) {
            record = activityRequestEntry->second;
            m_channelRecords.erase(activityRequestId);
        }
    }

    if (record) {
        m_focusManager->releaseChannel(record->m_channelName, record->m_observer);
    }
}

FocusManagerActivityChannels::~FocusManagerActivityChannels() {
    for (auto& recordEntry : m_channelRecords) {
        auto record = recordEntry.second;
        m_focusManager->releaseChannel(record->m_channelName, record->m_observer);
    }
    m_channelRecords.clear();
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
