cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(MultiAgentExperience-IPC VERSION 2.0.0 LANGUAGES CXX)

include(CTest)

add_library(MultiAgentExperience-IPC SHARED)

add_custom_target(dev)
add_dependencies(dev MultiAgentExperience-IPC)

set_target_properties(MultiAgentExperience-IPC
        PROPERTIES VERSION
        "${MultiAgentExperience-IPC_VERSION_MAJOR}.${MultiAgentExperience-IPC_VERSION_MINOR}"
        )

# Set include directories
# The generator expressions evaluate to include or "" depending on whether or not we are currently building
# or installing. This way we never have to rely on relative path expansion (which isn't supported)
target_include_directories(MultiAgentExperience-IPC PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${MultiAgentExperience-IPC_SOURCE_DIR}/include>
        )

#################### MultiAgentExperience-API #################################
find_package(MultiAgentExperience-API REQUIRED)
target_link_libraries(MultiAgentExperience-IPC PRIVATE MAX::MultiAgentExperience-API)
#################### MultiAgentExperience-API #################################

#################### MultiAgentExperience-ThreadExecutor #################################
find_package(MultiAgentExperience-ThreadExecutor REQUIRED)
target_link_libraries(MultiAgentExperience-IPC PRIVATE MAX::MultiAgentExperience-ThreadExecutor)
#################### MultiAgentExperience-ThreadExecutor #################################

#################### MultiAgentExperience-Logger #################################
find_package(MultiAgentExperience-Logger REQUIRED)
target_link_libraries(MultiAgentExperience-IPC PRIVATE MAX::MultiAgentExperience-Logger)
#################### MultiAgentExperience-Logger #################################

add_subdirectory(src)
include(cmake/Install.cmake)
