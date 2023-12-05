cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(MultiAgentExperience-Integration-App VERSION 2.0 LANGUAGES CXX)
add_executable(MultiAgentExperience-Integration-App src/Application.cpp)

#################### MultiAgentExperience-API #################################
find_package(MultiAgentExperience-API REQUIRED)
target_link_libraries(MultiAgentExperience-Integration-App PRIVATE MAX::MultiAgentExperience-API)
#################### MultiAgentExperience-API #################################

#################### MultiAgentExperience-Logger #################################
find_package(MultiAgentExperience-Logger REQUIRED)
target_link_libraries(MultiAgentExperience-Integration-App PRIVATE MAX::MultiAgentExperience-Logger)
#################### MultiAgentExperience-API #################################

#################### MultiAgentExperience #################################
find_package(MultiAgentExperience REQUIRED)
target_link_libraries(MultiAgentExperience-Integration-App PRIVATE MAX::MultiAgentExperience)
#################### MultiAgentExperience #################################

#################### MultiAgentExperience-ThreadExecutor #################################
find_package(MultiAgentExperience-ThreadExecutor REQUIRED)
target_link_libraries(MultiAgentExperience-Integration-App PRIVATE MAX::MultiAgentExperience-ThreadExecutor)
#################### MultiAgentExperience-ThreadExecutor #################################

#################### MultiAgentExperience-IPC #################################
find_package(MultiAgentExperience-IPC)
target_link_libraries(MultiAgentExperience-Integration-App PRIVATE MAX::MultiAgentExperience-IPC)
#################### MultiAgentExperience-IPC #################################

#################### MultiAgentExperience-IPC-gRPC #################################
find_package(MultiAgentExperience-IPC-gRPC)
target_link_libraries(MultiAgentExperience-Integration-App PRIVATE MAX::MultiAgentExperience-IPC-gRPC)
#################### MultiAgentExperience-IPC-gRPC #################################

#################### Protobuf ####################
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
#################### Protobuf ####################

#################### GRPC ####################
find_package(gRPC REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP gRPC::grpc++)
if(CMAKE_CROSSCOMPILING)
    find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else()
    set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif()

target_link_libraries(MultiAgentExperience-Integration-App PRIVATE
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF}
        )
#################### GRPC ####################


#################### AlexaSDK #################################
find_package(PkgConfig)
pkg_check_modules(AlexaClientSDK REQUIRED
        AlexaClientSDK
        )

message(AlexaClientSDK_LINK_LIBRARIES ${AlexaClientSDK_LINK_LIBRARIES})
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
