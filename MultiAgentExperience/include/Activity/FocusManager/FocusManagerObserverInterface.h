/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGER_FOCUSMANAGEROBSERVERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGER_FOCUSMANAGEROBSERVERINTERFACE_H_

#include "FocusState.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

/// An interface that clients can extend to register to observe focus changes.
class FocusManagerObserverInterface {
public:
    virtual ~FocusManagerObserverInterface() = default;

    /**
     * Used to notify the observer of focus changes.  This function should return quickly.
     *
     * @param channelName The name of the channel which changed @c FocusState.
     * @param newFocus The new @c FocusState of @c channelName.
     */
    virtual void onFocusChanged(const std::string& channelName, FocusState newFocus) = 0;
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGER_FOCUSMANAGEROBSERVERINTERFACE_H_
