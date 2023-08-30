/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Control/ControlInvoker.h"

#include <sstream>

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Control/Control.h"
#include "Control/ControlStore.h"
#include "Core/Transformer/TransformerUtils.h"

namespace multiAgentExperience {
namespace library {
namespace control {

static const std::string MODULE_TAG("ControlInvoker");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ControlInvoker::ControlInvoker(const ControlAccessKey controlAccessKey, std::shared_ptr<ControlStore> controlStore) :
        m_controlAccessKey(controlAccessKey),
        m_controlStore(controlStore) {
}

void ControlInvoker::invoke(const ControlName& controlName) {
    std::stringstream ss;
    ss << "Control details:"
       << "controlName=" << core::transformer::TransformerUtils::convertControlNameToString(controlName);
    LX(DEBUG3, ss.str());
    auto control = m_controlStore->getHighestPriorityControlByName(m_controlAccessKey, controlName);
    if (control) {
        control->operator()();
    }
    else {
        LX(WARN, "Expired controlName passed for invocation!");
    }
}

void ControlInvoker::invoke(std::weak_ptr<Control> control) {
    if(auto curControl = control.lock()){
        std::stringstream ss;
        ss << "Control details:"
           << "controlName=" << core::transformer::TransformerUtils::convertControlNameToString(curControl->getName());
        LX(DEBUG3, ss.str());
        curControl->operator()();
    }
    else {
        LX(WARN, "Expired control passed for invocation!");
    }
}

void ControlInvoker::cleanup() {
    m_controlStore->revokeAccess(m_controlAccessKey);
}

ControlInvoker::~ControlInvoker() {
    cleanup();
}

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience
