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


#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_TEST_INTEGRATION_TESTCONTROL_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_TEST_INTEGRATION_TESTCONTROL_H_

#include <MultiAgentExperience/Control/Control.h>

#include <mutex>
#include <condition_variable>

namespace multiAgentExperience {
namespace library {
namespace test {

class TestControlWrapper {
public:
    std::shared_ptr<control::Control> getControl(control::ControlType controlType) {
        if (!m_control) {
            auto task = [this]() {
                m_wasInvoked = true;
                std::cout << "notify was invoked" << std::endl;
                m_invokedCondition.notify_all();
            };
            m_control = std::make_shared<control::Control>(controlType, task);
        }
        return m_control;
    }

    bool wasInvoked() {
        return m_wasInvoked;
    }

private:
    const std::chrono::milliseconds TIMEOUT = std::chrono::milliseconds(1000);

    std::shared_ptr<control::Control> m_control;
    std::atomic_bool m_wasInvoked;
    std::mutex m_invokedMutex;
    std::condition_variable m_invokedCondition;
};

}  // namespace test
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_TEST_INTEGRATION_TESTCONTROL_H_
