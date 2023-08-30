/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_APPLICATION_MAXINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_APPLICATION_MAXINTERFACE_H_

#include <memory>

#include "MultiAgentExperience/Agent/AgentManagerInterface.h"
#include "MultiAgentExperience/Control/ControlManagerInterface.h"
#include "MultiAgentExperience/Control/ControlInvokerInterface.h"
#include "MultiAgentExperience/Device/SetupManagerInterface.h"
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
     * Returns a handle to the MAX Setup Manager.
     *
     * @return a handle to the @c SetupManagerInterface.
     */
    virtual std::shared_ptr<multiAgentExperience::device::SetupManagerInterface> getSetupManager() = 0;

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
