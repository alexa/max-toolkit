cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

project(MultiAgentExperience VERSION 1.3.0 LANGUAGES CXX)

include(CTest)

find_package(MultiAgentExperience-API REQUIRED)
find_package(MultiAgentExperience-Logger REQUIRED)

add_library(MultiAgentExperience SHARED)

# add custom empty target with dependency on MultiAgentExperience-Library
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

target_link_libraries(MultiAgentExperience PUBLIC MAX::MultiAgentExperience-API)
target_link_libraries(MultiAgentExperience PUBLIC MAX::MultiAgentExperience-Logger)

target_include_directories(MultiAgentExperience PRIVATE include)
add_subdirectory(src)
if(MAX_BUILD_TESTS)
    find_package(GTest REQUIRED)
    include(cmake/GoogleTest.cmake)
    add_subdirectory(test)
endif()

include(cmake/Install.cmake)
