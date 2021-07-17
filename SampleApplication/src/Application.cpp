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

#include "SampleApplication/Application.h"

#include <chrono>
#include <csignal>
#include <fstream>
#include <thread>

#include <MultiAgentExperience/Agent/Agent.h>
#include <MultiAgentExperience/Application/MAXFactory.h>

#include "SampleApplication/AgentManager/GestureHandlerInterface.h"
#include "SampleApplication/ApplicationConfig.h"
#include "SampleApplication/AudioManager/AudioConfig.h"
#include "SampleApplication/AudioManager/Microphone/MicrophoneConfig.h"
#include "SampleApplication/AudioManager/Microphone/PortAudioMicrophone.h"
#include "SampleApplication/AudioManager/Wakeword/AVSSDK/AVSSDK_KWDAdapter.h"
#include "SampleApplication/AudioManager/Wakeword/WakewordEnginesConfig.h"
#include "SampleApplication/ExperienceManager/Console/ConsoleExperienceRenderer.h"
#include "SampleApplication/ExperienceManager/SenseHAT/SenseHatExperienceRenderer.h"
#include "SampleApplication/UIManager/ConsolePrinter.h"
#include "SampleApplication/UIManager/InputHandler.h"
#include "SampleApplication/UIManager/InteractionHandler.h"
#include "SampleApplication/Utils/AVSSDK/CustomLogger.h"
#include "SampleApplication/Utils/AVSSDK/AVSSDKUtilities.h"
#include "SampleApplication/Utils/JSONUtils.h"
#include "SampleApplication/Utils/RadiantLogger.h"

