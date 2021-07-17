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

#include "SampleApplication/Utils/AVSSDK/AVSSDKUtilities.h"

#include <algorithm>
#include <iostream>

#include <AVSCommon/Utils/Logger/LoggerSinkManager.h>
#include <AVSCommon/AVS/Initialization/AlexaClientSDKInit.h>

#include "SampleApplication/Utils/StringUtils.h"
#include "SampleApplication/Utils/RadiantLogger.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace utils {
namespace avssdk {

using namespace alexaClientSDK;

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("AVSSDKUtilities");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

/// Our minimal AVS SDK configuration string, which instructs audio rendering to direct to the ALSA sink.
static const std::string ALSA_SINK_OVERRIDE_JSON = R"delim(
{
    "gstreamerMediaPlayer":{
        "audioSink":"alsasink"
    }
}
)delim";

void initializeAVSSDK() {
// instruct AVS SDK components which render audio to change their sink to ALSA. Enabled by cmake flag.
#ifdef OVERRIDE_ALSA_SINK
    std::vector<std::shared_ptr<std::istream>> configJsonStreams;
    auto jsonStream = std::shared_ptr<std::istringstream>(new std::istringstream(ALSA_SINK_OVERRIDE_JSON));
    configJsonStreams.push_back(jsonStream);

    if (!avsCommon::avs::initialization::AlexaClientSDKInit::initialize(configJsonStreams)) {
        LX(ERROR, "Failed to initialize AVS SDK");
    }
#endif
}

void initializeLogger() {
    static std::shared_ptr<CustomLogger> avssdkLogger;

    if (!avssdkLogger) {
        avssdkLogger = std::make_shared<CustomLogger>();
        avsCommon::utils::logger::LoggerSinkManager::instance().initialize(avssdkLogger);
    }
}

}  // namespace avssdk
}  // namespace utils
}  // namespace sampleApplication
}  // namespace multiAgentExperience
