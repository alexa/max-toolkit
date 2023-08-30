include(CMakePackageConfigHelpers)

#install targets
install(TARGETS MultiAgentExperience-CommandLine-Orchestrator
    EXPORT MultiAgentExperience-CommandLine-OrchestratorTargets
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

#build directory export
install(EXPORT MultiAgentExperience-CommandLine-OrchestratorTargets
    FILE MultiAgentExperience-CommandLine-OrchestratorTargets.cmake
    NAMESPACE MAX::
    DESTINATION cmake
)

install(DIRECTORY include/ DESTINATION include/MultiAgentExperience-CommandLine-Orchestrator)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-CommandLine-OrchestratorConfig.cmake"
    INSTALL_DESTINATION cmake
)

# generate the version file for the config file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-CommandLine-OrchestratorConfigVersion.cmake"
    VERSION "${MultiAgentExperience-CommandLine-Orchestrator_VERSION_MAJOR}.${MultiAgentExperience-CommandLine-Orchestrator_VERSION_MINOR}"
    COMPATIBILITY AnyNewerVersion
)


install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-CommandLine-OrchestratorConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-CommandLine-OrchestratorConfigVersion.cmake"
    DESTINATION cmake
)

export(EXPORT MultiAgentExperience-CommandLine-OrchestratorTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-CommandLine-OrchestratorTargets.cmake"
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
