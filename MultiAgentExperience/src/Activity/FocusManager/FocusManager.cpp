/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <algorithm>

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Activity/ActivityTypeToChannelUtils.h"
#include "Activity/FocusManager/FocusManager.h"
#include "Core/Transformer/TransformerUtils.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

static const std::string MODULE_TAG("FocusManager");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

/// Key for @c FocusManager configurations in configuration node.
static const std::string VIRTUAL_CHANNELS_CONFIG_KEY = "virtualChannels";

/// Key for the name of the channel in configuration node.
static const std::string CHANNEL_NAME_KEY = "name";

/// Key for the priority of the channel in configuration node.
static const std::string CHANNEL_PRIORITY_KEY = "priority";

FocusManager::FocusManager(
    const std::vector<ChannelConfiguration>& channelConfigurations,
    std::shared_ptr<multiAgentExperience::library::utils::threading::Executor> executor,
    std::shared_ptr<ActivityTrackerInterface> activityTrackerInterface,
    const std::vector<ChannelConfiguration>& virtualChannelConfigurations) :
        m_activityTracker{activityTrackerInterface},
        m_executor(executor) {
    // Read channel configurations.
    createChannelFromConfiguration(channelConfigurations, false);
    // Read virtual channel configurations.
    createChannelFromConfiguration(virtualChannelConfigurations, true);
}

bool FocusManager::acquireChannel(
    const std::string& channelName,
    std::shared_ptr<ChannelObserverInterface> channelObserver,
    const std::string& interfaceName,
    const MixabilityType& mixabilityType) {
    LX(DEBUG3, "channelName:" + channelName + ", interface:" + interfaceName);
    std::shared_ptr<Channel> channelToAcquire = getChannel(channelName);
    if (!channelToAcquire) {
        LX(ERROR, "acquireChannelFailed. reason:channelNotFound, channelName:" + channelName);
        return false;
    }

    auto channelActivity =
            FocusManagerInterface::Activity::create(interfaceName, channelObserver, mixabilityType);
    if (!channelActivity) {
        LX(ERROR, "acquireChannelFailed,reason:failedToCreateActivity,interface:" + interfaceName);
        return false;
    }

    m_executor->submit(
        [this, channelToAcquire, channelActivity]() { acquireChannelHelper(channelToAcquire, channelActivity); });
    return true;
}

bool FocusManager::acquireChannel(
    const std::string& channelName,
    std::shared_ptr<FocusManagerInterface::Activity> channelActivity) {
    LX(DEBUG3, "channelName:" + channelName + ", interface:" + channelActivity->getInterface());
    std::shared_ptr<Channel> channelToAcquire = getChannel(channelName);
    if (!channelToAcquire) {
        LX(ERROR, "acquireChannelFailed,reason:channelNotFound,channelName: " + channelName);
        return false;
    }

    if (!channelActivity) {
        LX(ERROR, "acquireChannelFailed,reason:channelActivityIsNull");
        return false;
    }

    m_executor->submit(
        [this, channelToAcquire, channelActivity]() { acquireChannelHelper(channelToAcquire, channelActivity); });
    return true;
}

std::future<bool> FocusManager::releaseChannel(
    const std::string& channelName,
    std::shared_ptr<ChannelObserverInterface> channelObserver) {
    LX(DEBUG3, "channelName:" + channelName);

    // Using a shared_ptr here so that the promise stays in scope by the time the Executor picks up the task.
    auto releaseChannelSuccess = std::make_shared<std::promise<bool>>();
    std::future<bool> returnValue = releaseChannelSuccess->get_future();
    std::shared_ptr<Channel> channelToRelease = getChannel(channelName);
    if (!channelToRelease) {
        LX(ERROR, "releaseChannelFailed,reason:channelNotFound,channelName:" + channelName);
        releaseChannelSuccess->set_value(false);
        return returnValue;
    }

    m_executor->submit([this, channelToRelease, channelObserver, releaseChannelSuccess, channelName]() {
        releaseChannelHelper(channelToRelease, channelObserver, releaseChannelSuccess, channelName);
    });

    return returnValue;
}

void FocusManager::stopForegroundActivity() {
    LX(DEBUG3, "");

    // We lock these variables so that we can correctly capture the currently foregrounded channel and activity.
    std::unique_lock<std::mutex> lock(m_mutex);
    std::shared_ptr<Channel> foregroundChannel = getHighestPriorityActiveChannelLocked();
    if (!foregroundChannel) {
        LX(DEBUG3, "stopForegroundActivityFailed,reason:noForegroundActivity");
        return;
    }

    std::string foregroundChannelInterface = foregroundChannel->getInterface();
    lock.unlock();

    m_executor->submitToFront([this, foregroundChannel, foregroundChannelInterface]() {
        stopForegroundActivityHelper(foregroundChannel, foregroundChannelInterface);
    });
}

void FocusManager::stopAllActivities() {
    LX(DEBUG3, "");

    if (m_activeChannels.empty()) {
        LX(DEBUG3, "no active channels");
        return;
    }

    ChannelsToInterfaceNamesMap channelOwnersCapture;
    std::unique_lock<std::mutex> lock(m_mutex);

    for (const auto& channel : m_activeChannels) {
        for (const auto& interfaceName : channel->getInterfaceList()) {
            channelOwnersCapture.insert(std::pair<std::shared_ptr<Channel>, std::string>(channel, interfaceName));
        }
    }

    lock.unlock();

    m_executor->submitToFront([this, channelOwnersCapture]() { stopAllActivitiesHelper(channelOwnersCapture); });
}

void FocusManager::addObserver(const std::shared_ptr<FocusManagerObserverInterface>& observer) {
    LX(DEBUG3, "");
    std::lock_guard<std::mutex> lock(m_mutex);
    m_observers.insert(observer);
}

void FocusManager::removeObserver(const std::shared_ptr<FocusManagerObserverInterface>& observer) {
    LX(DEBUG3, "");
    std::lock_guard<std::mutex> lock(m_mutex);
    m_observers.erase(observer);
}

void FocusManager::createChannelFromConfiguration(
    const std::vector<ChannelConfiguration>& channelConfigurations,
    bool isVirtual) {
    LX(DEBUG3, "");

    for (const auto& config : channelConfigurations) {
        if (doesChannelNameExist(config.name)) {
            LX(ERROR, "readChannelConfigurationFailed,reason:channelNameExists,config:" + config.toString());
            continue;
        }
        if (doesChannelPriorityExist(config.priority)) {
            LX(ERROR, "readChannelConfigurationFailed,reason:channelPriorityExists, config:" + config.toString());
            continue;
        }

        auto channel = std::make_shared<Channel>(config.name, config.priority, config.activitySchedulingPolicy, isVirtual);
        m_allChannels.insert({config.name, channel});
    }
}

void FocusManager::setChannelFocus(
    const std::shared_ptr<Channel>& channel,
    FocusState focus,
    MixingBehavior behavior,
    bool forceUpdate) {
    LX(DEBUG3, "");

    if (!channel->setFocus(focus, behavior, forceUpdate)) {
        return;
    }

    std::unique_lock<std::mutex> lock(m_mutex);
    // take a copy of the observers
    auto observers = m_observers;
    lock.unlock();

    // inform copy of the observers in an unlocked content
    for (auto& observer : observers) {
        observer->onFocusChanged(channel->getName(), focus);
    }
}

MixingBehavior FocusManager::getMixingBehavior(
    std::shared_ptr<Channel> lowPrioChannel,
    std::shared_ptr<Channel> highPrioChannel,
    MixingBehavior& mostRestrictiveMixingBehavior) {
    LX(DEBUG3, "");

    if (!lowPrioChannel || !highPrioChannel) {
        LX(ERROR, "getMixingBehaviorFailed,reason:nullInputChannels");
        return MixingBehavior::UNRESTRICTED;
    }

    if (*lowPrioChannel > *highPrioChannel) {
        std::stringstream ss;
        ss << "getMixingBehaviorFailed:,reason:Priorities of input channels violate API contract,lowPrioChannel "
           << "priority:" << lowPrioChannel->getPriority()
           << ",highPrioChannel priority:" << highPrioChannel->getPriority();
        LX(ERROR, ss.str());

        return MixingBehavior::UNRESTRICTED;
    }

    auto lowPrioChannelName = lowPrioChannel->getName();
    auto lowPrioChannelPrimaryActivity = lowPrioChannel->getPrimaryActivity();
    if (!lowPrioChannelPrimaryActivity) {
        LX(ERROR, "getMixingBehaviorFailed,No PrimaryActivity on lowPrioChannel:" + lowPrioChannelName);
        return MixingBehavior::UNRESTRICTED;
    }

    auto highPrioChannelName = highPrioChannel->getName();
    auto highPrioChannelPrimaryActivity = highPrioChannel->getPrimaryActivity();
    if (!highPrioChannelPrimaryActivity) {
        LX(ERROR, "getMixingBehaviorFailed,No PrimaryActivity on highPrioChannel:" + highPrioChannelName);
        return MixingBehavior::UNRESTRICTED;
    }

    return getMixingBehavior(
        lowPrioChannelPrimaryActivity->getMixabilityType(),
        highPrioChannelPrimaryActivity->getMixabilityType(),
        mostRestrictiveMixingBehavior);
}

MixingBehavior FocusManager::getMixingBehavior(
        multiAgentExperience::library::activity::MixabilityType lowPriorityMixabilityType,
        multiAgentExperience::library::activity::MixabilityType highPriorityMixabilityType,
        MixingBehavior& mostRestrictiveMixingBehavior) {

    MixingBehavior newMixingBehavior;

    switch (highPriorityMixabilityType) {
        case MixabilityType::NONMIXABLE:
            newMixingBehavior = MixingBehavior::MUST_PAUSE;
            break;

        case MixabilityType::MIXABLE_RESTRICTED:
            newMixingBehavior = lowPriorityMixabilityType == MixabilityType::NONMIXABLE?
                MixingBehavior::MUST_PAUSE: MixingBehavior::MUST_ATTENUATE;
            break;

        case MixabilityType::MIXABLE_UNRESTRICTED:
            newMixingBehavior = MixingBehavior::UNRESTRICTED;
            break;
    }

    // If the new MixingBehavior determined for the channel is more restrictive than `mostRestrictiveMixingBehavior`,
    // then overwrite it.
    if (newMixingBehavior > mostRestrictiveMixingBehavior)
        mostRestrictiveMixingBehavior = newMixingBehavior;

    return mostRestrictiveMixingBehavior;
}

void FocusManager::acquireChannelHelper(
    std::shared_ptr<Channel> channelToAcquire,
    std::shared_ptr<FocusManagerInterface::Activity> channelActivity) {
    LX(DEBUG3, "");

    // Lock here to update internal state which stopForegroundActivity may concurrently access.
    std::unique_lock<std::mutex> lock(m_mutex);
    std::shared_ptr<Channel> foregroundChannel = getHighestPriorityActiveChannelLocked();
    // insert the incoming channel
    m_activeChannels.insert(channelToAcquire);
    lock.unlock();

    LX(DEBUG2,
       "incomingChannel:" + channelToAcquire->getName() + ",incomingInterface:" + channelActivity->getInterface());

    // attach Activity to the Channel
    channelToAcquire->setPrimaryActivity(std::move(channelActivity));

    if (!foregroundChannel) {
        // channelToAcquire is the only active channel
        setChannelFocus(channelToAcquire, FocusState::FOREGROUND, MixingBehavior::UNRESTRICTED);
    } else if (foregroundChannel == channelToAcquire) {
        // acquireChannel request is for the same channel as the current foreground channel
        // NOTE : the primaryActivity interface may change , even though focus state has not changed for the channel
        setChannelFocus(channelToAcquire, FocusState::FOREGROUND, MixingBehavior::UNRESTRICTED, true);
    } else if (*channelToAcquire > *foregroundChannel) {
        // channelToAcquire will now become the foreground channel, other channels shall be backgrounded
        // For each background channel : consult interrupt model to determine the mixability
        // INFO: there is no need to set mixing behavior as it is not used. And for some reason this is causing a seg
        // fault
        setBackgroundChannelMixingBehavior(channelToAcquire);

        // set channelToAcquire as Foreground
        setChannelFocus(channelToAcquire, FocusState::FOREGROUND, MixingBehavior::UNRESTRICTED);
    } else {
        // channelToAcquire is to be backgrounded and mixing behaviors need to be recalculated
        setBackgroundChannelMixingBehavior(foregroundChannel);
    }

    notifyActivityTracker();
}

