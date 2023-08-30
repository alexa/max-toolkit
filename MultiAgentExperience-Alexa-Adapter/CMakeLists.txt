cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# Check that the SDK meets the minimum version requirement to be used with this adapter.
set(AVS_DEVICE_SDK_MIN_VER "1.26.0")
set(MAX_API_MIN_VER "0.6.0")

project(MultiAgentExperience-Alexa-Adapter VERSION 0.5.0 LANGUAGES CXX)

include(${AVS_CMAKE_BUILD}/BuildDefaults.cmake)

add_library(MultiAgentExperience-Alexa-Adapter SHARED)
set_target_properties(MultiAgentExperience-Alexa-Adapter
        PROPERTIES VERSION
        "${MultiAgentExperience-Alexa-Adapter_VERSION_MAJOR}.${MultiAgentExperience-Alexa-Adapter_VERSION_MINOR}"
        )

# Set up the compiler flags.
target_compile_features(MultiAgentExperience-Alexa-Adapter PUBLIC cxx_std_11)
set_target_properties(MultiAgentExperience-Alexa-Adapter PROPERTIES CXX_EXTENSIONS OFF)
set_target_properties(MultiAgentExperience-Alexa-Adapter PROPERTIES CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(MultiAgentExperience-Alexa-Adapter PRIVATE include)

find_package(MultiAgentExperience-API REQUIRED)
target_link_libraries(MultiAgentExperience-Alexa-Adapter PUBLIC
        MAX::MultiAgentExperience-API
        AVSCommon)

add_subdirectory(src)

# Set include directories
# The generator expressions evaluate to include or "" depending on whether or not we are currently building
# or installing. This way we never have to rely on relative path expansion (which isn't supported)
target_include_directories(MultiAgentExperience-Alexa-Adapter PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${MultiAgentExperience-Alexa-Adapter_SOURCE_DIR}/include>
        )

# install target
asdk_install()