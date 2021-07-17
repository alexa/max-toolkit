cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(ComputerAgent VERSION 0.4.0 LANGUAGES CXX)

# Use shared libraries, which is the default for the AWS C++ SDK build.
option(BUILD_SHARED_LIBS "Build shared libraries" ON)

# Fix for OSX platforms. Details: https://gitlab.kitware.com/cmake/cmake/-/issues/19120
if (APPLE)
    link_directories(/usr/local/lib)
endif()

add_library(ComputerAgent SHARED)

add_custom_target(dev)
add_dependencies(dev ComputerAgent)

set_target_properties(ComputerAgent
    PROPERTIES VERSION
    "${ComputerAgent_VERSION_MAJOR}.${ComputerAgent_VERSION_MINOR}"
)

find_package(PkgConfig)

pkg_check_modules(GST REQUIRED gstreamer-1.0>=1.8 gstreamer-app-1.0>=1.8 gstreamer-controller-1.0>=1.8)

find_package(MultiAgentExperience 0.4 REQUIRED)
target_link_libraries(ComputerAgent PUBLIC MAX::MultiAgentExperience)

find_package(AWSSDK REQUIRED COMPONENTS lex identity-management)
target_link_libraries(ComputerAgent PUBLIC
    ${AWSSDK_LINK_LIBRARIES}
    AVSCommon
    AIP
    "${GST_LDFLAGS}"
)

target_compile_features(ComputerAgent PUBLIC cxx_std_11)
set_target_properties(ComputerAgent PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(ComputerAgent PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(ComputerAgent PUBLIC
    "${GST_INCLUDE_DIRS}"
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${ComputerAgent_SOURCE_DIR}/include>
)

add_subdirectory(src)

# Fix for OSX platforms. Details: https://gitlab.kitware.com/cmake/cmake/-/issues/19120
if (APPLE)
    target_include_directories(ComputerAgent PUBLIC /usr/local/include)
endif()

include(cmake/Install.cmake)
