/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
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
