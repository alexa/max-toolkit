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

#ifndef VII_EXPERIENCE_TEST_MOCK_MOCK_EXPERIENCE_OBSERVER_H
#define VII_EXPERIENCE_TEST_MOCK_MOCK_EXPERIENCE_OBSERVER_H

#include <gmock/gmock.h>

#include "MultiAgentExperience/Experience/ExperienceObserverInterface.h"

namespace multiAgentExperience {
namespace experience {
namespace test {

struct MockExperienceObserver : public experience::ExperienceObserverInterface {
    MOCK_METHOD1(onExperienceChange, void(const std::vector<experience::Experience>&));
};

}  // namespace test
}  // namespace experience
}  // namespace multiAgentExperience

#endif
