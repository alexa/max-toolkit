/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
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

class FocusManagerActivityChannels
        : public ActivityChannels
        , public std::enable_shared_from_this<FocusManagerActivityChannels> {
public:
    static std::vector<FocusManager::ChannelConfiguration> getChannelConfigurations(
    const std::map<
        multiAgentExperience::activity::ActivityType,
        multiAgentExperience::application::ActivitySchedulingPolicy>& activitySchedulingPolicyMap) {

        std::vector<FocusManager::ChannelConfiguration> channelConfigs;
        channelConfigs.emplace_back(
            getChannelForActivityType(ActivityType::DIALOG), 1);
        channelConfigs.emplace_back(
            getChannelForActivityType(ActivityType::COMMUNICATIONS), 2, activitySchedulingPolicyMap.at(multiAgentExperience::activity::ActivityType::COMMUNICATION));
        channelConfigs.emplace_back(
            getChannelForActivityType(ActivityType::ALERTS), 3, activitySchedulingPolicyMap.at(multiAgentExperience::activity::ActivityType::ALERTS));
        channelConfigs.emplace_back(
            getChannelForActivityType(ActivityType::NOTIFICATIONS), 4, activitySchedulingPolicyMap.at(multiAgentExperience::activity::ActivityType::NOTIFICATIONS));
        channelConfigs.emplace_back(
            getChannelForActivityType(ActivityType::CONTENT), 5, activitySchedulingPolicyMap.at(multiAgentExperience::activity::ActivityType::CONTENT));

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
    ActivityLifecyclesSortedByPriorityAndActivityId getAllActivitiesSortedByPriority() override;
    /// @}

    /**
     * Cleans up any objects associated with the @c ActivityRequestID ID
     *
     * @param activityRequestId The activity request ID whose related objects are cleaned up
     */
    void cleanup(const ActivityRequestID activityRequestId);

    /**
     * Checks if the ChannelRecord associated with @c ActivityRequestID activityRequestId is present.
     *
     * @param activityRequestId The activity request ID who ChannelRecord is to be checked
     * @return true if ChannelRecord associated with @c ActivityRequestID activityRequestId is present. False, otherwise.
     */
    bool isChannelRecordPresent(const ActivityRequestID activityRequestId);

    /**
     * A callback, which when executed, invokes FocusManagerActivityChannels::cleanup to cleanup any objects like
     * ChannelRecords for the respective @c ActivityRequestID ID.
     */
    struct CleanupCallback {
    public:
        /**
         * Constructor.
         *
         * @param focusManagerActivityChannels A weak_ptr to the FocusManagerActivityChannels object
         * @param id The ActivityRequestID whose related objects are cleaned up
         */
        CleanupCallback(std::weak_ptr<FocusManagerActivityChannels> focusManagerActivityChannels, ActivityRequestID id);

        /**
         * Executes FocusManagerActivityChannels::cleanup for the activity request ID in @c m_id.
         */
        void operator()();

    private:
        std::weak_ptr<FocusManagerActivityChannels> m_focusManagerActivityChannels;
        ActivityRequestID m_id;
    };

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
