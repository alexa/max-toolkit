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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_GESTUREHANDLERINTERFACE_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_GESTUREHANDLERINTERFACE_H_

#include <string>

namespace multiAgentExperience {
namespace sampleApplication {
namespace agentManager {

/**
 * An interface which handles gesture invocation of an Agent. Currently modeled upon wakeword association with an
 * Agent, although this will most likely change in future revisions of the MAX Toolkit to be more Agent oriented.
 */
class GestureHandlerInterface {
public:
    /// The gestures by which an Agent may be invoked.
    enum class GestureType {
        /// Tap to talk.
        TAP,
        /// Hold to talk.
        HOLD
    };

    /**
     * Destructor.
     */
    virtual ~GestureHandlerInterface() = default;

    /**
     * Invoke a gesture given the wakeword. Implementations should map the wakeword to a given Agent then invoke the
     * gesture upon that Agent. Assumes that there are not duplicate wakewords across current Agents.
     *
     * @param gesture The gesture to invoke.
     * @param wakeword The wakeword associated with the Agent that should receive the gesture.
     */
    virtual void invokeGesture(GestureType gesture, const std::string& wakeword) = 0;
};

}  // namespace agentManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_GESTUREHANDLERINTERFACE_H_
