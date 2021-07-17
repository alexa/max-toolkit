cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# Set project information
project(SampleApplication VERSION 0.4.0 LANGUAGES CXX)
set(PROJECT_BRIEF "An Application which demonstrates the MAX library, enabling multi-agent co-existence and co-operation.")

if (ENABLE_DEMO_ONLY_SOFTWARE_CROSSWAKE_DETECTION)
    message("")
    message("***********************************************************************************************************")
    message("* WARNING - Enabling DEMO-ONLY crosswake detection for the Sample Application.")
    message("*")
    message("* This functionality emulates Audio Front End (AFE) hardware, and tests if an Agent's speech contains the")
    message("* wakeword of another Agent that may be registered with the MAX Library. Without an AFE, this will result")
    message("* in an active wakeword engine detecting the wakeword, and appear to the application as if the user had")
    message("* said the wakeword. The original Agent will then be interrupted in favor of the Agent whose wakeword it")
    message("* just spoke.")
    message("*")
    message("* This trivial implementation, when activated, disallows user barge-in on an Agent's speech when another")
    message("* Agent's wakeword is present. This should be enabled ONLY for demonstration purposes on devices without")
    message("* sufficient hardware, and for the purposes of testing cases where an Agent speaking another Agent's name")
    message("* causes that Agent to interrupt and begin listening.")
    message("***********************************************************************************************************")
    message("")
    add_definitions(-DENABLE_DEMO_ONLY_SOFTWARE_CROSSWAKE_DETECTION)
endif()

if (NOT DEFINED PORTAUDIO)
    message("To build the MAX SampleApplication, please enable PortAudio.")
    return()
endif()

if (NOT DEFINED GSTREAMER_MEDIA_PLAYER)
    message("To build the MAX SampleApplication, please enable GStreamer.")
    return()
endif()

if (OVERRIDE_ALSA_SINK)
    add_definitions(-DOVERRIDE_ALSA_SINK)
endif()

include(BuildUtils/BuildDefaults.cmake)

#    include(BuildUtils/Testing.cmake)

# Set variables for target install and .pc pkg-config file
include(BuildUtils/PrepareInstall.cmake)

# Create .pc pkg-config file
include(BuildUtils/GeneratePkgConfig.cmake)

set(LibSampleApplication_SOURCES)

list(APPEND LibSampleApplication_SOURCES
        src/Application.cpp
        src/ApplicationConfig.cpp
        src/AgentManager/AgentManager.cpp
        src/AgentManager/AgentsConfig.cpp
        src/AgentManager/AgentFactory.cpp
        src/AgentManager/Alexa/AlexaAgentFactory.cpp
        src/AgentManager/Alexa/DefaultClientFactory.cpp
        src/AgentManager/Computer/ComputerAgentFactory.cpp
        src/AgentManager/Alexa/AlexaActiveAgentSpeechStore.cpp
        src/AgentManager/Computer/ComputerAudioReader.cpp
        src/AgentManager/Computer/ComputerActiveAgentSpeechStore.cpp
        src/AudioManager/AudioManager.cpp
        src/AudioManager/AudioConfig.cpp
        src/AudioManager/Wakeword/WakewordMetadataCache.cpp
        src/AudioManager/Wakeword/CrosswakeDetector/SimpleCrosswakeDetector.cpp
        src/AudioManager/Microphone/MicrophoneConfig.cpp
        src/AudioManager/Microphone/PortAudioMicrophone.cpp
        src/AudioManager/SDS/SDSReader.cpp
        src/AudioManager/Wakeword/WakewordEngine.cpp
        src/AudioManager/Wakeword/WakewordEnginesConfig.cpp
        src/AudioManager/Wakeword/WakewordEngineFactory.cpp
        src/AudioManager/Wakeword/AVSSDK/AVSSDK_KWDAdapter.cpp
        src/ExperienceManager/ExperienceManager.cpp
        src/ExperienceManager/Console/ConsoleExperienceRenderer.cpp
        src/ExperienceManager/SenseHAT/SenseHatExperienceRenderer.cpp
        src/UIManager/UIManager.cpp
        src/UIManager/ConsoleReader.cpp
        src/UIManager/ConsolePrinter.cpp
        src/UIManager/InputHandler.cpp
        src/UIManager/InteractionHandler.cpp
        src/UniversalDeviceCommandManager/Console/ConsoleCommandRenderer.cpp
        src/UniversalDeviceCommandManager/UniversalDeviceCommandManager.cpp
        src/Utils/JSONUtils.cpp
        src/Utils/StringUtils.cpp
        src/Utils/RadiantLogger.cpp
        src/Utils/AVSSDK/AVSSDKUtilities.cpp
        src/Utils/AVSSDK/CustomLogger.cpp
        )

option(RPI_LEDS "Enable RPi LED Sense Hat" OFF)

if(RPI_LEDS)
    message("Building with LED Sense Hat for RPI enabled.")
    add_definitions(-DRPI_LED_SENSE_HAT)
    add_definitions("-DRPI_LED_ANIMATIONS=${PROJECT_SOURCE_DIR}/Assets/Animations/")
    list(APPEND LibSampleApplication_SOURCES
            src/ExperienceManager/SenseHAT/LEDController/AnimationEngine.cpp
            src/ExperienceManager/SenseHAT/LEDController/AnimationLine.cpp
            src/ExperienceManager/SenseHAT/LEDController/AnimationSequence.cpp
            src/ExperienceManager/SenseHAT/LEDController/Buffer.cpp
            src/ExperienceManager/SenseHAT/LEDController/DrawContext.cpp
            src/ExperienceManager/SenseHAT/LEDController/PiSenseMatrix.cpp
            src/ExperienceManager/SenseHAT/LEDController/Utils.cpp
    )
