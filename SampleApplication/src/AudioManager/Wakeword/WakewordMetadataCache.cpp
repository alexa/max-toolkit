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

#include "SampleApplication/AudioManager/Wakeword/WakewordMetadataCache.h"

#include <sstream>

#include "SampleApplication/Utils/RadiantLogger.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {
namespace wakeword {

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("WakewordMetadataCache");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

void WakewordMetadataCache::setMetadata(
    const alexaClientSDK::avsCommon::sdkInterfaces::KeyWordMetadataAccessorInterface::Metadata& data) {
    std::stringstream ss;
    ss << "Setting KWD metadata:"
       << "keyword:" << data.keyword << ", beginIndex:" << data.beginIndex << ", endIndex:" << data.endIndex
       << ", UNSPECIFIED_INDEX value (numeric_limits::max()):"
       << alexaClientSDK::avsCommon::sdkInterfaces::KeyWordObserverInterface::UNSPECIFIED_INDEX;
    if (data.additionalFields) {
        ss << ", additionalFields size:" << data.additionalFields->size();
    }

    LX(DEBUG3, ss.str());

    m_currentMetadata = data;
}

alexaClientSDK::avsCommon::sdkInterfaces::KeyWordMetadataAccessorInterface::Metadata WakewordMetadataCache::
    getKeywordMetadata() {
    LX(DEBUG3, "");
    return m_currentMetadata;
}

}  // namespace wakeword
}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience
