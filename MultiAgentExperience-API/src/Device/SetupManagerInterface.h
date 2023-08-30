/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/
#ifndef MULTIAGENTEXPERIENCE_API_SETUPMANAGERINTERFACE_H
#define MULTIAGENTEXPERIENCE_API_SETUPMANAGERINTERFACE_H

#include "MultiAgentExperience/Actor/ActorId.h"

namespace multiAgentExperience {
namespace device {

/**
 * The SetupManagerInterface is used to manage any behavior during setup from Device.
 */
class SetupManagerInterface {
public:
    /**
     * Destructor.
     */
    virtual ~SetupManagerInterface() = default;

    /**
     * Called when setup needs to be made from Device Companion app for particular Actor.
     * This stops all ongoing activities and blocks other actors from interrupting the setup.
     *
     * @param actorId - ActorId of the agent that is being setup.
     */
    virtual void enterSetupMode(const multiAgentExperience::actor::ActorId& actorId) = 0;

    /**
     * Called when Setup is complete from Device Companion app.
     * This enables all actors to get access to activity channels after the setup.
     */
    virtual void exitSetupMode() = 0;
};

}  // namespace device
}  // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_API_SETUPMANAGERINTERFACE_H
