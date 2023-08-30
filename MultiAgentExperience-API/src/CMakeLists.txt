add_library(MultiAgentExperience-API INTERFACE)
include(GNUInstallDirs)
message(${CMAKE_INSTALL_INCLUDEDIR})
target_include_directories(MultiAgentExperience-API
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

        
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-APIConfigVersion.cmake"
    VERSION "${MultiAgentExperience-API_VERSION_MAJOR}.${MultiAgentExperience-API_VERSION_MINOR}"
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-APIConfig.cmake"
    INSTALL_DESTINATION cmake
)
          
install(TARGETS MultiAgentExperience-API
    EXPORT MultiAgentExperience-API
)
install(
    TARGETS MultiAgentExperience-API
    EXPORT MultiAgentExperience-API_Targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(
    EXPORT MultiAgentExperience-API_Targets
    FILE MultiAgentExperience-APITargets.cmake
    NAMESPACE MAX::
    DESTINATION cmake)

install(DIRECTORY . DESTINATION include/MultiAgentExperience)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-APIConfig.cmake"
              "${CMAKE_CURRENT_BINARY_DIR}/MultiAgentExperience-APIConfigVersion.cmake"
        DESTINATION cmake)
include(CPack)
