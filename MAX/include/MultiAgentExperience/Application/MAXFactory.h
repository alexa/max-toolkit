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

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_APPLICATION_MAXFACTORY_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_APPLICATION_MAXFACTORY_H_

#include <memory>
#include <string>

#include "MultiAgentExperience/Actor/ActorId.h"
#include "MultiAgentExperience/Application/MAXInterface.h"
#include <MultiAgentExperience/Utils/Log.h>

namespace multiAgentExperience {
namespace application {

/**
 * A factory class which provides a handle to the application-facing MAX primitives and APIs.
 *
 * @note Any application shall only be provided a single instantiation of the @c MAXInterface. If this API is invoked
 * multiple times, the same instance shall be returned.
 */
class MAXFactory {
public:
    /// The default value for the integrators ActorId.
    static const actor::ActorId DEFAULT_INTEGRATOR_ACTOR_ID;

    /**
     * Provides a handle to a MAX primitives interface.
     *
     * @param integratorActorId The ActorId to use for the integrator which is creating and using the MAX library.
     * @param logger A handle to the logger which the MAX library should use. If nullptr, then the MAX library shall
     * use a logger of its own choosing.
     * @param logComponentName If a logger has been provided, then this parameter describes the component name to be
     * used within logging metadata. If no logger was provided, then this parameter is ignored.
     * @return A handle to a MAX primitives interface.
     */
    static std::shared_ptr<multiAgentExperience::application::MAXInterface> create(
        const actor::ActorId integratorActorId = DEFAULT_INTEGRATOR_ACTOR_ID,
        std::shared_ptr<multiAgentExperience::utils::Log> logger = nullptr,
        const std::string& logComponentName = "MAX_LIB");
};

}  // namespace application
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_APPLICATION_MAXFACTORY_H_
