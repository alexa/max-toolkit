/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_APPLICATION_MAXBUILDER_H
#define MULTI_AGENT_EXPERIENCE_INCLUDE_APPLICATION_MAXBUILDER_H

#include <map>
#include <memory>
#include <string>

#include "MultiAgentExperience/Activity/ActivityType.h"
#include "MultiAgentExperience/Actor/ActorId.h"
#include "MultiAgentExperience/Application/MAXInterface.h"
#include "MultiAgentExperience/Application/MAXPolicies.h"
#include "MultiAgentExperience/Utils/Log.h"

namespace multiAgentExperience {
namespace application {

/**
 * A builder class which provides a handle to the application-facing MAX primitives and APIs, based on the
 * properties passed to the builder.
 */
class MAXBuilder {

public:
    /// Constructor
    MAXBuilder();

    /**
     * Sets the ActorId which is to be used for the integrator which is creating and using the MAX library.
     *
     * @param integratorActorId The ActorId to use for the integrator which is creating and using the MAX library.
     * @return A reference to this instance to facilitate setting more information to this MAXBuilder
     */
    MAXBuilder& setIntegratorActorId(const actor::ActorId& integratorActorId);

    /**
     * Sets the logger which the MAX library should use.
     *
     * @param logger A handle to the logger which the MAX library should use. If nullptr, then the MAX library shall
     * use a logger of its own choosing.
     * @return A reference to this instance to facilitate setting more information to this MAXBuilder
     */
    MAXBuilder& setLogger(std::shared_ptr<multiAgentExperience::utils::Log> logger);

    /**
     * Sets the name which is used within logging metadata
     *
     * @param logComponentName If a logger has been provided, then this parameter describes the component name to be
     * used within logging metadata. If no logger was provided, then this parameter is ignored.
     * @return A reference to this instance to facilitate setting more information to this MAXBuilder
     */
    MAXBuilder& setLogComponentName(const std::string& logComponentName);

    /**
     * Sets the cross-agent barge-in policy for Dialogs with barge-in priority - high
     *
     * @param highPriorityCrossAgentBargeInPolicy The policy which indicates if the corresponding barge-in is supported or not
     * @return A reference to this instance to facilitate setting more information to this MAXBuilder
     */
    MAXBuilder& withHighPriorityCrossAgentBargeIn(
        const HighPriorityCrossAgentBargeInPolicy& highPriorityCrossAgentBargeInPolicy);

    /**
     * Sets the cross-agent barge-in policy for Dialogs with barge-in priority - normal
     *
     * @param normalPriorityCrossAgentBargeInPolicy The policy which indicates if the corresponding barge-in is supported or not
     * @return A reference to this instance to facilitate setting more information to this MAXBuilder
     */
    MAXBuilder& withNormalPriorityCrossAgentBargeIn(
        const NormalPriorityCrossAgentBargeInPolicy& normalPriorityCrossAgentBargeInPolicy);

    /**
     * Sets the activity scheduling policy for a particular activity type
     *
     * @param activityType The activity type for which the scheduling policy is to be set
     * @param activitySchedulingPolicy The scheduling policy
     * @return A reference to this instance to facilitate setting more information to this MAXBuilder
     */
    MAXBuilder& setActivitySchedulingPolicy(
        const multiAgentExperience::activity::ActivityType& activityType,
        const ActivitySchedulingPolicy& activitySchedulingPolicy);

    /**
     * Provides a handle to a MAX primitives interface, which is based on the state stored in the MAXBuilder
     *
     * @return A handle to a MAX primitives interface.
     */
    std::shared_ptr<multiAgentExperience::application::MAXInterface> build();

private:
    actor::ActorId m_integratorActorId;
    std::shared_ptr<multiAgentExperience::utils::Log> m_logger;
    std::string m_logComponentName;
    HighPriorityCrossAgentBargeInPolicy m_highPriorityCrossAgentBargeInPolicy;
    NormalPriorityCrossAgentBargeInPolicy m_normalPriorityCrossAgentBargeInPolicy;
    std::map<multiAgentExperience::activity::ActivityType, ActivitySchedulingPolicy> m_activitySchedulingPolicyMap;
};

}  // namespace application
}  // namespace multiAgentExperience

#endif // MULTI_AGENT_EXPERIENCE_INCLUDE_APPLICATION_MAXBUILDER_H
