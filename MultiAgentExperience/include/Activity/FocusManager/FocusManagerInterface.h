/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGER_FOCUSMANAGERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGER_FOCUSMANAGERINTERFACE_H_

#include <future>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#include "ChannelObserverInterface.h"
#include "FocusManagerObserverInterface.h"
#include "MixabilityType.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

/**
 * A FocusManager takes requests to acquire and release Channels and updates the focuses of other Channels based on
 * their priorities so that the invariant that there can only be one Foreground Channel is held. The following
 * operations are provided:
 *
 * acquire Channel - clients should call the acquireChannel() method, passing in the name of the Channel they wish to
 * acquire, a pointer to the observer that they want to be notified once they get focus, and a unique interface name.
 * clients could alternatively construct an @c Activity object and pass that along with the channel name to acquire the
 * channel.
 *
 * release Channel - clients should call the releaseChannel() method, passing in the name of the Channel and the
 * observer of the Channel they wish to release.
 *
 * stop foreground Channel - clients should call the stopForegroundActivity() method.
 *
 * stop all activities - client should call stopAllActivities
 *
 * All of these methods will notify the observer of the Channel of focus changes via an asynchronous callback to the
 * ChannelObserverInterface##onFocusChanged() method, at which point the client should make a user observable change
 * based on the focus it receives.
 */
class FocusManagerInterface {
public:
    /**
     * An activity representation of an entity (that includes details of a policy) that can acquire a channel.
     */
    class Activity {
    public:
        /**
         * Constructs a new Activity object.
         *
         * @param interfaceName The Activity's interface.
         * @param channelObserver The Activity's Channel Observer.
         * @param mixabilityType The Activity's Mixability Type.
         */
        static std::shared_ptr<Activity> create(
            const std::string& interfaceName,
            const std::shared_ptr<ChannelObserverInterface>& channelObserver,
            const MixabilityType mixabilityType = MixabilityType::MIXABLE_RESTRICTED);

        bool operator==(const Activity& rhs) {
            return this->m_interface == rhs.m_interface;
        }

        /**
         * Returns the name of Activity's AVS interface.
         *
         * @return The name of the AVS interface.
         */
        const std::string getInterface() const;

        /**
         * Returns the @c MixabilityType associated with the @c Activity.
         *
         * @return The @c MixabilityType associated with this @c Activity.
         */
        MixabilityType getMixabilityType() const;

        /**
         * Sets the @c MixabilityType associated with this @c Activity.
         *
         * @param mixabilityType The @c MixabilityType associated with this @c Activity.
         */
        void setMixabilityType(MixabilityType mixabilityType);

        /**
         * Gets the last @c MixingBehavior set for this Activity.
         *
         * @param The @c MixingBehavior to be set for this @c Activity
         */
        MixingBehavior getMixingBehavior() const;

        /**
         * Returns the channel observer of Activity.
         *
         * @return The channel observer of Activity.
         */
        std::shared_ptr<ChannelObserverInterface> getChannelObserver() const;

        /**
         * Notifies the channel Observer of focus of Channel and Channel owner interface.
         *
         * @return @c true if observer was notified, else @c false.
         */
        bool notifyObserver(FocusState focus, MixingBehavior behavior);

    private:
        /**
         * Constructs a new Activity object.
         *
         * @param interfaceName The Activity's interface.
         * @param channelObserver The Activity's Channel Observer.
         * @param mixabilityType The Activity's Mixability Type.
         */
        Activity(
            const std::string& interfaceName,
            const std::shared_ptr<ChannelObserverInterface>& channelObserver,
            const MixabilityType mixabilityType) :
                m_interface{interfaceName},
                m_channelObserver{channelObserver},
                m_mixabilityType{mixabilityType},
                m_mixingBehavior{MixingBehavior::UNRESTRICTED} {
        }

