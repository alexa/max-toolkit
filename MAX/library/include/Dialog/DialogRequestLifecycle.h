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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGREQUESTLIFECYCLE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGREQUESTLIFECYCLE_H_

#include <memory>
#include <mutex>

#include "DialogRequestID.h"
#include "DialogRequest.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

class DialogRequestLifecycle {
public:
    DialogRequestLifecycle(std::shared_ptr<DialogRequest> dialogRequest);

    const DialogRequestID getID() const;

    void grant();

    void deny();

private:
    enum class RequestState { REQUESTED, GRANTED, DENIED };

    std::mutex m_stateMutex;
    RequestState m_state;
    std::shared_ptr<DialogRequest> m_dialogRequest;
};

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGREQUESTLIFECYCLE_H_
