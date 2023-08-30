/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGER_CHANNELOBSERVERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGER_CHANNELOBSERVERINTERFACE_H_

#include "FocusState.h"
#include "MixingBehavior.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

/**
 * A ChannelObserverInterface is an interface class that clients can extend to register for focus changes.
 */
class ChannelObserverInterface {
public:
    /**
     * Destructor.
     */
    virtual ~ChannelObserverInterface() = default;

    /**
     * Used to notify the observer of the Channel of focus changes. Once called, the client should make a user
     * observable change only and return immediately. Any additional work that needs to be done should be done on a
     * separate thread or after returning. "User observable change" here refers to events that the end user of the
     * product can visibly see or hear. For example, An Agent's speech or music playing would be examples of user
     * observable changes. Other work, such as database storing, logging, or communicating via network should be
     * done on a different thread. Not doing so could result in delays for other clients trying to access the
     * Channel.
     *
     * @param newFocus The new Focus of the channel.
     * @param behavior The mixingBehavior for the ChannelObserver to take as per the interrupt model
     * @note when newFocus is FocusState::FOREGROUND, the MixingBehavior shall be guaranteed to be PRIMARY
     *       when newFocus is FocusState::NONE, the MixingBehavior shall be guaranteed to be MUST_STOP
     */
    virtual void onFocusChanged(FocusState newFocus, MixingBehavior behavior) = 0;
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGER_CHANNELOBSERVERINTERFACE_H_
