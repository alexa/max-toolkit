/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_EXPERIENCE_EXPERIENCECONTROLLERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_EXPERIENCE_EXPERIENCECONTROLLERINTERFACE_H_

#include "ExperienceId.h"

namespace multiAgentExperience {
namespace experience {

/**
 * An interface used to start and end Experiences.
 */
class ExperienceControllerInterface {
public:
    /**
     * Destructor.
     */
    virtual ~ExperienceControllerInterface() = default;

    /**
     * Begin an experience.
     * @param experience
     */
    virtual void startExperience(const ExperienceId& experience) = 0;

    /**
     * End the experience.
     */
    virtual void endExperience() = 0;

    /**
     * End the active experience and invalidate this control handle (it won't be able to begin more experiences.
     */
    virtual void invalidate() = 0;
};

}  // namespace experience
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_EXPERIENCE_EXPERIENCECONTROLLERINTERFACE_H_
