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

#ifndef MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_RESPONSE_RESPONSE_H_
#define MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_RESPONSE_RESPONSE_H_

#include <iostream>
#include <memory>
#include <utility>

#include "ResponseType.h"
#include "ResponsePayload.h"

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {
namespace response {

class Response {
public:
    static std::shared_ptr<Response> createSpeakResponse(
        std::string& responseText,
        std::shared_ptr<std::istream> audioStream) {
        std::shared_ptr<Response> response(new Response(responseText, ResponseType::SPEAK, "", std::move(audioStream)));
        return response;
    }
    static std::shared_ptr<Response> createErrorResponse() {
        std::shared_ptr<Response> response(new Response("error", ResponseType::ERROR, ""));
        return response;
    }
    static std::shared_ptr<Response> createResponse(
        const std::string& responseText,
        const ResponseType responseType,
        const ResponsePayload& responsePayload) {
        std::shared_ptr<Response> response(new Response(responseText, responseType, responsePayload));
        return response;
    }
    static std::shared_ptr<Response> createResponse(
        const std::string& responseText,
        const std::string& responseType,
        const std::string& responsePayload) {
        std::shared_ptr<Response> response(
            new Response(responseText, response::getResponseTypeFromString(responseType), responsePayload));
        return response;
    }
    static std::shared_ptr<Response> createResponse(
        const std::string& responseText,
        const std::string& responseType,
        const std::string& responsePayload,
        std::shared_ptr<std::istream> audioStream) {
        std::shared_ptr<Response> response(new Response(
            responseText, response::getResponseTypeFromString(responseType), responsePayload, std::move(audioStream)));
        return response;
    }

    ResponseType getResponseType() {
        return m_responseType;
    }
    ResponsePayload getResponsePayload() {
        return m_responsePayload;
    }
    std::shared_ptr<std::istream> getAudioStream() {
        return m_audioStream;
    }
    std::string getResponseText() {
        return m_responseText;
    }

private:
    explicit Response(
        const std::string& responseText,
        ResponseType responseType,
        ResponsePayload responsePayload = "",
        std::shared_ptr<std::istream> audioStream = nullptr) :
            m_responseText{responseText},
            m_responseType{responseType},
            m_responsePayload{std::move(responsePayload)},
            m_audioStream{std::move(audioStream)} {
    }

    std::string m_responseText;
    ResponseType m_responseType;
    ResponsePayload m_responsePayload;
    std::shared_ptr<std::istream> m_audioStream;
};

}  // namespace response
}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_RESPONSE_RESPONSE_H_
