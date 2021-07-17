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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_WAKEWORDENGINESCONFIG_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_WAKEWORDENGINESCONFIG_H_

#include <ostream>
#include <set>
#include <string>
#include <vector>

#include <rapidjson/document.h>

#include "SampleApplication/AudioManager/Wakeword/WakewordEngine.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {
namespace wakeword {

/**
 * A struct that captures the configuration of multiple wakeword engines.
 */
struct WakewordEnginesConfig {
    /**
     * A struct that captures a wakeword engine configuration.
     */
    struct EngineConfig {
        /**
         * Constructor.
         */
        EngineConfig();

        /// The name of the wakeword engine.
        std::string name;
        /// How the engine should be created.
        WakewordEngine::CreateMethod createMethod;
        /// The wakewords the engine is expected to detect.
        std::vector<std::string> wakewords;
        /// An additional directory that may be used to instantiate the engine.
        std::string resourceFolder;
    };

    /// All engine configs.
    std::vector<EngineConfig> engineConfigs;
};

/**
 * A utility function to parse a given rapidjson document and produce an @c WakewordEnginesConfig object.
 *
 * @param document The rapidjson document.
 * @param format [out] The WakewordEnginesConfig object to be set.
 * @return Whether the parse was successful.
 */
bool parseJSONConfig(const rapidjson::Document& document, WakewordEnginesConfig* format);

}  // namespace wakeword
}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_WAKEWORDENGINESCONFIG_H_
