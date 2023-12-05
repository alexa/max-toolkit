set(APP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/Log/AppLogger.cpp)

if (MULTI_AGENT_EXPERIENCE_ENABLED)
    list(APPEND APP_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/Device/ConsoleExperienceRenderer.cpp)
endif()

target_sources(
        MultiAgentExperience-Integration-App
        PRIVATE
        ${APP_SOURCES})