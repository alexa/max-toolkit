cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(MultiAgentExperience-Logger VERSION 1.3.0 LANGUAGES CXX)
include(CTest)

find_package(MultiAgentExperience-API REQUIRED)

add_library(MultiAgentExperience-Logger SHARED)

# add custom empty target with dependency on MultiAgentExperience-Library
# this enables 'make dev' to only build the library, even when BUILD_TESTS=ON
add_custom_target(dev)
add_dependencies(dev MultiAgentExperience-Logger)

set_target_properties(MultiAgentExperience-Logger
        PROPERTIES VERSION
        "${MultiAgentExperience-Logger_VERSION_MAJOR}.${MultiAgentExperience-Logger_VERSION_MINOR}")

# Set up the compiler flags.
target_compile_features(MultiAgentExperience-Logger PUBLIC cxx_std_11)
set_target_properties(MultiAgentExperience-Logger PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(MultiAgentExperience-Logger PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON)

# Set include directories
# The generator expressions evaluate to include or "" depending on whether or not we are currently building
# or installing. This way we never have to rely on relative path expansion (which isn't supported)
target_include_directories(MultiAgentExperience-Logger PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${MultiAgentExperience-Logger_SOURCE_DIR}/include>
        )

target_link_libraries(MultiAgentExperience-Logger PRIVATE MAX::MultiAgentExperience-API)

target_include_directories(MultiAgentExperience-Logger PRIVATE include)

add_subdirectory(src)

include(cmake/Install.cmake)
