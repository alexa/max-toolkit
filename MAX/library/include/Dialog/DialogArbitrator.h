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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGARBITRATOR_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGARBITRATOR_H_

#include <memory>
#include <mutex>

#include "DialogRequestID.h"
#include "DialogLifecycle.h"
#include "DialogLifecycleFactory.h"
#include "DialogRequest.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

class DialogArbitrator {
public:
    DialogArbitrator(std::shared_ptr<DialogLifecycleFactory> dialogLifecycleFactory);

    bool tryInterruptingWith(std::shared_ptr<DialogRequest> dialogRequest);

    std::shared_ptr<DialogLifecycle> getCurrentDialog();

    void cleanup(const DialogRequestID dialogRequestId);

private:
    std::mutex m_sessionMutex;
    std::shared_ptr<DialogLifecycleFactory> m_dialogLifecycleFactory;
    std::shared_ptr<DialogLifecycle> m_dialogLifecycle;
    DialogRequestID m_dialogRequestID;
};

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGARBITRATOR_H_
