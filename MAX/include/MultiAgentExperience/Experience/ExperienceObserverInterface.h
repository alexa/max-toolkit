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

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_EXPERIENCE_EXPERIENCOBSERVERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_EXPERIENCE_EXPERIENCOBSERVERINTERFACE_H_

#include <vector>

#include "Experience.h"

namespace multiAgentExperience {
namespace experience {

/**
 * @brief An interface used to receive notifications when the active experience(s) change.
 */
class ExperienceObserverInterface {
public:
    /**
     * Destructor.
     */
    virtual ~ExperienceObserverInterface() = default;

    /**
     * When the active experiences the device Ux should display change, this
     * callback will be called.
     *
     * Your implementation should return quickly from this callback. Ie, if long operations
     * are required, store the list of experiences and perform that work an a different thread.
     *
     * @param experiences The list of currently active experiences. In priority order
     * eg. experiences[0] is higher priority to display than experiences[1]
     */
    virtual void onExperienceChange(const std::vector<Experience>& experiences) = 0;
};

}  // namespace experience
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_EXPERIENCE_EXPERIENCOBSERVERINTERFACE_H_
