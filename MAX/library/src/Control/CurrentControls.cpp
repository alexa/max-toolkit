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

#include "Control/CurrentControls.h"

#include "Control/ControlName.h"
#include "Control/ControlStore.h"

namespace multiAgentExperience {
namespace library {
namespace control {

CurrentControls::CurrentControls(const ControlAccessKey controlAccessKey, std::shared_ptr<ControlStore> controlStore) :
        m_controlAccessKey(controlAccessKey),
        m_controlStore(controlStore) {
}

std::unordered_set<ControlName> CurrentControls::getCurrentControls() {
    return m_controlStore->getUnionOfControlNames(m_controlAccessKey);
}

CurrentControls::~CurrentControls() {
    m_controlStore->revokeAccess(m_controlAccessKey);
}

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience
