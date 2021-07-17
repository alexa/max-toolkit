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

#ifndef VII_CORE_EXPERIENCE_MOCKEXPERIENCECONTROLINTERFACE_H
#define VII_CORE_EXPERIENCE_MOCKEXPERIENCECONTROLINTERFACE_H

#include "MultiAgentExperience/Experience/ExperienceControllerInterface.h"

#include <gmock/gmock.h>
#include <memory>

namespace multiAgentExperience {
namespace experience {
namespace test {

class MockExperienceControlInterface : public multiAgentExperience::experience::ExperienceControllerInterface {
public:
    MOCK_METHOD1(startExperience, void(const multiAgentExperience::experience::ExperienceId&));
    MOCK_METHOD0(endExperience, void());
    MOCK_METHOD0(invalidate, void());
};

}  // namespace test
}  // namespace experience
}  // namespace multiAgentExperience

#endif  // VII_CORE_EXPERIENCE_MOCKEXPERIENCECONTROLINTERFACE_H