endif()

# Fix for OSX platforms. Details: https://gitlab.kitware.com/cmake/cmake/-/issues/19120
if (APPLE)
    link_directories(/usr/local/lib)
endif()

if (SNOWBOY_KEYWORD_DETECTOR)
    if(NOT SNOWBOY_KEYWORD_DETECTOR_LIB_PATH)
        message(FATAL_ERROR "Must pass library path of Snowboy KeywordDetector.")
    endif()
    if(NOT SNOWBOY_KEYWORD_DETECTOR_INCLUDE_DIR)
        message(FATAL_ERROR "Must pass include dir path of Snowboy KeywordDetector.")
    endif()
    message("Building with Snowboy Keyword Detector enabled.")
    add_definitions(-DBUILD_WITH_SNOWBOY)
    list(APPEND LibSampleApplication_SOURCES
            src/AudioManager/Wakeword/KittAi/SnowboyKWD.cpp
            src/AudioManager/Wakeword/KittAi/SnowboyWrapper.cpp
            )
endif()

add_library(LibSampleApplication SHARED ${LibSampleApplication_SOURCES})

target_compile_features(LibSampleApplication PUBLIC cxx_std_11)
set_target_properties(LibSampleApplication PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(LibSampleApplication PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(MultiAgentExperience 0.4 REQUIRED)
target_link_libraries(LibSampleApplication PUBLIC MAX::MultiAgentExperience)

find_package(ComputerAgent 0.4 REQUIRED)
target_link_libraries(LibSampleApplication PUBLIC MAX::ComputerAgent)

if (SNOWBOY_KEYWORD_DETECTOR)
    target_include_directories(LibSampleApplication PUBLIC "${SNOWBOY_KEYWORD_DETECTOR_INCLUDE_DIR}")
    target_link_libraries(LibSampleApplication PRIVATE "${SNOWBOY_KEYWORD_DETECTOR_LIB_PATH}" blas)
endif()

if (SNOWBOY_KEYWORD_DETECTOR)
    target_compile_definitions(LibSampleApplication PUBLIC LINK_AGAINST_AVS_SDK_KWDPROVIDER)
    target_link_libraries(LibSampleApplication PUBLIC KeywordDetectorProvider)
endif()

target_include_directories(LibSampleApplication PUBLIC
        "${SampleApplication_SOURCE_DIR}/include"
        "${GST_INCLUDE_DIRS}"
        "${MAX_INCLUDE_DIR}"
        "${COMPUTER_AGENT_INCLUDE_DIR}"
        "${PORTAUDIO_INCLUDE_DIR}")

add_definitions(${GLIB_CFLAGS} ${GLIB_CFLAGS_OTHER})

# Fix for OSX platforms. Details: https://gitlab.kitware.com/cmake/cmake/-/issues/19120
if (APPLE)
    target_include_directories(LibSampleApplication PUBLIC /usr/local/include)
endif()

target_link_libraries(LibSampleApplication
        PUBLIC
        acsdkAlerts
        acsdkBluetooth
        acsdkCore
        acsdkDefaultSampleApplicationOptions
        acsdkManufactory
        acsdkNotifications
        acsdkShared
        ACL
        AFML
        AudioResources
        AVSCommon
        AVSGatewayManager
        CapabilitiesDelegate
        CBLAuthDelegate
        CertifiedSender
        ContextManager
        DefaultClient
        DeviceSettings
        acsdkEqualizer
        acsdkEqualizerImplementations
        InterruptModel
        LibSampleApp
        KWD
        MediaPlayer
        RegistrationManager
        SpeakerManager
        SQLiteStorage
        SynchronizeStateSender
        "${MAX_LIB_PATH}"
        "${COMPUTER_AGENT_LIB_PATH}"
        "${PORTAUDIO_LIB_PATH}")

if (SNOWBOY_KEYWORD_DETECTOR)
    target_compile_definitions(LibSampleApplication PUBLIC LINK_AGAINST_AVS_SDK_KWDPROVIDER)
    target_link_libraries(LibSampleApplication PUBLIC KeywordDetectorProvider)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    target_link_libraries(LibSampleApplication
            PUBLIC
            "-framework CoreAudio"
            "-framework AudioToolbox"
            "-framework AudioUnit"
            "-framework CoreServices"
            "-framework Carbon"
            )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(LibSampleApplication
            PUBLIC
            rt
            m
            pthread
            asound
            atomic
            )
endif()

if (GSTREAMER_MEDIA_PLAYER)
    target_link_libraries(LibSampleApplication PUBLIC "${GST_LDFLAGS}")
endif()

add_executable(SampleApplication src/main.cpp)

target_compile_features(SampleApplication PUBLIC cxx_std_11)
set_target_properties(SampleApplication PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(SampleApplication PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON)

target_link_libraries(SampleApplication LibSampleApplication)

# install target
asdk_install_targets(SampleApplication TRUE)