void FocusManager::releaseChannelHelper(
    std::shared_ptr<Channel> channelToRelease,
    std::shared_ptr<ChannelObserverInterface> channelObserver,
    std::shared_ptr<std::promise<bool>> releaseChannelSuccess,
    const std::string& name) {
    LX(DEBUG3, "channelToRelease:" + channelToRelease->getName());

    bool success = channelToRelease->releaseActivity(std::move(channelObserver));
    releaseChannelSuccess->set_value(success);

    if (!success) {
        LX(ERROR,
           "reason:releaseActivityFailed, channel:" + channelToRelease->getName() + ", interface" +
               channelToRelease->getInterface());
        return;
    }

    // Only release and set entire channel focus to NONE if there are no active Activity remaining.
    if (!channelToRelease->isActive()) {
        // Lock here to update internal state which stopForegroundActivity may concurrently access.
        std::unique_lock<std::mutex> lock(m_mutex);
        m_activeChannels.erase(channelToRelease);
        lock.unlock();
        setChannelFocus(channelToRelease, FocusState::NONE, MixingBehavior::MUST_PAUSE);
    }
    foregroundHighestPriorityActiveChannel();
    notifyActivityTracker();
}

void FocusManager::stopForegroundActivityHelper(
    std::shared_ptr<Channel> foregroundChannel,
    std::string foregroundChannelInterface) {
    LX(DEBUG3, "");

    if (foregroundChannelInterface != foregroundChannel->getInterface()) {
        return;
    }
    LX(DEBUG3, "interface:" + foregroundChannelInterface);
    bool success = foregroundChannel->releaseActivity(foregroundChannel->getInterface());
    if (!success) {
        LX(ERROR,
           "releaseActivityFailed, channel:" + foregroundChannel->getName() +
               ", interface:" + foregroundChannel->getInterface());
    }

    // Only release and set entire channel focus to NONE if there are no active Activity remaining.
    if (!foregroundChannel->isActive()) {
        LX(DEBUG1, "Channel is not active ... releasing");
        // Lock here to update internal state which stopForegroundActivity may concurrently access.
        std::unique_lock<std::mutex> lock(m_mutex);
        m_activeChannels.erase(foregroundChannel);
        lock.unlock();
        setChannelFocus(foregroundChannel, FocusState::NONE, MixingBehavior::MUST_PAUSE);
    }
    foregroundHighestPriorityActiveChannel();
    notifyActivityTracker();
}

void FocusManager::stopAllActivitiesHelper(const ChannelsToInterfaceNamesMap& channelsOwnersMap) {
    LX(DEBUG3, "");

    std::set<std::shared_ptr<Channel>> channelsToClear;

    std::unique_lock<std::mutex> lock(m_mutex);

    for (const auto& channelAndInterface : channelsOwnersMap) {
        auto channel = channelAndInterface.first;
        auto interfaceName = channelAndInterface.second;
        LX(DEBUG1, "channel:" + channel->getName() + ", interface:" + interfaceName);

        bool success = channel->releaseActivity(channelAndInterface.second);
        if (!success) {
            LX(ERROR, "releaseActivityFailed, channel:" + channel->getName() + ", interface" + interfaceName);
        }
        channelsToClear.insert(channel);
    }

    lock.unlock();

    for (const auto& channel : channelsToClear) {
        // Only release and set entire channel focus to NONE if there are no active Activity remaining.
        if (!channel->isActive()) {
            // Lock here to update internal state which stopForegroundActivity may concurrently access.
            std::unique_lock<std::mutex> activeChannelsLock(m_mutex);
            m_activeChannels.erase(channel);
            activeChannelsLock.unlock();
            setChannelFocus(channel, FocusState::NONE, MixingBehavior::MUST_PAUSE);
        }
    }
    foregroundHighestPriorityActiveChannel();
    notifyActivityTracker();
}

