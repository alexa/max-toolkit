include(CMakePackageConfigHelpers)

#install targets
install(TARGETS MultiAgentExperience-Logger
        EXPORT MultiAgentExperience-LoggerTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
        )

install(DIRECTORY include/
        DESTINATION include/MultiAgentExperience/Utils/Logger
        )

# build directory export
install(EXPORT MultiAgentExperience-LoggerTargets
        FILE MultiAgentExperience-LoggerTargets.cmake
        NAMESPACE MAX::
        DESTINATION cmake
        )

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-LoggerConfig.cmake"
        INSTALL_DESTINATION cmake
        )

# generate the version file for the config file
write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-LoggerConfigVersion.cmake"
        VERSION "${MultiAgentExperience-Logger_VERSION_MAJOR}.${MultiAgentExperience-Logger_VERSION_MINOR}"
        COMPATIBILITY AnyNewerVersion
)


install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-LoggerConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-LoggerConfigVersion.cmake"
        DESTINATION cmake
        )

export(EXPORT MultiAgentExperience-LoggerTargets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-LoggerTargets.cmake"
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