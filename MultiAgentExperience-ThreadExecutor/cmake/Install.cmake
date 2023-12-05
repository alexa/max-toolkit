include(CMakePackageConfigHelpers)

#install targets
install(TARGETS MultiAgentExperience-ThreadExecutor
    EXPORT MultiAgentExperience-ThreadExecutorTargets
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

#build directory export
install(EXPORT MultiAgentExperience-ThreadExecutorTargets
    FILE MultiAgentExperience-ThreadExecutorTargets.cmake
    NAMESPACE MAX::
    DESTINATION cmake
)

install(DIRECTORY include/ DESTINATION include/)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-ThreadExecutorConfig.cmake"
    INSTALL_DESTINATION cmake
)

# generate the version file for the config file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-ThreadExecutorConfigVersion.cmake"
    VERSION "${MultiAgentExperience-ThreadExecutor_VERSION_MAJOR}.${MultiAgentExperience-ThreadExecutor_VERSION_MINOR}"
    COMPATIBILITY AnyNewerVersion
)


install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-ThreadExecutorConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-ThreadExecutorConfigVersion.cmake"
    DESTINATION cmake
)

export(EXPORT MultiAgentExperience-ThreadExecutorTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-ThreadExecutorTargets.cmake"
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
