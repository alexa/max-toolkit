/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Dialog/DialogLifecycleFactory.h"

#include "Dialog/Dialog.h"
#include "Dialog/DialogLifecycle.h"

namespace multiAgentExperience {
namespace library {
namespace dialog {

DialogLifecycleFactory::DialogLifecycleFactory(
    std::shared_ptr<control::CurrentControls> currentControls,
    std::shared_ptr<control::ControlRegistryFactory> controlRegistryFactory,
    std::shared_ptr<control::ControlInvokerFactory> controlInvokerFactory) :
        m_currentControls(currentControls),
        m_controlRegistryFactory(controlRegistryFactory),
        m_controlInvokerFactory(controlInvokerFactory) {
}

std::shared_ptr<DialogLifecycle> DialogLifecycleFactory::create(std::shared_ptr<Dialog> dialog) {
    return std::make_shared<DialogLifecycle>(
        dialog, m_currentControls, m_controlRegistryFactory, m_controlInvokerFactory);
}

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience
