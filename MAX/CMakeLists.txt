cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(MultiAgentExperience VERSION 0.4.0 LANGUAGES CXX)

include(cmake/Testing.cmake)

add_subdirectory(thirdparty)

add_library(MultiAgentExperience SHARED)

# add custom empty target with dependancy on MultiAgentExperience
# this enables 'make dev' to only build the library, even when BUILD_TESTS=ON
add_custom_target(dev)
add_dependencies(dev MultiAgentExperience)

set_target_properties(MultiAgentExperience
    PROPERTIES VERSION
    "${MultiAgentExperience_VERSION_MAJOR}.${MultiAgentExperience_VERSION_MINOR}"
)

# Set up the compiler flags.
target_compile_features(MultiAgentExperience PUBLIC cxx_std_11)
set_target_properties(MultiAgentExperience PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(MultiAgentExperience PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON)

# Set include directories
# The generator expressions evaluate to include or "" depending on whether or not we are currently building
# or installing. This way we never have to rely on relative path expansion (which isn't supported)
target_include_directories(MultiAgentExperience PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${MultiAgentExperience_SOURCE_DIR}/include>
)

add_subdirectory(library)

include(cmake/Install.cmake)
