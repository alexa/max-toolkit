cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(MultiAgentExperience-ThreadExecutorMultiAgentExperience-ThreadExecutor VERSION 2.0 LANGUAGES CXX)
add_library(MultiAgentExperience-ThreadExecutor SHARED)

# add custom empty target with dependancy on MultiAgentExperience-Library
# this enables 'make dev' to only build the library, even when BUILD_TESTS=ON
add_custom_target(dev)
add_dependencies(dev MultiAgentExperience-ThreadExecutor)

set_target_properties(MultiAgentExperience-ThreadExecutor
        PROPERTIES VERSION
        "${MultiAgentExperience-ThreadExecutor_VERSION_MAJOR}.${MultiAgentExperience-ThreadExecutor_VERSION_MINOR}"
        )

# Set up the compiler flags.
target_compile_features(MultiAgentExperience-ThreadExecutor PUBLIC cxx_std_14)
set_target_properties(MultiAgentExperience-ThreadExecutor PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(MultiAgentExperience-ThreadExecutor PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(MultiAgentExperience-ThreadExecutor PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${MultiAgentExperience-ThreadExecutor_SOURCE_DIR}/include>
        )

target_include_directories(MultiAgentExperience-ThreadExecutor PRIVATE include)
add_subdirectory(src)

include(cmake/Install.cmake)



