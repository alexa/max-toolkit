# Install script for directory: /local/home/aneeshpb/GitHubRelease1.3/MaxToolkitWs/src/MultiAgentExperience/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/aneeshpb/GitHubRelease1.3/MaxToolkitWs/build/MultiAgentExperience/MultiAgentExperience-1.3/AL2_x86_64/DEV.STD.PTHREAD/build/private/arnold-workspace/arnold-build/MultiAgentExperience/1.3/alexa/stable/package/539ea8c59b56084491a07dff60b864c7848c2d55")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/aneeshpb/GitHubRelease1.3/MaxToolkitWs/build/MultiAgentExperience/MultiAgentExperience-1.3/AL2_x86_64/DEV.STD.PTHREAD/build/private/arnold-workspace/arnold-build/MultiAgentExperience/1.3/alexa/stable/builds/539ea8c59b56084491a07dff60b864c7848c2d55/src/Control/cmake_install.cmake")
  include("/home/aneeshpb/GitHubRelease1.3/MaxToolkitWs/build/MultiAgentExperience/MultiAgentExperience-1.3/AL2_x86_64/DEV.STD.PTHREAD/build/private/arnold-workspace/arnold-build/MultiAgentExperience/1.3/alexa/stable/builds/539ea8c59b56084491a07dff60b864c7848c2d55/src/Activity/cmake_install.cmake")
  include("/home/aneeshpb/GitHubRelease1.3/MaxToolkitWs/build/MultiAgentExperience/MultiAgentExperience-1.3/AL2_x86_64/DEV.STD.PTHREAD/build/private/arnold-workspace/arnold-build/MultiAgentExperience/1.3/alexa/stable/builds/539ea8c59b56084491a07dff60b864c7848c2d55/src/Application/cmake_install.cmake")
  include("/home/aneeshpb/GitHubRelease1.3/MaxToolkitWs/build/MultiAgentExperience/MultiAgentExperience-1.3/AL2_x86_64/DEV.STD.PTHREAD/build/private/arnold-workspace/arnold-build/MultiAgentExperience/1.3/alexa/stable/builds/539ea8c59b56084491a07dff60b864c7848c2d55/src/Common/cmake_install.cmake")
  include("/home/aneeshpb/GitHubRelease1.3/MaxToolkitWs/build/MultiAgentExperience/MultiAgentExperience-1.3/AL2_x86_64/DEV.STD.PTHREAD/build/private/arnold-workspace/arnold-build/MultiAgentExperience/1.3/alexa/stable/builds/539ea8c59b56084491a07dff60b864c7848c2d55/src/Core/cmake_install.cmake")
  include("/home/aneeshpb/GitHubRelease1.3/MaxToolkitWs/build/MultiAgentExperience/MultiAgentExperience-1.3/AL2_x86_64/DEV.STD.PTHREAD/build/private/arnold-workspace/arnold-build/MultiAgentExperience/1.3/alexa/stable/builds/539ea8c59b56084491a07dff60b864c7848c2d55/src/Device/cmake_install.cmake")
  include("/home/aneeshpb/GitHubRelease1.3/MaxToolkitWs/build/MultiAgentExperience/MultiAgentExperience-1.3/AL2_x86_64/DEV.STD.PTHREAD/build/private/arnold-workspace/arnold-build/MultiAgentExperience/1.3/alexa/stable/builds/539ea8c59b56084491a07dff60b864c7848c2d55/src/Dialog/cmake_install.cmake")
  include("/home/aneeshpb/GitHubRelease1.3/MaxToolkitWs/build/MultiAgentExperience/MultiAgentExperience-1.3/AL2_x86_64/DEV.STD.PTHREAD/build/private/arnold-workspace/arnold-build/MultiAgentExperience/1.3/alexa/stable/builds/539ea8c59b56084491a07dff60b864c7848c2d55/src/Experience/cmake_install.cmake")
  include("/home/aneeshpb/GitHubRelease1.3/MaxToolkitWs/build/MultiAgentExperience/MultiAgentExperience-1.3/AL2_x86_64/DEV.STD.PTHREAD/build/private/arnold-workspace/arnold-build/MultiAgentExperience/1.3/alexa/stable/builds/539ea8c59b56084491a07dff60b864c7848c2d55/src/Utils/cmake_install.cmake")

endif()