namespace multiAgentExperience {
namespace sampleApplication {

using namespace rapidjson;

namespace MAX = multiAgentExperience;

/// The default log level we will use before we've parsed our input config.
static const MAX::utils::Log::Level DEFAULT_GLOBAL_LOG_LEVEL = MAX::utils::Log::Level::DEBUG3;

/// Metadata parameters that will be passed into our logging system.
static const std::string MODULE_TAG("Application");
#define LX(logCommand, message) \
    SAMPLE_APP_LOG_##logCommand(utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MODULE_TAG, __func__, message)

/**
 * Allows the process to ignore the SIGPIPE signal. The SIGPIPE signal may be received when the application performs a
 * write to a closed socket. This is a case that arises in the use of certain networking libraries.
 *
 * @return true if the action for handling SIGPIPEs was correctly set to ignore, else false.
 */
static bool ignoreSigpipeSignals() {
#ifndef NO_SIGPIPE
    if (std::signal(SIGPIPE, SIG_IGN) == SIG_ERR) {
        return false;
    }
#endif
    return true;
}

/**
 * Utility function to read the text from a file.
 *
 * @param path Path to the file which we wish to read.
 * @param fileText [out] The text from the file which is read.
 * @return Whether the read was successful.
 */
static bool getConfigFileText(const std::string& path, std::string* fileText) {
    LX(DEBUG3, "file path:" + path);
    std::ifstream fileStream(path);
    if (!fileStream.good()) {
        LX(ERROR, std::string("Failed to open path:") + path);
        return false;
    }

    *fileText = std::string((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
    return true;
}

/**
 * Utility function to perform a rapidjson parse on a given JSON string.
 *
 * @param maxConfigPath A string which contains our JSON to be parsed.
 * @param jsonDocument [out] The rapidjson document that will be created.
 * @return Whether the rapidjson parse was successful.
 */
static bool getParsedJSONDocumentRoot(const std::string& maxConfigPath, Document* jsonDocument) {
    LX(DEBUG3, "file path:" + maxConfigPath);

    std::string fileText;
    if (!getConfigFileText(maxConfigPath, &fileText)) {
        LX(ERROR, "Unable to read JSON from the provided config file path:" + maxConfigPath);
        return false;
    }

    if (!utils::performInitialJSONParse(fileText, jsonDocument)) {
        LX(ERROR, "Unable to parse the file contents as JSON. Text:" + fileText);
        return false;
    }

    return true;
}

std::unique_ptr<Application> Application::create(const std::string& maxConfigPath) {
    // by default, let's make AVS SDK logging error only. Note that MAX config settings may override this shortly.
    //    utils::RadiantLogger::instance()->setComponentLevel(
    //        utils::RadiantLogger::AVS_SDK_COMPONENT_NAME, MAX::utils::Log::Level::ERROR);

    // set our log levels for MAX LIB so we can capture anything it logs above INFO before we read our config.
    utils::RadiantLogger::instance()->setComponentLevel(
        utils::RadiantLogger::MAX_APP_COMPONENT_NAME, MAX::utils::Log::Level::WARN);
    utils::RadiantLogger::instance()->setComponentLevel(
        utils::RadiantLogger::AVS_SDK_COMPONENT_NAME, MAX::utils::Log::Level::WARN);
    utils::RadiantLogger::instance()->setComponentLevel(
        utils::RadiantLogger::MAX_LIB_COMPONENT_NAME, MAX::utils::Log::Level::WARN);
    utils::RadiantLogger::instance()->setComponentLevel(
        utils::RadiantLogger::COMPUTER_AGENT_COMPONENT_NAME, MAX::utils::Log::Level::WARN);

    LX(DEBUG3, "file path:" + maxConfigPath);

    if (maxConfigPath.empty()) {
        LX(ERROR, "ApplicationCreateFailed: MAX config filename is empty.");
        return nullptr;
    }

    // this will primarily provide minimal JSON metadata which AVS SDK components may then leverage upon instantiation.
    utils::avssdk::initializeAVSSDK();

    // let's register our logger with the AVS SDK.
    utils::avssdk::initializeLogger();

    actor::ActorId sampleAppActorId("sample-application");

    auto maxInterface = application::MAXFactory::create(
        sampleAppActorId, utils::RadiantLogger::instance(), utils::RadiantLogger::MAX_LIB_COMPONENT_NAME);
    if (!maxInterface) {
        LX(ERROR, "Error creating the MAX Interface.");
        return nullptr;
    }

    if (!ignoreSigpipeSignals()) {
        LX(ERROR, "Failed to set a signal handler for SIGPIPE.");
        return nullptr;
    }

    Document jsonDocument;
    if (!getParsedJSONDocumentRoot(maxConfigPath, &jsonDocument)) {
        LX(ERROR, "Unable to acquire application config.");
        return nullptr;
    }

    auto crosswakeDetector = std::make_shared<audioManager::wakeword::crosswake::SimpleCrosswakeDetector>();

    auto application = std::unique_ptr<Application>(new Application(crosswakeDetector, maxInterface));
    if (!application->initialize(jsonDocument)) {
        LX(ERROR, "Unable to initialize the application.");
        return nullptr;
    }

    LX(DEBUG3, "create successful.");

    return application;
}

Application::Application(
    std::shared_ptr<audioManager::wakeword::crosswake::SimpleCrosswakeDetector> crosswakeDetector,
    std::shared_ptr<application::MAXInterface> maxInterface) :
        m_crosswakeDetector{crosswakeDetector},
        m_maxInterface{maxInterface} {
}

bool Application::initialize(const rapidjson::Document& parsedJsonDocumentRoot) {
    LX(DEBUG3, "");

    ApplicationConfig config(DEFAULT_GLOBAL_LOG_LEVEL);
    if (!parseJSONConfig(parsedJsonDocumentRoot, &config)) {
        LX(ERROR, "Error parsing runtime options.");
        return false;
    }

    utils::RadiantLogger::instance()->setComponentLevel(
        utils::RadiantLogger::MAX_APP_COMPONENT_NAME, getApplicationLogLevel(config));
    utils::RadiantLogger::instance()->setComponentLevel(
        utils::RadiantLogger::AVS_SDK_COMPONENT_NAME, getAVSSDKLogLevel(config));
    utils::RadiantLogger::instance()->setComponentLevel(
        utils::RadiantLogger::MAX_LIB_COMPONENT_NAME, getMAXLogLevel(config));
    utils::RadiantLogger::instance()->setComponentLevel(
        utils::RadiantLogger::COMPUTER_AGENT_COMPONENT_NAME, getComputerAgentLogLevel(config));

    m_audioManager = audioManager::AudioManager::create(
        m_crosswakeDetector, m_maxInterface->getWakewordObserver(), parsedJsonDocumentRoot);
    if (!m_audioManager) {
        LX(ERROR, "Unable to create audio manager.");
        return false;
    }

    m_agentManager = agentManager::AgentManager::create(
        m_maxInterface->getAgentManager(),
        parsedJsonDocumentRoot,
        m_audioManager->getAudioFormat(),
        m_audioManager,
        m_crosswakeDetector,
        m_audioManager->getMetadataCache());
    if (!m_agentManager) {
        LX(ERROR, "Unable to create agent manager.");
        return false;
    }

    m_audioManager->setGestureHandler(m_agentManager);

    m_experienceManager = experienceManager::ExperienceManager::create(m_maxInterface->getExperienceManager());
    if (!m_experienceManager) {
        LX(ERROR, "Unable to create experience manager.");
        return false;
    }

    m_udcManager = universalDeviceCommandManager::UniversalDeviceCommandManager::create(
        m_maxInterface->getControlManager(), m_maxInterface->getControlInvoker());
    if (!m_udcManager) {
        LX(ERROR, "Unable to create UDC manager.");
        return false;
    }

    m_uiManager = uiManager::UIManager::create(m_agentManager, m_udcManager, m_audioManager);
    if (!m_uiManager) {
        LX(ERROR, "Unable to create agent UI manager.");
        return false;
    }

    auto consoleExperienceRenderer =
        std::make_shared<experienceManager::console::ConsoleExperienceRenderer>(m_uiManager->getConsolePrinter());
    m_experienceManager->addRenderer(consoleExperienceRenderer);

    m_commandRenderer = std::make_shared<universalDeviceCommandManager::console::ConsoleCommandRenderer>(
        m_uiManager->getConsolePrinter());
    m_udcManager->addRenderer(m_commandRenderer);

#ifdef RPI_LED_SENSE_HAT
    auto senseHatExperienceRenderer = std::make_shared<experienceManager::senseHat::SenseHatExperienceRenderer>();
    m_experienceManager->addRenderer(senseHatExperienceRenderer);
#endif

    return true;
}

void Application::run() {
    LX(DEBUG3, "");

    if (!m_uiManager) {
        LX(WARN, "Run has been invoked without a UI manager. Exiting.");
        return;
    }

    m_uiManager->start();
}

}  // namespace sampleApplication
}  // namespace multiAgentExperience
