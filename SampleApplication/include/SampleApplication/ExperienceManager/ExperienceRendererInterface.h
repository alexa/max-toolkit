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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_EXPERIENCERENDERERINTERFACE_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_EXPERIENCERENDERERINTERFACE_H_

#include <MultiAgentExperience/Experience/ExperienceObserverInterface.h>

namespace multiAgentExperience {
namespace sampleApplication {
namespace experienceManager {

namespace MAX = multiAgentExperience;

/**
 * A wrapper interface around the MAX experience observer.
 */
class ExperienceRendererInterface : public MAX::experience::ExperienceObserverInterface {
public:
    /**
     * Destructor.
     */
    virtual ~ExperienceRendererInterface() = default;
};

}  // namespace experienceManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_EXPERIENCEMANAGER_EXPERIENCERENDERERINTERFACE_H_
