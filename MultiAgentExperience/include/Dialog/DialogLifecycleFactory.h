/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGLIFECYCLEFACTORY_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGLIFECYCLEFACTORY_H_

#include <memory>

#include "Control/CurrentControls.h"
#include "Control/ControlRegistryFactory.h"
#include "Control/ControlInvokerFactory.h"
#include "Dialog.h"
#include "DialogLifecycle.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

class DialogLifecycleFactory {
public:
    DialogLifecycleFactory(
        std::shared_ptr<control::CurrentControls> currentControls,
        std::shared_ptr<control::ControlRegistryFactory> controlRegistryFactory,
        std::shared_ptr<control::ControlInvokerFactory> controlInvokerFactory);

    std::shared_ptr<DialogLifecycle> create(std::shared_ptr<Dialog> dialog);

private:
    std::shared_ptr<control::CurrentControls> m_currentControls;
    std::shared_ptr<control::ControlRegistryFactory> m_controlRegistryFactory;
    std::shared_ptr<control::ControlInvokerFactory> m_controlInvokerFactory;
};

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGLIFECYCLEFACTORY_H_
