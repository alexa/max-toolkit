target_sources(
        MultiAgentExperience-IPC-gRPC
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/GrpcClient.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/GrpcServer.cpp
)