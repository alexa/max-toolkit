include(CMakePackageConfigHelpers)

#install targets
install(TARGETS MultiAgentExperience-IPC-gRPC
    EXPORT MultiAgentExperience-IPC-gRPCTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

install(DIRECTORY include/
    DESTINATION include
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/protobuf/maxrpc.grpc.pb.h" "${CMAKE_CURRENT_BINARY_DIR}/protobuf/maxrpc.pb.h"
        DESTINATION include  # install protobuf generated dependencies in include directory
        )

#build directory export
install(EXPORT MultiAgentExperience-IPC-gRPCTargets
    FILE MultiAgentExperience-IPC-gRPCTargets.cmake
    NAMESPACE MAX::
    DESTINATION cmake
)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-IPC-gRPCConfig.cmake"
    INSTALL_DESTINATION cmake
)

# generate the version file for the config file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-IPC-gRPCConfigVersion.cmake"
    VERSION "${MultiAgentExperience-IPC-gRPC_VERSION_MAJOR}.${MultiAgentExperience-IPC-gRPC_VERSION_MINOR}"
    COMPATIBILITY AnyNewerVersion
)


install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-IPC-gRPCConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-IPC-gRPCConfigVersion.cmake"
    DESTINATION cmake
)

export(EXPORT MultiAgentExperience-IPC-gRPCTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-IPC-gRPCTargets.cmake"
    NAMESPACE MAX::
)

# uninstall target
if(NOT TARGET uninstall)
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/CMakeUninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY
    )

    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake
    )
endif()
