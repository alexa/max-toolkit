/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_APPLICATION_MAXLIFECYCLEOBSERVERINTERFACE_H
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_APPLICATION_MAXLIFECYCLEOBSERVERINTERFACE_H

namespace multiAgentExperience {
namespace library {
namespace application {

/**
* Observer of MAXLifecycle.
*/
class MAXLifecycleObserverInterface {
public:
    /// Action to be taken on notification from @c MAXLifecycle, that its state has changed to READY.
    virtual void onTransitionToReady() = 0;
};

}  // namespace application
}  // namespace library
}  // namespace multiAgentExperience

#endif //MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_APPLICATION_MAXLIFECYCLEOBSERVERINTERFACE_H
