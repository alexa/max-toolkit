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

#include "Dialog/DialogRequest.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

static DialogRequestID generateID() {
    static DialogRequestID id = 1;
    return id++;
}

DialogRequest::DialogRequest(std::shared_ptr<Dialog> dialog) : m_id(generateID()), m_dialog(dialog) {
}

std::shared_ptr<Dialog> DialogRequest::getDialog() {
    return m_dialog;
}

const DialogRequestID DialogRequest::getID() const {
    return m_id;
}

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience
