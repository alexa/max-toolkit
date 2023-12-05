/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_ACTIVITYREQUESTINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_ACTIVITYREQUESTINTERFACE_H_

#include "MultiAgentExperience/Activity/ActivityType.h"
#include "MultiAgentExperience/Activity/ActivityHandlerInterface.h"
#include "MultiAgentExperience/Activity/MixabilityType.h"
#include "MultiAgentExperience/Utils/HashableInterface.h"

namespace multiAgentExperience {
namespace activity {

/**
 * An ActivityRequestInterface is used to request activities from the ActivityManagerInterface. It gathers all state
 * the manager will need to determine if the request is grantable. A new ActivityRequestInterface is expected to be
 * used for each request.
 */
class ActivityRequestInterface : public utils::HashableInterface {
public:
    /**
     * Creates an activity request of the given ActivityType and handled by the given ActivityHandlerInterface.
     *
     * @param activityType - The type of the activity.
     * @param handler - The handler for the activity if the request is granted.
     */
    ActivityRequestInterface(ActivityType activityType,
                             std::shared_ptr<ActivityHandlerInterface> handler,
                             MixabilityType mixabilityType = MixabilityType::MIXABLE_RESTRICTED) :
            m_activityType{activityType},
            m_handler{handler},
            m_mixabilityType{mixabilityType} {
    }

    /**
     * Destructor.
     */
    virtual ~ActivityRequestInterface() = default;

    /**
     * @return The type of the requested activity.
     */
    virtual ActivityType getType() const {
        return m_activityType;
    }

    /**
     * @return The handler for the requested activity.
     */
    virtual std::shared_ptr<ActivityHandlerInterface> getHandler() const {
        return m_handler;
    }

    /**
     * @return The MixabilityType for the requested activity.
     */
    virtual MixabilityType getMixabilityType() const {
        return m_mixabilityType;
    }

private:
    ActivityType m_activityType;
    std::shared_ptr<ActivityHandlerInterface> m_handler;
    MixabilityType m_mixabilityType;
};

}  // namespace activity
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_ACTIVITY_ACTIVITYREQUESTINTERFACE_H_
