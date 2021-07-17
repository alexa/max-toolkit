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
