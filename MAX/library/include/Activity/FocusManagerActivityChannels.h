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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGERACTIVITYCHANNELS_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGERACTIVITYCHANNELS_H_

#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

#include "ActivityChannels.h"
#include "ActivityTypeToChannelUtils.h"
#include "Control/ControlRegistryFactory.h"
#include "CurrentActivities.h"
#include "CurrentActivityRequests.h"
#include "FocusManager/ChannelObserverInterface.h"
#include "FocusManager/FocusManager.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

class FocusManagerActivityChannels : public ActivityChannels {
public:
    static std::vector<FocusManager::ChannelConfiguration> getChannelConfigurations() {
        std::vector<FocusManager::ChannelConfiguration> channelConfigs;
        channelConfigs.emplace_back(getChannelForActivityType(ActivityType::DIALOG), 1);
        channelConfigs.emplace_back(getChannelForActivityType(ActivityType::COMMUNICATIONS), 2);
        channelConfigs.emplace_back(getChannelForActivityType(ActivityType::ALERTS), 3);
        channelConfigs.emplace_back(getChannelForActivityType(ActivityType::CONTENT), 4);
        return channelConfigs;
    }

    FocusManagerActivityChannels(
        std::shared_ptr<FocusManager> focusManager,
        std::shared_ptr<CurrentActivityRequests> activityRequests,
        std::shared_ptr<CurrentActivities> currentActivities,
        std::shared_ptr<control::ControlRegistryFactory> controlRegistryFactory);

    ~FocusManagerActivityChannels();

    /// @name ActivityChannels method overrides.
    /// @{
    bool add(std::shared_ptr<ActivityRequestLifecycle> activityRequest) override;
    void remove(const ActivityRequestID activityRequestId) override;
    /// @}

private:
    struct ChannelRecord {
    public:
        ChannelRecord(std::string channel_name, std::shared_ptr<ChannelObserverInterface> observer) :
                m_channelName(channel_name),
                m_observer(observer) {
        }
        const std::string m_channelName;
        const std::shared_ptr<ChannelObserverInterface> m_observer;
    };

    std::mutex m_channelRecordsMutex;
    std::shared_ptr<FocusManager> m_focusManager;
    std::shared_ptr<CurrentActivityRequests> m_currentActivityRequests;
    std::shared_ptr<CurrentActivities> m_currentActivities;
    std::shared_ptr<control::ControlRegistryFactory> m_controlRegistryFactory;
    std::unordered_map<ActivityRequestID, std::shared_ptr<ChannelRecord>> m_channelRecords;
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGERACTIVITYCHANNELS_H_
