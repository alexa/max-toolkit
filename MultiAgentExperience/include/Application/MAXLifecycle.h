/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_APPLICATION_MAXLIFECYCLE_H
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_APPLICATION_MAXLIFECYCLE_H

#include <memory>
#include <vector>

#include "Application/MAXLifecycleObserverInterface.h"

namespace multiAgentExperience {
namespace library {
namespace application {

/**
 * Keeps track of the state MAX is in, via the @c MAXState.
 * Also, notifies any observer (@c MAXLifecycleObserverInterface) of this class, of a MAX state change.
 */
class MAXLifecycle {
public:
    MAXLifecycle();

    /**
     * Adds an observer which can be notified of any change to the @c MAXState
     *
     * @param observer An observer object that implements @c MAXLifecycleObserverInterface
     */
    void addObserver(std::shared_ptr<MAXLifecycleObserverInterface> observer);

    /**
     * Changes the state of MAX to MAXState::READY and notifies any observers of this change.
     *
     * Currently we transition to this state, when MAX receives @c OnCompletionCallbacks for
     * @c AgentRegistrationInterface::onReady, from all agents.
     */
    void transitionToReady();

    /**
     * Returns true if MAX is in READY state. False, otherwise.
     *
     * @return True if MAX is in READY state. False, otherwise.
     */
    bool isReady();

private:
    /**
     * The state that MAX is in.
     */
    enum class MAXState {
        /// The state up until the completion of agent registration
        NOT_READY,

        /// The state when all agents have been successfully registered with MAX
        READY
    };
    MAXState m_state;
    std::vector<std::weak_ptr<MAXLifecycleObserverInterface>> m_observers;
};

}  // namespace application
}  // namespace library
}  // namespace multiAgentExperience

#endif //MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_APPLICATION_MAXLIFECYCLE_H
