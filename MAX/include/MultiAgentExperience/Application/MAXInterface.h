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

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_APPLICATION_MAXINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_APPLICATION_MAXINTERFACE_H_

#include <memory>

#include "MultiAgentExperience/Agent/AgentManagerInterface.h"
#include "MultiAgentExperience/Application/WakeWordObserverInterface.h"
#include "MultiAgentExperience/Control/ControlManagerInterface.h"
#include "MultiAgentExperience/Control/ControlInvokerInterface.h"
#include "MultiAgentExperience/Experience/ExperienceManagerInterface.h"
#include "MultiAgentExperience/Utils/Log.h"

namespace multiAgentExperience {
namespace application {

/**
 * The central API for applications wishing to use MAX. This interface provides access to MAX subsystem APIs.
 */
class MAXInterface {
public:
    /**
     * destructor.
     */
    virtual ~MAXInterface() = default;

    /**
     * Returns a handle to the MAX Agent Manager.
     *
     * @return a handle to the @c AgentManagerInterface.
     */
    virtual std::shared_ptr<multiAgentExperience::agent::AgentManagerInterface> getAgentManager() = 0;

    /**
     * Returns a handle to the MAX Wakeword Observer.
     *
     * @return a handle to the @c WakeWordObserverInterface.
     */
    virtual std::shared_ptr<multiAgentExperience::application::WakeWordObserverInterface> getWakewordObserver() = 0;

    /**
     * Returns a handle to the MAX Experience Manager.
     *
     * @return a handle to the @c ExperienceManagerInterface.
     */
    virtual std::shared_ptr<multiAgentExperience::experience::ExperienceManagerInterface> getExperienceManager() = 0;

    /**
     * Returns a handle to the MAX Activity Manager.
     *
     * @return a handle to the @c ActivityManagerInterface.
     */
    virtual std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> getActivityManager() = 0;

    /**
     * Returns a handle to the MAX Control Manager.
     *
     * @return a handle to the @c ControlManagerInterface.
     */
    virtual std::shared_ptr<multiAgentExperience::control::ControlManagerInterface> getControlManager() = 0;

    /**
     * Returns a handle to the MAX Control Invoker.
     *
     * @return a handle to the @c ControlInvokerInterface.
     */
    virtual std::shared_ptr<multiAgentExperience::control::ControlInvokerInterface> getControlInvoker() = 0;

    /**
     * Sets the log level of the runtime MAX library.
     *
     * @param level The log level to be used.
     */
    virtual void setLogLevel(multiAgentExperience::utils::Log::Level level) = 0;
};

}  // namespace application
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_APPLICATION_MAXINTERFACE_H_