std::shared_ptr<Channel> FocusManager::getChannel(const std::string& channelName) const {
    LX(DEBUG3, "");

    auto search = m_allChannels.find(channelName);
    if (search != m_allChannels.end()) {
        return search->second;
    }
    return nullptr;
}

std::shared_ptr<Channel> FocusManager::getHighestPriorityActiveChannelLocked() const {
    LX(DEBUG3, "");

    if (m_activeChannels.empty()) {
        return nullptr;
    }
    return *m_activeChannels.begin();
}

bool FocusManager::isChannelForegroundedLocked(const std::shared_ptr<Channel>& channel) const {
    LX(DEBUG3, "");

    return getHighestPriorityActiveChannelLocked() == channel;
}

bool FocusManager::doesChannelNameExist(const std::string& name) const {
    LX(DEBUG3, "");

    return m_allChannels.find(name) != m_allChannels.end();
}

bool FocusManager::doesChannelPriorityExist(const unsigned int priority) const {
    LX(DEBUG3, "");

    for (const auto& m_allChannel : m_allChannels) {
        if (m_allChannel.second->getPriority() == priority) {
            return true;
        }
    }
    return false;
}

void FocusManager::modifyMixabilityType(
        const std::string& channelName,
        const std::string& interfaceName,
        MixabilityType mixabilityType) {
    LX(DEBUG3, "");

    // find the channel
    auto channel = getChannel(channelName);
    if (!channel) {
        LX(ERROR, "modifyMixabilityTypeFailed,reason:channelNotFound,channel:" + channelName);
        return;
    }

    // find the activity associated with the interfacename in the channel
    auto activity = channel->getActivity(interfaceName);
    if (!activity) {
        LX(ERROR, "no activity found associated with interfaceName:" + interfaceName);
        return;
    }

    if (mixabilityType == activity->getMixabilityType()) {
        LX(ERROR, "no mixabilityType to modify it is already identical: " + mixabilityTypeToString(mixabilityType));
        return;
    }

    // modify the mixabilityType associated with the activity
    activity->setMixabilityType(mixabilityType);

    // reconsult the InterruptModel and set the new MixingBehaviors for all backgrounded channelobservers
    std::unique_lock<std::mutex> lock(m_mutex);
    std::shared_ptr<Channel> foregroundChannel = getHighestPriorityActiveChannelLocked();
    lock.unlock();
    setBackgroundChannelMixingBehavior(foregroundChannel);
}

void FocusManager::setBackgroundChannelMixingBehavior(std::shared_ptr<Channel> foregroundChannel) {
    LX(DEBUG3, "");

    std::unique_lock<std::mutex> lock(m_mutex);

    auto channelIter = m_activeChannels.find(foregroundChannel);
    if (channelIter == m_activeChannels.end()) {
        LX(ERROR, "Could not find channel:" + foregroundChannel->getName());
        return;
    }
    // skip to the next channel in priority
    channelIter++;

    /**
     * When determining the MixingBehavior of a background channel, we need to check if any higher priority background channel
     * has a more restrictive MixingBehavior. For example, if the (higher priority) ALERTS channel is NONMIXABLE and
     * the CONTENT channel is MIXABLE_RESTRICTED, the more restrictive behavior of the two is NONMIXABLE. Hence, NONMIXABLE
     * would be applied to the CONTENT channel as well.
     *
     * Hence we keep track of the more restrictive MixingBehaviors while going down the background channel.
     */
    MixingBehavior mostRestrictiveMixingBehavior = MixingBehavior::UNRESTRICTED;

    for (; channelIter != m_activeChannels.end(); channelIter++) {
        // determine mixingBehavior for each background channel
        auto mixingBehavior = getMixingBehavior(*channelIter, foregroundChannel, mostRestrictiveMixingBehavior);
        lock.unlock();
        setChannelFocus(*channelIter, FocusState::BACKGROUND, mixingBehavior);
        lock.lock();
    }
}

