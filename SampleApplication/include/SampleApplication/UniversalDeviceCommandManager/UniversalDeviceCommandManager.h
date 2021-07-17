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


#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UNIVERSALDEVICECOMMANDMANAGER_UNIVERSALDEVICECOMMANDMANAGER_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UNIVERSALDEVICECOMMANDMANAGER_UNIVERSALDEVICECOMMANDMANAGER_H_

#include <MultiAgentExperience/Control/ControlManagerInterface.h>
#include <MultiAgentExperience/Control/ControlInvokerInterface.h>

#include "UniversalDeviceCommandRendererInterface.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace universalDeviceCommandManager {

/**
 * This class handles management of MAX Universal Device Commands and their rendering.
 */
class UniversalDeviceCommandManager {
public:
    /**
     * Creates an @c ExperienceManager.
     *
     * @param maxControlManager The MAX Control Manager to be used.
     * @param maxControlInvoker The MAX Control Invoker to be used.
     * @return A handle to a @c UniversalDeviceCommandManager if successful, otherwise nullptr.
     */
    static std::unique_ptr<UniversalDeviceCommandManager> create(
        std::shared_ptr<MAX::control::ControlManagerInterface> maxControlManager,
        std::shared_ptr<MAX::control::ControlInvokerInterface> maxControlInvoker);

    /**
     * Add a UDC renderer and maintains a weak reference. If the original renderer goes out of scope it is automatically
     * removed.
     *
     * @param renderer The renderer to add.
     */
    void addRenderer(std::weak_ptr<UniversalDeviceCommandRendererInterface> renderer);

    /**
     * Removes all UDC renderers.
     */
    void clearRenderers();

    /**
     * Invokes the stop UDC on MAX. If stop is unavailable it does nothing.
     */
    void invokeStop();

private:
    /**
     * Constructor.
     *
     * @param maxControlManager A handle to the MAX Control Manager.
     */
    UniversalDeviceCommandManager(
        std::shared_ptr<MAX::control::ControlManagerInterface> maxControlManager,
        std::shared_ptr<MAX::control::ControlInvokerInterface> maxControlInvoker);

    /// A handle to the MAX Control Manager.
    std::shared_ptr<MAX::control::ControlManagerInterface> m_maxControlManager;
    /// A handle to the MAX Control Invoker.
    std::shared_ptr<MAX::control::ControlInvokerInterface> m_maxControlInvoker;
};

}  // namespace universalDeviceCommandManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UNIVERSALDEVICECOMMANDMANAGER_UNIVERSALDEVICECOMMANDMANAGER_H_
