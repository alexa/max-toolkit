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

#include "SampleApplication/Utils/JSONUtils.h"

#include <iostream>
#include <sstream>

#include <rapidjson/error/en.h>

#include "SampleApplication/Utils/RadiantLogger.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace utils {

using namespace rapidjson;

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("JSONUtils");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, __func__, MODULE_TAG, message)

bool performInitialJSONParse(const std::string& unparsedText, Document* document) {
    LX(DEBUG3, "");

    if (!document) {
        LX(ERROR, "document is nullptr.");
        return false;
    }

    // invoke parse with a flag which supports double-slash comments within JSON.
    document->Parse<kParseCommentsFlag>(unparsedText.c_str());

    if (document->HasParseError()) {
        std::stringstream ss;
        ss << "offset:" << document->GetErrorOffset() << ", error:" << GetParseError_En(document->GetParseError());
        LX(ERROR, ss.str());
        return false;
    }

    return true;
}

}  // namespace utils
}  // namespace sampleApplication
}  // namespace multiAgentExperience