        /**
         * Sets the @c MixingBehavior for this @c Activity
         *
         * @param behavior The @c MixingBehavior to be set for this @c Activity.
         */
        void setMixingBehavior(MixingBehavior behavior);

        // The mutex that synchronizes all operations within the activity
        mutable std::mutex m_mutex;

        // The interface name of the Activity.
        const std::string m_interface;

        // The channel observer of the Activity.
        const std::shared_ptr<ChannelObserverInterface> m_channelObserver;

        // The MixabilityType associated with this Activity
        MixabilityType m_mixabilityType;

        // Last MixingBehavior associated with this activity
        MixingBehavior m_mixingBehavior;
    };

    /// The default Dialog Channel name.
    static constexpr const char* DIALOG_CHANNEL_NAME = "Dialog";

    /// The default dialog Channel priority.
    static constexpr unsigned int DIALOG_CHANNEL_PRIORITY = 100;

    /// The default Communications Channel name.
    static constexpr const char* COMMUNICATIONS_CHANNEL_NAME = "Communications";

    /// The default Communications Channel priority.
    static constexpr unsigned int COMMUNICATIONS_CHANNEL_PRIORITY = 150;

    /// The default Alert Channel name.
    static constexpr const char* ALERT_CHANNEL_NAME = "Alert";

    /// The default Alert Channel priority.
    static constexpr unsigned int ALERT_CHANNEL_PRIORITY = 200;

    /// The default Notifications Channel name.
    static constexpr const char* NOTIFICATIONS_CHANNEL_NAME = "Notifications";

    /// The default Notifications Channel priority.
    static constexpr unsigned int NOTIFICATIONS_CHANNEL_PRIORITY = 250;

    /// The default Content Channel name.
    static constexpr const char* CONTENT_CHANNEL_NAME = "Content";

    /// The default Content Channel priority.
    static constexpr unsigned int CONTENT_CHANNEL_PRIORITY = 300;

    /// The default Visual Channel name.
    static constexpr const char* VISUAL_CHANNEL_NAME = "Visual";

    /// The default Visual Channel priority.
    static constexpr unsigned int VISUAL_CHANNEL_PRIORITY = 100;

    /// Destructor.
    virtual ~FocusManagerInterface() = default;

    /**
     * This method will acquire the channel and grant the appropriate focus to it and other channels if needed. The
     * caller will be notified via an ChannelObserverInterface##onFocusChanged() call to the @c channelObserver when
     * it can start the activity.
     *
     * @param channelName The name of the Channel to acquire.
     * @param channelObserver The observer that will be acquiring the Channel and be notified of focus changes.
     * @param interfaceName The name of the AVS interface occupying the Channel. This should be unique and represents
     * the name of the AVS interface using the Channel.  The name of the AVS interface is used by the ActivityTracker to
     * send Context to AVS.
     * @param mixabilityType The parameter which defines how a channel behaves when mixed with other channels
     *
     * @return Returns @c true if the Channel can be acquired and @c false otherwise.
     */
    virtual bool acquireChannel(
        const std::string& channelName,
        std::shared_ptr<ChannelObserverInterface> channelObserver,
        const std::string& interfaceName,
        const MixabilityType& mixabilityType) = 0;

    /**
     * This method will acquire the channel and grant the appropriate focus to it and other channels if needed. The
     * caller will be notified via an ChannelObserverInterface##onFocusChanged() call to the @c channelObserver when
     * it can start the activity.
     *
     * @param channelName The name of the Channel to acquire.
     * @param channelActivity Activity object associated with the Channel.
     *
     * @return Returns @c true if the Channel can be acquired and @c false otherwise.
     */
    virtual bool acquireChannel(
        const std::string& channelName,
        std::shared_ptr<FocusManagerInterface::Activity> channelActivity) = 0;

