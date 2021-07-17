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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_APPLICATION_MAX_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_APPLICATION_MAX_H_

#include <map>
#include <memory>
#include <set>
#include <string>

#include <MultiAgentExperience/Application/MAXInterface.h>

namespace multiAgentExperience {
namespace library {
namespace application {

/**
 * A wrapper class over Core to prevent unneeded access to Core.
 */
class MAX : public multiAgentExperience::application::MAXInterface {
public:
    /**
     * Creates an instance. A device's main application must call this to access Core functionality.
     *
     * @param integratorActorId The ActorId to use for the integrator which is creating and using the MAX library.
     * @return std::shared_ptr<MAX>
     */
    static std::shared_ptr<MAX> create(const actor::ActorId integratorActorId);

    /// @name MAXInterface method overrides.
    /// @{
    std::shared_ptr<multiAgentExperience::agent::AgentManagerInterface> getAgentManager() override;
    std::shared_ptr<multiAgentExperience::experience::ExperienceManagerInterface> getExperienceManager() override;
    std::shared_ptr<multiAgentExperience::application::WakeWordObserverInterface> getWakewordObserver() override;
    std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> getActivityManager() override;
    std::shared_ptr<multiAgentExperience::control::ControlManagerInterface> getControlManager() override;
    std::shared_ptr<multiAgentExperience::control::ControlInvokerInterface> getControlInvoker() override;
    void setLogLevel(multiAgentExperience::utils::Log::Level level) override;
    /// @}

private:
    /**
     * Constructor.
     */
    MAX(const actor::ActorId integratorActorId,
        std::shared_ptr<multiAgentExperience::agent::AgentManagerInterface> agentManager,
        std::shared_ptr<multiAgentExperience::experience::ExperienceManagerInterface> experienceManager,
        std::shared_ptr<multiAgentExperience::application::WakeWordObserverInterface> wakewordObserver,
        std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> activityManager,
        std::shared_ptr<multiAgentExperience::control::ControlManagerInterface> controlManager,
        std::shared_ptr<multiAgentExperience::control::ControlInvokerInterface> controlInvoker);

    /// The max integrator id
    const actor::ActorId m_integratorActorId;

    /// The max agent manager
    std::shared_ptr<multiAgentExperience::agent::AgentManagerInterface> m_agentManager;

    /// The max experience manager
    std::shared_ptr<multiAgentExperience::experience::ExperienceManagerInterface> m_experienceManager;

    /// The max wakeword observe
    std::shared_ptr<multiAgentExperience::application::WakeWordObserverInterface> m_wakewordObserver;

    /// The max activity manager for device application use
    std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> m_activityManager;

    /// The max control manager for device application use
    std::shared_ptr<multiAgentExperience::control::ControlManagerInterface> m_controlManager;

    /// The max control invoker for device application use
    std::shared_ptr<multiAgentExperience::control::ControlInvokerInterface> m_controlInvoker;
};

}  // namespace application
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_APPLICATION_MAX_H_
