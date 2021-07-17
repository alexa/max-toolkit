include(CMakePackageConfigHelpers)

#install targets
install(TARGETS ComputerAgent
    EXPORT ComputerAgentTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    INCLUDES DESTINATION include
)

install(DIRECTORY include/
    DESTINATION include
)

#build directory export
install(EXPORT ComputerAgentTargets
    FILE ComputerAgentTargets.cmake
    NAMESPACE MAX::
    DESTINATION lib/cmake
)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake.in
    "${CMAKE_CURRENT_BINARY_DIR}/ComputerAgentConfig.cmake"
    INSTALL_DESTINATION lib/cmake
)

# generate the version file for the config file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/ComputerAgentConfigVersion.cmake"
    VERSION "${ComputerAgent_VERSION_MAJOR}.${ComputerAgent_VERSION_MINOR}"
    COMPATIBILITY AnyNewerVersion
)


install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/ComputerAgentConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/ComputerAgentConfigVersion.cmake"
    DESTINATION lib/cmake
)

export(EXPORT ComputerAgentTargets
    FILE "${CMAKE_CURRENT_BINARY_DIR}/ComputerAgentTargets.cmake"
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
