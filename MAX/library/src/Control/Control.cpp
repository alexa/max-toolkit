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

#include <memory>

#include "Control/Control.h"

namespace multiAgentExperience {
namespace library {
namespace control {

static ControlID generateID() {
    static ControlID id = 1;
    return id++;
}

Control::Control(const ControlName name, std::shared_ptr<ControlTask> task) :
        m_name{name},
        m_id{generateID()},
        m_task{task},
        m_invoked{std::make_shared<std::atomic_bool>(false)} {
}

ControlName Control::getName() const {
    return m_name;
}

ControlID Control::getID() const {
    return m_id;
}

void Control::operator()() const {
    auto expected = false;
    if (std::atomic_compare_exchange_strong(m_invoked.get(), &expected, true)) {
        m_task->operator()();
    }
}

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience
