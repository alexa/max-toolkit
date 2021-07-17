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

#ifndef MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_RESPONSE_RESPONSE_TYPE_H_
#define MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_RESPONSE_RESPONSE_TYPE_H_

#include <string>

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {
namespace response {

enum class ResponseType { SPEAK, PLAY_LOCAL_AUDIO, INVOKE_ACTIVITY_CONTROL, INVOKE_AGENT_TRANSFER, ERROR };

static ResponseType getResponseTypeFromString(const std::string& responseType) {
    if (responseType == "InvokeActivityControl") {
        return ResponseType::INVOKE_ACTIVITY_CONTROL;
    } else if (responseType == "InvokeAgentTransfer") {
        return ResponseType::INVOKE_AGENT_TRANSFER;
    } else if (responseType == "PlayLocalAudio") {
        return ResponseType::PLAY_LOCAL_AUDIO;
    } else if (responseType == "Speak") {
        return ResponseType::SPEAK;
    } else {
        return ResponseType::ERROR;
    }
}

inline std::ostream& operator<<(std::ostream& stream, ResponseType type) {
    switch (type) {
        case ResponseType::SPEAK:
            stream << "SPEAK";
            return stream;
        case ResponseType::PLAY_LOCAL_AUDIO:
            stream << "PLAY_LOCAL_AUDIO";
            return stream;
        case ResponseType::INVOKE_ACTIVITY_CONTROL:
            stream << "INVOKE_ACTIVITY_CONTROL";
            return stream;
        case ResponseType::INVOKE_AGENT_TRANSFER:
            stream << "INVOKE_AGENT_TRANSFER";
            return stream;
        case ResponseType::ERROR:
            stream << "ERROR";
            return stream;
    }

    stream << "UNKNOWN_TYPE";
    return stream;
}

}  // namespace response
}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_RESPONSE_RESPONSE_TYPE_H_
