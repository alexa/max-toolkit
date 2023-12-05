/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_AGENT_AGENTREGISTRATIONINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_AGENT_AGENTREGISTRATIONINTERFACE_H_

#include <memory>
#include <set>
#include <string>

#include "MultiAgentExperience/Activity/ActivityManagerInterface.h"
#include "MultiAgentExperience/Actor/ActorId.h"
#include "MultiAgentExperience/Common/OnCompletionCallbackInterface.h"
#include "MultiAgentExperience/Dialog/DialogManagerInterface.h"
#include "MultiAgentExperience/Experience/StaticExperienceManagerInterface.h"

namespace multiAgentExperience {
namespace agent {

/**
 * The Agent is an actor which handles input from the user to participate in the multi-agent experience.
 *
 * The Agent is not initialized until it is registered. Be aware that the MAX ActivityManagerInterface,
 * DialogManagerInterface and StaticExperienceManagerInterface are not usable until onReady is called.
 */
class AgentRegistrationInterface {
public:

    /**
     * Destructor
     */
    virtual ~AgentRegistrationInterface() = default;

    /**
     * Provides access to the core MAX APIs required by the Agent when they are available.
     *
     * @param onCompletionCallback The callback is expected to be invoked by the agent when it has determined that it is ready.
     *
     * The different usages of the callback are:\n
     *
     * 1. Registration of all agents for the first time. There may be no Activities or Dialogs to be re-requested, and hence,
     * this callback may be invoked immediately or ignored.\n
     *
     * 2. Registration of all agents after MAX has recovered from a crash. If any Activities or Dialogs need to be
     * re-requested, the callback should be executed after those requests are placed. After the execution of the
     * OnCompletionCallback, MAX will evaluate all currently requested items and accept the ones which are still valid,
     * placing them in the correct state.
     *
     * @param activityManager The manager for scheduling Activities
     * @param dialogManager The manager for scheduling Dialogs
     * @param staticExperienceManager  The manager for handing StaticExperiences
     */
    virtual void onReady(
        std::shared_ptr<multiAgentExperience::common::OnCompletionCallbackInterface> onCompletionCallback,
        std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> activityManager,
        std::shared_ptr<multiAgentExperience::dialog::DialogManagerInterface> dialogManager,
        std::shared_ptr<multiAgentExperience::experience::StaticExperienceManagerInterface> staticExperienceManager) = 0;

    /** @brief Get the ActorId of the agent.
     *
     * @return the ActorId of the agent
     */
    virtual actor::ActorId getId() = 0;

    /** @brief Get the customer facing name of the agent.
     *
     * @return the Name of the agent
     */
    virtual std::string getName() = 0;
};

}  // namespace agent
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_AGENT_AGENTREGISTRATIONINTERFACE_H_
