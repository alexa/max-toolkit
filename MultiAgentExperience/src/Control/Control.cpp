/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
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
