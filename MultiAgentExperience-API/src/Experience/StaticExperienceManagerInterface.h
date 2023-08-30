/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_EXPERIENCE_STATICEXPERIENCEMANAGERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_EXPERIENCE_STATICEXPERIENCEMANAGERINTERFACE_H_

#include "ExperienceId.h"

namespace multiAgentExperience {
namespace experience {
/**
 * An interface used to add & remove static experiences supported by a MAX conformant agent
 */
class StaticExperienceManagerInterface {
public:
    /**
     * Destructor.
     */
    virtual ~StaticExperienceManagerInterface() = default;

    /**
     * Method for adding a static experience with it's relative priority. The relative priority of
     * a static experience is an unsigned integer following the value semantics that lower value is
     * higher priority as can be seen from below :
     *
     * Static_Experience_1 with priority 0 > Static_Experience_2 with priority 1
     */
    virtual void addStaticExperience(const ExperienceId& experienceId, const unsigned int priority) = 0;

    /**
     * Method that the agent could use to remove a static experience from the list of static
     * experiences it supports
     */
    virtual void removeStaticExperience(const ExperienceId& experienceId) = 0;

    /**
     * Method to remove all experiences from the collection of static experiences supported by
     * the agent
     */
    virtual void removeAllStaticExperiences() = 0;
};
}  // namespace experience
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_EXPERIENCE_STATICEXPERIENCEMANAGERINTERFACE_H_