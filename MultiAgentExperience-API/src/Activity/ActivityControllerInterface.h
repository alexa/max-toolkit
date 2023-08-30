/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_ACTIVITYCONTROLLERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_ACTIVITYCONTROLLERINTERFACE_H_

namespace multiAgentExperience {
namespace activity {

/**
 * The ActivityControllerInterface allows control over the current activity's lifecycle.
 */
class ActivityControllerInterface {
public:
    /**
     * Destructor.
     */
    virtual ~ActivityControllerInterface() = default;

    /**
     * Immediately stops the activity.
     */
    virtual void stop() = 0;
};

}  // namespace activity
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_ACTIVITYCONTROLLERINTERFACE_H_
