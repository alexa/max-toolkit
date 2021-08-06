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

#ifndef VII_CORE_EXPERIENCE_MOCKEXPERIENCEMANAGERINTERFACE_H
#define VII_CORE_EXPERIENCE_MOCKEXPERIENCEMANAGERINTERFACE_H

#include "Experience/ExperienceManager.h"
#include "MultiAgentExperience/Experience/ExperienceControllerInterface.h"

#include <gmock/gmock.h>
#include <memory>

namespace multiAgentExperience {
namespace experience {
namespace test {

class MockExperienceManager : public library::experience::ExperienceManager {
public:
    MOCK_METHOD1(addObserver, void(std::weak_ptr<experience::ExperienceObserverInterface> observer));
    MOCK_METHOD0(clearObservers, void());
    MOCK_METHOD1(getControl, std::shared_ptr<experience::ExperienceControllerInterface>(const std::string& agent));
};

}  // namespace test
}  // namespace experience
}  // namespace multiAgentExperience

#endif  // VII_CORE_EXPERIENCE_MOCKEXPERIENCEMANAGERINTERFACE_H
