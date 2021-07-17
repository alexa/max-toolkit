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

#include "MultiAgentExperience/Application/MAXFactory.h"
#include "Application/MAX.h"
#include "Utils/Logger/Logger.h"

namespace multiAgentExperience {
namespace application {

const actor::ActorId MAXFactory::DEFAULT_INTEGRATOR_ACTOR_ID = actor::ActorId("MAX_APPLICATION_INTEGRATOR_ID");

std::shared_ptr<multiAgentExperience::application::MAXInterface> MAXFactory::create(
    const actor::ActorId integratorActorId,
    std::shared_ptr<multiAgentExperience::utils::Log> logger,
    const std::string& logComponentName) {
    if (!logger) {
        logger = std::make_shared<library::utils::logger::Logger>();
    }

    library::utils::logger::setLoggerComponentName(logComponentName);
    library::utils::logger::setLoggerInstance(logger);

    return library::application::MAX::create(integratorActorId);
}

}  // namespace application
}  // namespace multiAgentExperience
