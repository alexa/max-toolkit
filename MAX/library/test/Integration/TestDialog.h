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


#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_TEST_INTEGRATION_TESTDIALOGREQUEST_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_TEST_INTEGRATION_TESTDIALOGREQUEST_H_

#include <gmock/gmock.h>

#include <mutex>
#include <condition_variable>

#include <MultiAgentExperience/Dialog/DialogRequestInterface.h>
#include <MultiAgentExperience/Dialog/ListeningHandlerInterface.h>
#include <MultiAgentExperience/Dialog/ThinkingHandlerInterface.h>

namespace multiAgentExperience {
namespace library {
namespace test {

class TestDialog
        : public multiAgentExperience::dialog::DialogRequestInterface
        , public multiAgentExperience::dialog::ListeningHandlerInterface
        , public multiAgentExperience::dialog::ThinkingHandlerInterface {
public:
    void onDenied(const std::string& denialMessage) override {
    }

    void onDialogStarted(std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> controller) override {
        m_controller = controller;
        m_transitionCondition.notify_all();
    }

    void onError(const std::string& errorMessage) override {
    }

    void onDialogStopped() override {
    }

    void onStartListening(
        std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> controller,
        std::set<multiAgentExperience::control::ControlType> controls) override {
        m_controls = controls;
        m_transitionCondition.notify_all();
    }

    void onStopListening() override {
    }

    void onStartThinking(std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> controller) override {
        m_transitionCondition.notify_all();
    }

    void onStopThinking() override {
    }

    void invokeControl(control::ControlType controlType) {
        if (m_controller && m_controls.find(controlType) != m_controls.end()) {
            m_controller->stopAndInvokeControl(controlType);
        } else {
            FAIL() << "control type is not available";
        }
    }

    void startListening() {
        std::unique_lock<std::mutex> lock{m_transitionMutex};
        m_transitionCondition.wait_for(lock, TIMEOUT);
        m_controller->startListening();
    }

    void startThinking() {
        m_controller->startThinking();
    }

private:
    const std::chrono::milliseconds TIMEOUT = std::chrono::milliseconds(1000);

    std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> m_controller;
    std::set<multiAgentExperience::control::ControlType> m_controls;
    std::mutex m_transitionMutex;
    std::condition_variable m_transitionCondition;
};

}  // namespace test
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_TEST_INTEGRATION_TESTDIALOGREQUEST_H_
