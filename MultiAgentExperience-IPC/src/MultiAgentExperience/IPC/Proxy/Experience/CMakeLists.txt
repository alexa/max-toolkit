target_sources(
        MultiAgentExperience-IPC
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/ExperienceControllerMessageHandler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ExperienceControllerProxy.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/StaticExperienceManagerProxy.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/StaticExperienceManagerMessageHandler.cpp
)