void FocusManager::foregroundHighestPriorityActiveChannel() {
    LX(DEBUG3, "");

    std::unique_lock<std::mutex> lock(m_mutex);
    std::shared_ptr<Channel> channelToForeground = getHighestPriorityActiveChannelLocked();
    lock.unlock();

    if (channelToForeground) {
        // inform background channels of the new MixingBehavior as per the new Foreground Channel
        setBackgroundChannelMixingBehavior(channelToForeground);

        // Foreground the highest priority channel
        setChannelFocus(channelToForeground, FocusState::FOREGROUND, MixingBehavior::UNRESTRICTED);
    }
}

void FocusManager::notifyActivityTracker() {
    LX(DEBUG3, "");

    std::unique_lock<std::mutex> lock(m_mutex);
    for (const auto& channel : m_allChannels) {
        auto activityUpdates = channel.second->getActivityUpdates();
        for (const auto& activity : activityUpdates) {
            m_activityUpdates.push_back(activity);
            LX(DEBUG1,
               "name:" + activity.name + ", interfaceName:" + activity.interfaceName +
                   ", focusState:" + focusStateToString(activity.focusState));
        }
    }
    lock.unlock();

    if (m_activityTracker && !m_activityUpdates.empty()) {
        m_activityTracker->notifyOfActivityUpdates(m_activityUpdates);
    }
    m_activityUpdates.clear();
}

const std::vector<FocusManager::ChannelConfiguration> FocusManager::getDefaultAudioChannels() {
    LX(DEBUG3, "");

    static const std::vector<FocusManager::ChannelConfiguration> defaultAudioChannels = {
        {FocusManagerInterface::DIALOG_CHANNEL_NAME, FocusManagerInterface::DIALOG_CHANNEL_PRIORITY},
        {FocusManagerInterface::ALERT_CHANNEL_NAME, FocusManagerInterface::ALERT_CHANNEL_PRIORITY},
        {FocusManagerInterface::COMMUNICATIONS_CHANNEL_NAME, FocusManagerInterface::COMMUNICATIONS_CHANNEL_PRIORITY},
        {FocusManagerInterface::NOTIFICATIONS_CHANNEL_NAME, FocusManagerInterface::NOTIFICATIONS_CHANNEL_PRIORITY},
        {FocusManagerInterface::CONTENT_CHANNEL_NAME, FocusManagerInterface::CONTENT_CHANNEL_PRIORITY}};

    return defaultAudioChannels;
}

const std::vector<FocusManager::ChannelConfiguration> FocusManager::getDefaultVisualChannels() {
    LX(DEBUG3, "");

    static const std::vector<FocusManager::ChannelConfiguration> defaultVisualChannels = {
        {FocusManagerInterface::VISUAL_CHANNEL_NAME, FocusManagerInterface::VISUAL_CHANNEL_PRIORITY}};

    return defaultVisualChannels;
}

bool activity::FocusManager::ChannelConfiguration::readChannelConfiguration(
    const std::string& channelTypeKey,
    std::vector<activity::FocusManager::ChannelConfiguration>* virtualChannelConfigurations) {
    LX(DEBUG3, "");

    if (!virtualChannelConfigurations) {
        LX(ERROR, "reason:nullVirtualChannelConfiguration");
        return false;
    }

    bool returnValue = true;
    if (channelTypeKey == VIRTUAL_CHANNELS_CONFIG_KEY) {
        /**
         * This was modified to hard code virtual channels instead of having a dependency on ConfigurationNode.
         */

        activity::FocusManager::ChannelConfiguration earconConfig{"Earcon", static_cast<unsigned int>(250)};
        virtualChannelConfigurations->push_back(earconConfig);
        activity::FocusManager::ChannelConfiguration hpdConfig{"HighPriorityDucking", static_cast<unsigned int>(175)};
        virtualChannelConfigurations->push_back(hpdConfig);
    }

    return returnValue;
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience
