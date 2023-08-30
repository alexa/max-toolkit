/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Control/ControlInvokerFactory.h"

#include "Control/ControlAccessKeys.h"
#include "Control/ControlInvoker.h"

namespace multiAgentExperience {
namespace library {
namespace control {

ControlInvokerFactory::ControlInvokerFactory(
    std::shared_ptr<ControlAccessKeys> controlAccessKeys,
    std::shared_ptr<ControlStore> controlStore) :
        m_controlAccessKeys(controlAccessKeys),
        m_controlStore(controlStore) {
}

std::shared_ptr<ControlInvoker> ControlInvokerFactory::create() {
    auto key = m_controlAccessKeys->requestAccessKey();
    return std::make_shared<ControlInvoker>(key, m_controlStore);
}

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience
