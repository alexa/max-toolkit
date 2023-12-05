cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(MultiAgentExperience-IPC-gRPC VERSION 2.0.0 LANGUAGES CXX)

include(CTest)

add_library(MultiAgentExperience-IPC-gRPC SHARED)

add_custom_target(dev)
add_dependencies(dev MultiAgentExperience-IPC-gRPC)

set_target_properties(MultiAgentExperience-IPC-gRPC
        PROPERTIES VERSION
        "${MultiAgentExperience-IPC-gRPC_VERSION_MAJOR}.${MultiAgentExperience-IPC-gRPC_VERSION_MINOR}"
        )

# Set up the compiler flags.
target_compile_features(MultiAgentExperience-IPC-gRPC PUBLIC cxx_std_11)
set_target_properties(MultiAgentExperience-IPC-gRPC PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(MultiAgentExperience-IPC-gRPC PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON)

# Set include directories
# The generator expressions evaluate to include or "" depending on whether or not we are currently building
# or installing. This way we never have to rely on relative path expansion (which isn't supported)
target_include_directories(MultiAgentExperience-IPC-gRPC PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${MultiAgentExperience-IPC-gRPC_SOURCE_DIR}/include>
        )

#################### MultiAgentExperience-API #################################
find_package(MultiAgentExperience-API REQUIRED)
target_link_libraries(MultiAgentExperience-IPC-gRPC PRIVATE MAX::MultiAgentExperience-API)
#################### MultiAgentExperience-API #################################

#################### MultiAgentExperience-ThreadExecutor #################################
find_package(MultiAgentExperience-ThreadExecutor REQUIRED)
target_link_libraries(MultiAgentExperience-IPC-gRPC PRIVATE MAX::MultiAgentExperience-ThreadExecutor)
#################### MultiAgentExperience-ThreadExecutor #################################

#################### MultiAgentExperience-Logger #################################
find_package(MultiAgentExperience-Logger REQUIRED)
target_link_libraries(MultiAgentExperience-IPC-gRPC PRIVATE MAX::MultiAgentExperience-Logger)
#################### MultiAgentExperience-Logger #################################

#################### MultiAgentExperience-IPC #################################
find_package(MultiAgentExperience-IPC REQUIRED)
target_link_libraries(MultiAgentExperience-IPC-gRPC PRIVATE MAX::MultiAgentExperience-IPC)
#################### MultiAgentExperience-IPC #################################

#################### gRPC #################################
add_subdirectory(protobuf)
target_link_libraries(MultiAgentExperience-IPC-gRPC PRIVATE
        maxrpc_grpc_proto)

target_include_directories(MultiAgentExperience-IPC-gRPC PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/protobuf)
#################### gRPC #################################

add_subdirectory(src)
include(cmake/Install.cmake)

