cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(MultiAgentExperience-Integration-App VERSION 1.3 LANGUAGES CXX)
add_executable(MultiAgentExperience-Integration-App src/Application.cpp)

#################### MultiAgentExperience-API #################################
find_package(MultiAgentExperience-API REQUIRED)
target_link_libraries(MultiAgentExperience-Integration-App PRIVATE MAX::MultiAgentExperience-API)
#################### MultiAgentExperience-API #################################

#################### MultiAgentExperience #################################
find_package(MultiAgentExperience REQUIRED)
target_link_libraries(MultiAgentExperience-Integration-App PRIVATE MAX::MultiAgentExperience)
#################### MultiAgentExperience #################################

#################### MultiAgentExperience-Logger #################################
find_package(MultiAgentExperience-Logger REQUIRED)
target_link_libraries(MultiAgentExperience-Integration-App PRIVATE MAX::MultiAgentExperience-Logger)
#################### MultiAgentExperience-Logger #################################

#################### MultiAgentExperience-CommandLine-Orchestrator #################################
find_package(MultiAgentExperience-CommandLine-Orchestrator REQUIRED)
target_link_libraries(MultiAgentExperience-Integration-App PRIVATE MAX::MultiAgentExperience-CommandLine-Orchestrator)
#################### MultiAgentExperience-CommandLine-Orchestrator #################################

###################### Threads ###########################################
find_package(Threads REQUIRED)
target_link_libraries(MultiAgentExperience-Integration-App PRIVATE Threads::Threads)
###################### Threads ###########################################

#################### AlexaSDK #################################
find_package(PkgConfig)
pkg_check_modules(AlexaClientSDK REQUIRED
        AlexaClientSDK
        )
target_link_libraries(MultiAgentExperience-Integration-App PRIVATE ${AlexaClientSDK_LINK_LIBRARIES})
target_include_directories(MultiAgentExperience-Integration-App PRIVATE ${AlexaClientSDK_INCLUDE_DIRS})
#################### AlexaSDK #################################

target_compile_features(MultiAgentExperience-Integration-App PUBLIC cxx_std_14)
set_target_properties(MultiAgentExperience-Integration-App PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(MultiAgentExperience-Integration-App PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON)

if(MULTI_AGENT_EXPERIENCE_ENABLED)
    add_definitions(-DMULTI_AGENT_EXPERIENCE)
endif()

include_directories(include)
add_subdirectory(src)
include(cmake/Install.cmake)

