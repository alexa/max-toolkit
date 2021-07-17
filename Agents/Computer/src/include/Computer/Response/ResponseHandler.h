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

#ifndef MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_RESPONSE_RESPONSE_HANDLER_H_
#define MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_RESPONSE_RESPONSE_HANDLER_H_

#include <MultiAgentExperience/Dialog/DialogControllerInterface.h>

#include "Computer/Audio/ComputerSoundFilePlayer.h"
#include "Computer/Response/Response.h"
#include "Computer/Response/SpeechResponder.h"

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {
namespace response {

class ResponseHandler : public std::enable_shared_from_this<ResponseHandler> {
public:
    ResponseHandler(
        std::shared_ptr<SpeechResponder> speechResponder,
        std::shared_ptr<audio::ComputerSoundFilePlayer> soundPlayer);

    void handleResponse(
        std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> controller,
        std::shared_ptr<Response> response);

private:
    std::shared_ptr<SpeechResponder> m_speechResponder;
    std::shared_ptr<audio::ComputerSoundFilePlayer> m_soundPlayer;
};

}  // namespace response
}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_AGENTS_COMPUTER_RESPONSE_RESPONSE_HANDLER_H_
