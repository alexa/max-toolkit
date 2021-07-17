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


#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_TEST_INTEGRATION_TESTAGENT_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_TEST_INTEGRATION_TESTAGENT_H_

#include <gmock/gmock.h>

#include <mutex>
#include <condition_variable>

#include <MultiAgentExperience/Agent/Agent.h>

#include "TestDialog.h"

namespace multiAgentExperience {
namespace library {
namespace test {

class TestAgent : public multiAgentExperience::agent::Agent {
public:
    TestAgent(const actor::ActorId& id) : Agent(id, ""), m_wasTransferredTo{false} {
    }

    void startActivity(std::shared_ptr<multiAgentExperience::activity::ActivityRequestInterface> request) {
        if (m_activityManager) {
            m_activityManager->request(request);
        } else {
            FAIL() << "agent not initialized: " + getId().get();
        }
    }

    void startDialog(std::shared_ptr<TestDialog> dialogRequest) {
        if (m_dialogManager) {
            m_dialogManager->setListeningHandler(dialogRequest);
            m_dialogManager->setThinkingHandler(dialogRequest);
            m_dialogManager->request(dialogRequest);
        } else {
            FAIL() << "agent not initialized: " + getId().get();
        }
    }

    bool wasTransferredTo() {
        return m_wasTransferredTo;
    }

protected:
    void handleOnWakeWordDetected() override {
    }

    void handleOnTapDetected() override {
    }

    void handleOnAgentTransfer() override {
        m_wasTransferredTo = true;
    }

    void onInitialized() override {
    }

private:
    bool m_wasTransferredTo;
};

}  // namespace test
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_TEST_INTEGRATION_TESTAGENT_H_
