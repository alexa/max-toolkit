target_sources(
        MultiAgentExperience-Alexa-Adapter
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiAgentExperience/AlexaAdapter/Activity/AlexaActivityHandler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiAgentExperience/AlexaAdapter/Activity/AlexaActivityRequest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiAgentExperience/AlexaAdapter/Alexa/AlexaChannelNames.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiAgentExperience/AlexaAdapter/Alexa/AlexaExperienceIds.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiAgentExperience/AlexaAdapter/Alexa/AlexaExperiencePriorities.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiAgentExperience/AlexaAdapter/Alexa/AlexaFocusRequestBuffer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiAgentExperience/AlexaAdapter/Agent/AlexaAgentRegistration.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiAgentExperience/AlexaAdapter/Agent/MAXConnection.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiAgentExperience/AlexaAdapter/Dialog/AlexaDialogRequest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiAgentExperience/AlexaAdapter/Dialog/AlexaDialogTransitionHandler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiAgentExperience/AlexaAdapter/Experience/AlexaNotificationsObserver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiAgentExperience/AlexaAdapter/Experience/DoNotDisturbSettingObserver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiAgentExperience/AlexaAdapter/Dialog/AlexaControlReceiver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiAgentExperience/AlexaAdapter/Mediator/MAXFocusMediatorCleanupCallback.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiAgentExperience/AlexaAdapter/Mediator/MAXActivityFocusRequester.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiAgentExperience/AlexaAdapter/Mediator/MAXDialogFocusRequester.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiAgentExperience/AlexaAdapter/Mediator/MAXDialogUXStateObserver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiAgentExperience/AlexaAdapter/Mediator/MAXFocusMediator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiAgentExperience/AlexaAdapter/UniversalDeviceController/UniversalDeviceCommandsInvoker.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/MultiAgentExperience/AlexaAdapter/UniversalDeviceController/UniversalDeviceCommandsProvider
)

#Set flags to use AVS-SDK Logger
add_definitions("-DACSDK_LOG_MODULE=max_adapter")
target_compile_options(MultiAgentExperience-Alexa-Adapter PUBLIC -DACSDK_LOG_ENABLED $<$<CONFIG:Debug>:-DACSDK_DEBUG_LOG_ENABLED>)