    /**
     * This method will release the Channel and notify the observer of the Channel, if the observer is the same as the
     * observer passed in the acquireChannel call, to stop via ChannelObserverInterface##onFocusChanged(). If the
     * Channel to release is the current foreground focused Channel, it will also notify the next highest priority
     * Channel via an ChannelObserverInterface##onFocusChanged() callback that it has gained foreground focus.
     *
     * @param channelName The name of the Channel to release.
     * @param channelObserver The observer to be released from the Channel.
     * @return @c std::future<bool> which will contain @c true if the Channel can be released and @c false otherwise.
     */
    virtual std::future<bool> releaseChannel(
        const std::string& channelName,
        std::shared_ptr<ChannelObserverInterface> channelObserver) = 0;

    /**
     * This method will request that the currently foregrounded Channel activity be stopped, if there is one. This will
     * be performed asynchronously, and so, if at the time of processing, the activity has stopped for any reason, then
     * no stop will be performed. If something was stopped, the next highest priority active Channel will be brought
     * to the foreground.
     */
    virtual void stopForegroundActivity() = 0;

    /**
     *  This method will request to stop all active channels. This will be performed asynchronously, and so, if at the
     *  time performing the stop, the channel is owned by another interface, this channel won't get stopped.
     */
    virtual void stopAllActivities() = 0;

    /**
     * Add an observer to the focus manager.
     *
     * @param observer The observer to add.
     */
    virtual void addObserver(const std::shared_ptr<FocusManagerObserverInterface>& observer) = 0;

    /**
     * Remove an observer from the focus manager.
     *
     * @param observer The observer to remove.
     */
    virtual void removeObserver(const std::shared_ptr<FocusManagerObserverInterface>& observer) = 0;

    /**
     * This function allows ChannelObservers to modify the @c MixabilityType rendering on their associated Activity
     * This will cause the focus manager to reconsult the interruptModel in order to determine the new @c MixingBehavior
     * for all backgrounded channels.
     *
     * @param channelName the channel associated with the ChannelObserver
     * @param interfaceName the interface name associated with the ChannelObserver
     * @param mixabilityType the new @c MixabilityType
     */
    virtual void modifyMixabilityType(
            const std::string& channelName,
            const std::string& interfaceName,
            MixabilityType mixabilityType) = 0;
};

inline std::shared_ptr<FocusManagerInterface::Activity> FocusManagerInterface::Activity::create(
    const std::string& interfaceName,
    const std::shared_ptr<ChannelObserverInterface>& channelObserver,
    const MixabilityType mixabilityType) {
    if (interfaceName.empty() || channelObserver == nullptr) {
        return nullptr;
    }

    auto activity = std::shared_ptr<FocusManagerInterface::Activity>(
        new FocusManagerInterface::Activity(interfaceName, channelObserver, mixabilityType));
    return activity;
}

inline const std::string FocusManagerInterface::Activity::getInterface() const {
    return m_interface;
}

inline MixabilityType FocusManagerInterface::Activity::getMixabilityType() const {
    std::unique_lock<std::mutex> lock(m_mutex);
    return m_mixabilityType;
}

inline void FocusManagerInterface::Activity::setMixabilityType(MixabilityType mixabilityType) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_mixabilityType = mixabilityType;
}

inline MixingBehavior FocusManagerInterface::Activity::getMixingBehavior() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_mixingBehavior;
}

inline std::shared_ptr<ChannelObserverInterface> FocusManagerInterface::Activity::getChannelObserver() const {
    return m_channelObserver;
}

inline bool FocusManagerInterface::Activity::notifyObserver(FocusState focus, MixingBehavior behavior) {
    if (m_channelObserver) {
        m_channelObserver->onFocusChanged(focus, behavior);
        // Set the current mixing behavior that the observer received.
        setMixingBehavior(behavior);
        return true;
    }
    return false;
}

inline void FocusManagerInterface::Activity::setMixingBehavior(MixingBehavior behavior) {
    std::unique_lock<std::mutex> lock(m_mutex);
    m_mixingBehavior = behavior;
}

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGER_FOCUSMANAGERINTERFACE_H_
