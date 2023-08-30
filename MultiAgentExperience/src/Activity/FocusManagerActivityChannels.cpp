/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Activity/FocusManagerActivityChannels.h"

#include "Activity/ActivityRequestID.h"
#include "Activity/ActivityRequestLifecycle.h"
#include "Activity/ChannelToActivityObserver.h"
#include "Activity/CurrentActivityRequests.h"
#include "Activity/FocusManager/FocusManager.h"
#include "Control/ControlPriority.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

static const std::string MODULE_TAG("FocusManagerActivityChannels");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

static control::ControlPriority convertActivityTypeToControlPriority(const ActivityType& activityType) {
    switch (activityType) {
        case ActivityType::DIALOG:
            return control::ControlPriority::DIALOG;
        case ActivityType::COMMUNICATIONS:
            return control::ControlPriority::COMMUNICATIONS;
        case ActivityType::ALERTS:
            return control::ControlPriority::ALERTS;
        case ActivityType::NOTIFICATIONS:
            return control::ControlPriority::NOTIFICATIONS;
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
    LX(DEBUG3, "");

    ActivityRequestID id = activityRequest->getID();
    auto channelName = getChannelForActivityType(activityRequest->getActivityType());
    auto controlPriority = convertActivityTypeToControlPriority(activityRequest->getActivityType());
    auto cleanupCallback = std::make_shared<CleanupCallback>(shared_from_this(), id);
    auto observer = std::make_shared<ChannelToActivityObserver>(
        m_currentActivityRequests, m_currentActivities, controlPriority, m_controlRegistryFactory, id, cleanupCallback);

    {
        std::unique_lock<std::mutex> lock(m_channelRecordsMutex);
        auto record = std::make_shared<ChannelRecord>(channelName, observer);
        m_channelRecords.insert(std::make_pair(id, record));
    }

    return m_focusManager->acquireChannel(channelName,
                                          observer,
                                          std::to_string(id),
                                          activityRequest->getMixabilityType());
}

void FocusManagerActivityChannels::remove(const ActivityRequestID activityRequestId) {
    LX(DEBUG3, "");

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

void FocusManagerActivityChannels::cleanup(
    const multiAgentExperience::library::activity::ActivityRequestID activityRequestId) {
    LX(DEBUG3, "");

    std::unique_lock<std::mutex> lock(m_channelRecordsMutex);
    auto activityRequestEntry = m_channelRecords.find(activityRequestId);
    if (activityRequestEntry != m_channelRecords.end()) {
        m_channelRecords.erase(activityRequestId);
    }
}

bool FocusManagerActivityChannels::isChannelRecordPresent(
    const multiAgentExperience::library::activity::ActivityRequestID activityRequestId) {

    std::unique_lock<std::mutex> lock(m_channelRecordsMutex);
    return m_channelRecords.find(activityRequestId) != m_channelRecords.end();
}

ActivityLifecyclesSortedByPriorityAndActivityId FocusManagerActivityChannels::getAllActivitiesSortedByPriority() {
    return m_currentActivities->getAllActivitiesSortedByPriority();
}

FocusManagerActivityChannels::~FocusManagerActivityChannels() {
    for (auto& recordEntry : m_channelRecords) {
        auto record = recordEntry.second;
        m_focusManager->releaseChannel(record->m_channelName, record->m_observer);
    }
    m_channelRecords.clear();
}

FocusManagerActivityChannels::CleanupCallback::CleanupCallback(
    std::weak_ptr<FocusManagerActivityChannels> focusManagerActivityChannels,
    multiAgentExperience::library::activity::ActivityRequestID id) :
    m_focusManagerActivityChannels{focusManagerActivityChannels},
    m_id{id} {
}

void FocusManagerActivityChannels::CleanupCallback::operator()() {
    if (auto focusManagerActivityChannels = m_focusManagerActivityChannels.lock()) {
        focusManagerActivityChannels->cleanup(m_id);
    }
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
