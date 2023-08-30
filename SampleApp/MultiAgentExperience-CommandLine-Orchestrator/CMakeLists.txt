cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(MultiAgentExperience-CommandLine-Orchestrator VERSION 1.3 LANGUAGES CXX)
add_library(MultiAgentExperience-CommandLine-Orchestrator SHARED)

target_sources(
        MultiAgentExperience-CommandLine-Orchestrator
        PRIVATE
        src/Orchestrator.cpp)

# add custom empty target with dependancy on MultiAgentExperience-Library
# this enables 'make dev' to only build the library, even when BUILD_TESTS=ON
add_custom_target(dev)
add_dependencies(dev MultiAgentExperience-CommandLine-Orchestrator)

set_target_properties(MultiAgentExperience-CommandLine-Orchestrator
        PROPERTIES VERSION
        "${MultiAgentExperience-CommandLine-Orchestrator_VERSION_MAJOR}.${MultiAgentExperience-CommandLine-Orchestrator_VERSION_MINOR}"
        )

# Set up the compiler flags.
target_compile_features(MultiAgentExperience-CommandLine-Orchestrator PUBLIC cxx_std_14)
set_target_properties(MultiAgentExperience-CommandLine-Orchestrator PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(MultiAgentExperience-CommandLine-Orchestrator PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(MultiAgentExperience-CommandLine-Orchestrator PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${MultiAgentExperience-CommandLine-Orchestrator_SOURCE_DIR}/include>
        )

find_package(cli)
target_link_libraries(MultiAgentExperience-CommandLine-Orchestrator PRIVATE cli::cli)

target_include_directories(MultiAgentExperience-CommandLine-Orchestrator PRIVATE include)
add_subdirectory(src)

include(cmake/Install.cmake)




