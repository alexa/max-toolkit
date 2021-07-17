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

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_APPLICATION_WAKEWORDOBSERVERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_APPLICATION_WAKEWORDOBSERVERINTERFACE_H_

#include <string>

namespace multiAgentExperience {
namespace application {

/**
 *
 */
class WakeWordObserverInterface {
public:
    /**
     * Destructor.
     */
    virtual ~WakeWordObserverInterface() = default;

    /**
     * @brief Callback to be called when the device detects a wakeword. Iff the WWE does not notify the agents directly.
     *
     * @param wakeword the wakeword that was detected.
     */
    virtual void onWakeWordDetected(const std::string& wakeword) = 0;
};

}  // namespace application
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_APPLICATION_WAKEWORDOBSERVERINTERFACE_H_
