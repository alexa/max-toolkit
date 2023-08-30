/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_EXPERIENCE_EXPERIENCEMANAGERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_EXPERIENCE_EXPERIENCEMANAGERINTERFACE_H_

#include <memory>

#include "ExperienceObserverInterface.h"

namespace multiAgentExperience {
namespace experience {

/**
 * An interface used to register observers of experience changes.
 */
class ExperienceManagerInterface {
public:
    /**
     * Destructor.
     */
    virtual ~ExperienceManagerInterface() = default;

    /**
     * "Register" an observers to be notified when the active experiences change.
     * @param observer the ExperienceObserverInterface implementation
     */
    virtual void addObserver(std::weak_ptr<ExperienceObserverInterface> observer) = 0;

    /**
     * "De-Register" an observer i.e. the observer will then "not" be notified when
     * active experiences change.
     * @param observer the ExperienceObserverInterface implementation
     */
    virtual void removeObserver(std::weak_ptr<ExperienceObserverInterface> observer) = 0;

    /**
     * "De-register" all observers of experience changes
     */
    virtual void clearObservers() = 0;
};

}  // namespace experience
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_EXPERIENCE_EXPERIENCEMANAGERINTERFACE_H_
