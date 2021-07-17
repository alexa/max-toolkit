/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
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
