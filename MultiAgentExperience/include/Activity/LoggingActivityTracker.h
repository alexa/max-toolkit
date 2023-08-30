/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_LOGGINGACTIVITYTRACKER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_LOGGINGACTIVITYTRACKER_H_

#include "FocusManager/ActivityTrackerInterface.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

class LoggingActivityTracker : public ActivityTrackerInterface {
public:
    /// @name ActivityTrackerInterface method overrides.
    /// @{
    void notifyOfActivityUpdates(const std::vector<Channel::State>& channelStates) override;
    /// @}
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_LOGGINGACTIVITYTRACKER_H_
