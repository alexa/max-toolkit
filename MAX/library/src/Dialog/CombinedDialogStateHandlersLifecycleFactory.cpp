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
