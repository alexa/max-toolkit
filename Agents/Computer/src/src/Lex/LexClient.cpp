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

#include "Computer/Lex/LexClient.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>

#include <aws/core/utils/Outcome.h>
#include <aws/lex/model/PostContentRequest.h>

#include <AVSCommon/Utils/JSON/JSONGenerator.h>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include "Utils/Base64.h"
#include "Utils/ControlTypeUtils.h"
#include "Utils/Logger.h"

using namespace alexaClientSDK;
using namespace alexaClientSDK::avsCommon;
using namespace alexaClientSDK::avsCommon::utils;
using namespace alexaClientSDK::avsCommon::utils::json;

using namespace Aws::Auth;
using namespace Aws::CognitoIdentity;
using namespace Aws::CognitoIdentity::Model;
using namespace Aws::LexRuntimeService::Model;

using namespace multiAgentExperience::dialog;
using namespace multiAgentExperience::samples::agents::computer::utils;
using namespace multiAgentExperience::samples::agents::computer::response;

using namespace rapidjson;

namespace MAX = multiAgentExperience;

namespace multiAgentExperience {
namespace samples {
namespace agents {
namespace computer {
namespace lex {

static const std::string MODULE_TAG("LexClient");
#define LX(logCommand, message) COMPUTER_AGENT_LOG_##logCommand("", MODULE_TAG, __func__, message)

static const std::string BOT_NAME = "ctdlComputer";
static const std::string BOT_ALIAS = "Demo";
static const std::string USER_ID = "ToyAgent";
static const std::string AWS_REGION = "us-west-2";
static const std::string AUDIO_FILE_NAME = "recorded.raw";
static const std::string AWS_ACCOUNT_ID = "926735276694";
static const std::string IDENTITY_POOL_ID = "us-west-2:0b017ce5-8d97-40b5-9b81-f0e9a8dd33ff";

static const char* ALLOCATION_TAG = "ComputerAgent";

static const long RECORDING_DURATION_IN_SECONDS = 5;

/**
 * Utility function to clear the local audio file which is persisted to enable the Lex call.
 *
 * TODO VII-183: This implementation to be updated to stream audio directly to Lex, which will improve performance,
 * and also remove the need for this local file to be persisted.
 */
static void clearAudioFile() {
    FILE* fileHandle = fopen(AUDIO_FILE_NAME.c_str(), "wb");
    if (fileHandle) {
        fclose(fileHandle);
    } else {
        LX(ERROR, "Failed to open audio file for clearing.");
    }
}

Aws::Client::ClientConfiguration LexClient::getAwsClientConfiguration() {
    LX(DEBUG3, "");
    if (!m_awsClientConfiguration) {
        LX(DEBUG3, "creating.");
        m_awsClientConfiguration = std::make_shared<Aws::Client::ClientConfiguration>();
        m_awsClientConfiguration->region = Aws::String(AWS_REGION.c_str());
    }

    LX(DEBUG3, "returning");

    return *m_awsClientConfiguration;
}

LexClient::LexClient(
    std::shared_ptr<response::ResponseHandler> responseHandler,
    std::shared_ptr<MAX::audio::AudioReaderInterface> audioReader) :
        m_responseHandler{responseHandler},
        m_audioReader{audioReader} {
    Aws::InitAPI(m_awsSdkOptions);
    m_lexClient = std::make_shared<Aws::LexRuntimeService::LexRuntimeServiceClient>(
        getCognitoCredentialsProvider(), getAwsClientConfiguration());
}

LexClient::~LexClient() {
    Aws::ShutdownAPI(m_awsSdkOptions);
}

bool LexClient::recordAudio(std::set<control::ControlType> activityControls, bool autoStopRecording) {
    LX(DEBUG3, "");

    m_activeActivityControls = activityControls;

    auto format = m_audioReader->getAudioFormat();
    m_audioReader->seekToNow();

    if (format.sampleRateHz != 16000 && format.sampleRateHz != 8000) {
        LX(ERROR, "unsupportedSampleRateForPCM:" + std::to_string(format.sampleRateHz));
        return false;
    }

    if (format.numChannels != 1) {
        LX(ERROR, "unsupportedNumChannels:" + std::to_string(format.numChannels));
        return false;
    }

    int bitsPerSample = format.wordsPerSample * format.wordSizeBits;
    if (bitsPerSample != 16) {
        LX(ERROR, "unsupportedBitsPerSample:" + std::to_string(bitsPerSample));
        return false;
    }

    m_voiceActivityDetector.initialize(format.sampleRateHz);

    // Record audio to file
    m_voiceActivityDetector.reset();

    // note : 2 bytes per word, hence int16_t buffer type. This is clearly not parameterized right now.
    long wordsToRead = RECORDING_DURATION_IN_SECONDS * format.sampleRateHz;
    long wordsReadSoFar = 0;
    long numWordsPerBuffer = 1024;
    int16_t buffer[numWordsPerBuffer];

    // Write audio
    FILE* fid = fopen(AUDIO_FILE_NAME.c_str(), "wb");
    if (!fid) {
        LX(ERROR, "Failed to write audio to file");
        return false;
    } else {
        while (wordsReadSoFar < wordsToRead) {
            auto numBytesRead = m_audioReader->read(&buffer, numWordsPerBuffer * format.wordsPerSample);
            if (numBytesRead < 0) {
                return false;
            }

            auto numWordsRead = numBytesRead / format.wordsPerSample;
            bool silenced = m_voiceActivityDetector.processFrame(buffer, numWordsRead);

            auto wordsWrittenToFile = fwrite(&buffer, format.wordsPerSample, numWordsRead, fid);
            wordsReadSoFar += numWordsRead;

            if (silenced && autoStopRecording) {
                LX(DEBUG3, "Silence detected:" + std::to_string(wordsReadSoFar));
                break;
            }
        }

        fclose(fid);
    }

    return true;
}

void LexClient::stopRecording() {
    LX(DEBUG3, "");
}

std::shared_ptr<Response> LexClient::processRequest() {
    LX(DEBUG3, "");

    // Create Lex Request
    const std::shared_ptr<Aws::IOStream> input_data =
        Aws::MakeShared<Aws::FStream>(ALLOCATION_TAG, AUDIO_FILE_NAME, std::ios_base::in | std::ios_base::binary);
    Aws::LexRuntimeService::Model::PostContentRequest request;
    const std::string contentType(
        "audio/l16; rate=" + std::to_string(m_audioReader->getAudioFormat().sampleRateHz) + "; channels=1");
    request.SetBotName(BOT_NAME.c_str());
    request.SetBotAlias(BOT_ALIAS.c_str());
    request.SetUserId(USER_ID.c_str());
    request.SetContentType(contentType.c_str());
    request.SetAccept("audio/mpeg");
    request.SetBody(input_data);
    request.SetSessionAttributes(base64_encode("{}").c_str());

    // Generate request attributes
    if (!m_activeActivityControls.empty()) {
        for (auto controlType : m_activeActivityControls) {
            LX(DEBUG3, ControlTypeUtils::getNameForControlType(controlType) + " available");
        }

        std::string activityControls = "{\"availableActivityControls\" : \"[";
        for (control::ControlType controlType : m_activeActivityControls) {
            auto controlName = ControlTypeUtils::getNameForControlType(controlType);
            if (controlName != "UNDEFINED") {
                activityControls += ("\\\"" + controlName + "\\\"" + ",");
            }
        }
        if (activityControls.back() == ',') {
            activityControls.pop_back();
        }
        activityControls += "]\"}";
        request.SetRequestAttributes(base64_encode(activityControls).c_str());
    }

    // Make the call to Lex
    auto outcome = m_lexClient->PostContent(request);

    // Process Response
    if (outcome.IsSuccess()) {

        // At this point, Lex is done reading the audio data, so let's clear the file.
        clearAudioFile();

        auto result = outcome.GetResultWithOwnership();

        auto sessionAttributes = base64_decode(result.GetSessionAttributes().c_str());
        std::string responseType = "";
        std::string responsePayload = "";

        if (!sessionAttributes.empty()) {
            Document jsonDocument;
            jsonDocument.Parse(sessionAttributes.c_str());
            if (jsonDocument.IsObject()) {
                if (jsonDocument.HasMember("responseType") && jsonDocument.HasMember("responsePayload")) {
                    Value::MemberIterator responseTypeObject = jsonDocument.FindMember("responseType");
                    Value::MemberIterator responsePayloadObject = jsonDocument.FindMember("responsePayload");
                    if (responseTypeObject != jsonDocument.MemberEnd() &&
                        responsePayloadObject != jsonDocument.MemberEnd() && responseTypeObject->value.IsString() &&
                        responsePayloadObject->value.IsString()) {
                        responseType = responseTypeObject->value.GetString();
                        responsePayload = responsePayloadObject->value.GetString();
                    }
                }
            }
        }

        if (!responseType.empty()) {
            std::stringstream ss;
            ss << "Received Custom Response|type:" << responseType << ", payload:" << responsePayload;
            LX(DEBUG3, ss.str());

            std::string responseText = "";
            if (!result.GetMessage().empty()) {
                responseText = std::string(result.GetMessage().c_str());
            }
            if (result.GetAudioStream()) {
                auto audioStream = std::make_shared<std::istream>(nullptr);
                // Point the underlying stream buffer to the original audio stream buffer
                audioStream->rdbuf(result.GetAudioStream().rdbuf());
                result.GetAudioStream().rdbuf(nullptr);
                return Response::createResponse(responseText, responseType, responsePayload, audioStream);
            }
            return Response::createResponse(responseText, responseType, responsePayload);
        } else {
            LX(DEBUG3, "Received Speak Response -> " + std::string(result.GetMessage().c_str()));
            // Return audio stream response
            auto audioStream = std::make_shared<std::istream>(nullptr);
            // Point the underlying stream buffer to the original audio stream buffer
            audioStream->rdbuf(result.GetAudioStream().rdbuf());
            auto responseText = std::string(result.GetMessage().c_str());
            result.GetAudioStream().rdbuf(nullptr);
            return Response::createSpeakResponse(responseText, audioStream);
        }
    } else {
        clearAudioFile();

        std::stringstream ss;
        ss << "Failed to process request|" << outcome.GetError();
        LX(ERROR, ss.str());
        return Response::createErrorResponse();
    }
}

std::shared_ptr<CognitoCachingAnonymousCredentialsProvider> LexClient::getCognitoCredentialsProvider() {
    LX(DEBUG3, "");

    auto cognitoIdentityClient = Aws::MakeShared<CognitoIdentityClient>(
        ALLOCATION_TAG, Aws::MakeShared<AnonymousAWSCredentialsProvider>(ALLOCATION_TAG), getAwsClientConfiguration());
    auto cognitoCredentialsProvider = Aws::MakeShared<CognitoCachingAnonymousCredentialsProvider>(
        ALLOCATION_TAG, AWS_ACCOUNT_ID.c_str(), IDENTITY_POOL_ID.c_str(), cognitoIdentityClient);

    return cognitoCredentialsProvider;
}

void LexClient::onStartListening(
    std::shared_ptr<DialogControllerInterface> controller,
    std::set<control::ControlType> controls) {
    LX(DEBUG3, "");

    auto listen = [this, controls]() { return recordAudio(controls, true); };

    auto result = m_executor.submit(listen);

    if (result.get()) {
        controller->startThinking();
    } else {
        controller->stop();
    }
}

void LexClient::onStopListening() {
    LX(DEBUG3, "");
}

void LexClient::onStartThinking(std::shared_ptr<DialogControllerInterface> controller) {
    LX(DEBUG3, "");
    auto response = processRequest();
    m_responseHandler->handleResponse(controller, response);
}

void LexClient::onStopThinking() {
    LX(DEBUG3, "");
}

}  // namespace lex
}  // namespace computer
}  // namespace agents
}  // namespace samples
}  // namespace multiAgentExperience
