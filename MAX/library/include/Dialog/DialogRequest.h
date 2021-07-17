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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGREQUEST_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGREQUEST_H_

#include <memory>

#include "DialogRequestID.h"
#include "Dialog.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

class DialogRequest {
public:
    // TODO: Add a constructor for Agent initiated dialogs.

    DialogRequest(std::shared_ptr<Dialog> dialog);

    virtual ~DialogRequest() = default;

    std::shared_ptr<Dialog> getDialog();

    const DialogRequestID getID() const;

    virtual void onGranted() = 0;

    virtual void onDenied() = 0;

private:
    const DialogRequestID m_id;
    std::shared_ptr<Dialog> m_dialog;
};

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGREQUEST_H_
