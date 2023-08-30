include(CMakePackageConfigHelpers)

#install targets
install(TARGETS MultiAgentExperience-Integration-App
    EXPORT MultiAgentExperience-Integration-AppTargets
    RUNTIME DESTINATION bin
)

#build directory export
install(EXPORT MultiAgentExperience-Integration-AppTargets
    FILE MultiAgentExperience-Integration-AppTargets.cmake
    NAMESPACE MAX::
    DESTINATION cmake
)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-Integration-AppConfig.cmake"
    INSTALL_DESTINATION cmake
)

# generate the version file for the config file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-Integration-AppConfigVersion.cmake"
    VERSION "${MultiAgentExperience-Integration-App_VERSION_MAJOR}.${MultiAgentExperience-Integration-App_VERSION_MINOR}"
    COMPATIBILITY AnyNewerVersion
)


install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-Integration-AppConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-Integration-AppConfigVersion.cmake"
    DESTINATION cmake
)

export(EXPORT MultiAgentExperience-Integration-AppTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-Integration-AppTargets.cmake"
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
