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


#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_TEST_INTEGRATION_TESTACTIVITYHANDLER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_TEST_INTEGRATION_TESTACTIVITYHANDLER_H_

#include <gmock/gmock.h>

#include <mutex>
#include <condition_variable>

#include <MultiAgentExperience/Activity/ActivityHandlerInterface.h>

#include <MultiAgentExperience/Control/Control.h>

namespace multiAgentExperience {
namespace library {
namespace test {

class TestActivityHandler : public multiAgentExperience::activity::ActivityHandlerInterface {
public:
    void onDenied() override {
    }

    void onReady(
        std::shared_ptr<multiAgentExperience::activity::ActivityControllerInterface> activityController,
        multiAgentExperience::activity::ActivityFocus focus,
        std::shared_ptr<control::ControlRegistryInterface> controlRegistry,
        std::shared_ptr<experience::ExperienceControllerInterface> experienceControl) override {
        m_controlRegistry = controlRegistry;
        m_initializedCondition.notify_all();
    }

    void onFocusStateChange(multiAgentExperience::activity::ActivityFocus focus) override {
    }

    void onStop() override {
    }

    void addControl(std::shared_ptr<multiAgentExperience::control::Control> control) {
        std::unique_lock<std::mutex> lock{m_initializationMutex};
        m_initializedCondition.wait_for(lock, TIMEOUT);
        if (m_controlRegistry) {
            std::set<std::shared_ptr<multiAgentExperience::control::Control>> controls;
            controls.insert(control);
            m_controlRegistry->update(controls);
        } else {
            FAIL() << "activity not ready";
        }
    }

private:
    const std::chrono::milliseconds TIMEOUT = std::chrono::milliseconds(1000);

    std::shared_ptr<control::ControlRegistryInterface> m_controlRegistry;
    std::mutex m_initializationMutex;
    std::condition_variable m_initializedCondition;
};

}  // namespace test
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_TEST_INTEGRATION_TESTACTIVITYHANDLER_H_
