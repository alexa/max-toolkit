/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLINVOKERFACTORY_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLINVOKERFACTORY_H_

#include <memory>

#include "ControlAccessKey.h"
#include "ControlInvoker.h"
#include "ControlStore.h"

namespace multiAgentExperience {
namespace library {
namespace control {

class ControlInvokerFactory {
public:
    ControlInvokerFactory(
        std::shared_ptr<ControlAccessKeys> controlAccessKeys,
        std::shared_ptr<ControlStore> controlStore);

    std::shared_ptr<ControlInvoker> create();

private:
    std::shared_ptr<ControlAccessKeys> m_controlAccessKeys;
    std::shared_ptr<ControlStore> m_controlStore;
};

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLINVOKERFACTORY_H_
