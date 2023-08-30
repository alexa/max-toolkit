/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLINVOKER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLINVOKER_H_

#include <memory>

#include "ControlAccessKey.h"
#include "ControlName.h"
#include "ControlStore.h"

namespace multiAgentExperience {
namespace library {
namespace control {

class ControlInvoker {
public:
    explicit ControlInvoker(const ControlAccessKey controlAccessKey, std::shared_ptr<ControlStore> controlStore);

    ~ControlInvoker();

    void invoke(const ControlName& controlName);

    void invoke(std::weak_ptr<Control> control);

    void cleanup();

private:
    const ControlAccessKey m_controlAccessKey;
    std::shared_ptr<ControlStore> m_controlStore;
};

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLINVOKER_H_
