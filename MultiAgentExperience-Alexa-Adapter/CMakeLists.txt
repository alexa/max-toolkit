cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# Check that the SDK meets the minimum version requirement to be used with this adapter.
set(AVS_DEVICE_SDK_MIN_VER "1.26.9")
set(MAX_API_MIN_VER "2.0.0")

project(MultiAgentExperience-Alexa-Adapter VERSION 2.0.0 LANGUAGES CXX)

include(${AVS_CMAKE_BUILD}/BuildDefaults.cmake)

add_library(MultiAgentExperience-Alexa-Adapter SHARED)
set_target_properties(MultiAgentExperience-Alexa-Adapter
        PROPERTIES VERSION
        "${MultiAgentExperience-Alexa-Adapter_VERSION_MAJOR}.${MultiAgentExperience-Alexa-Adapter_VERSION_MINOR}"
        )

# Set up the compiler flags.
target_compile_features(MultiAgentExperience-Alexa-Adapter PUBLIC cxx_std_11)
set_target_properties(MultiAgentExperience-Alexa-Adapter PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(MultiAgentExperience-Alexa-Adapter PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(MultiAgentExperience-Alexa-Adapter PRIVATE include)

# The MAX IPC solution specifically requires all the below packages
find_package(MultiAgentExperience-API REQUIRED)
find_package(MultiAgentExperience-Logger REQUIRED)
find_package(MultiAgentExperience-ThreadExecutor REQUIRED)
find_package(MultiAgentExperience-IPC REQUIRED)
find_package(MultiAgentExperience-IPC-gRPC REQUIRED)

# Needs to PUBLIC so that AVS SDK can find these libraries
target_link_libraries(MultiAgentExperience-Alexa-Adapter PUBLIC
        MAX::MultiAgentExperience-API
        MAX::MultiAgentExperience-Logger
        MAX::MultiAgentExperience-ThreadExecutor
        MAX::MultiAgentExperience-IPC
        MAX::MultiAgentExperience-IPC-gRPC
        AVSCommon)

#################### Protobuf and gRPC #################################
find_package(Protobuf REQUIRED)
message("Protobuf directory is ${Protobuf_DIR} with cross compilation - ${CMAKE_CROSSCOMPILING}")
message(STATUS "Using protobuf ${Protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)
if(CMAKE_CROSSCOMPILING)
    find_program(_PROTOBUF_PROTOC protoc)
else()
    set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
endif()

find_package(gRPC REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP gRPC::grpc++)
if(CMAKE_CROSSCOMPILING)
    find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
    set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif()

# Needs to PUBLIC so that AVS SDK can find these libraries
target_link_libraries(MultiAgentExperience-Alexa-Adapter PUBLIC
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF})
#################### Protobuf and gRPC #################################

add_subdirectory(src)

# Set include directories
# The generator expressions evaluate to include or "" depending on whether or not we are currently building
# or installing. This way we never have to rely on relative path expansion (which isn't supported)
target_include_directories(MultiAgentExperience-Alexa-Adapter PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${MultiAgentExperience-Alexa-Adapter_SOURCE_DIR}/include>
        )

# install target
asdk_install()
