#!/bin/bash

# Exit on error.
set -e

SCRIPT_NAME=$(basename "$0")

# Define color codes for the log statements
COLOR_GREEN="\033[32;1m"
COLOR_RED="\033[1;31m"
COLOR_RESET="\033[0m"

print () {
    echo -e "$(date +"%Y-%m-%d %T") [$SCRIPT_NAME]: $1"
}

announce_success () {
   echo -e "${COLOR_GREEN}$(date +"%Y-%m-%d %T") [$SCRIPT_NAME]:
################################################################################################
      $1
################################################################################################
   ${COLOR_RESET}"
}

announce_failure () {
    echo -e "${COLOR_RED}$(date +"%Y-%m-%d %T") [$SCRIPT_NAME]: $1 ${COLOR_RESET}"
}

# Find the path of the CMake binary on the host system (MacOS or Linux)
CMAKE_BINARY_INSTALL_PATH=$(which cmake)
if [ -z "$CMAKE_BINARY_INSTALL_PATH" ]; then
    announce_failure "\"cmake\" binary not found on system. Exiting..."
    exit 1
else
    print "\"cmake\" found at $CMAKE_BINARY_INSTALL_PATH. Proceeding..."
fi

# Fetch the path of the current working directory i.e. the directory that houses this script
CURRENT_WORKING_DIRECTORY=$(pwd)
print "Current working directory is : $CURRENT_WORKING_DIRECTORY"

# Get the path of the parent directory (one level up) which houses all the relevant packages for successfully building MAX library
MAX_ARTIFACTS_DIR=$(dirname "$CURRENT_WORKING_DIRECTORY")
print "MAX artifact directory is : $MAX_ARTIFACTS_DIR"

# Set the build and install directories 
MAX_BUILD_DIR="$MAX_ARTIFACTS_DIR/build"
MAX_INSTALL_DIR="$MAX_ARTIFACTS_DIR/install"
MAKE_THREADS_NUM=1

if [[ "$OSTYPE" == "darwin"* ]]; then
    MAKE_THREADS_NUM=`sysctl -n hw.ncpu`
else
    MAKE_THREADS_NUM=`nproc`
fi

print "Number of processing units available : $MAKE_THREADS_NUM"

################################################################################################################################
############################################ MultiAgentExperience-API Build ####################################################
################################################################################################################################
PATH_TO_MAX_API_BUILD=${MAX_BUILD_DIR}/MultiAgentExperience-API
print "Path to MultiAgentExperience-API build directory is : $PATH_TO_MAX_API_BUILD"

PATH_TO_MAX_API_SOURCE=${MAX_ARTIFACTS_DIR}/MultiAgentExperience-API
print "Path to MultiAgentExperience-API source directory is : $PATH_TO_MAX_API_SOURCE"

PATH_TO_MAX_API_INSTALL=${MAX_INSTALL_DIR}/MultiAgentExperience-API
print "Path to MultiAgentExperience-API install directory is : $PATH_TO_MAX_API_INSTALL"

mkdir -p $PATH_TO_MAX_API_BUILD
mkdir -p $PATH_TO_MAX_API_INSTALL

cd $PATH_TO_MAX_API_BUILD

print "Building MultiAgentExperience-API in $PATH_TO_MAX_API_BUILD"
cmake -DCMAKE_INSTALL_PREFIX=$PATH_TO_MAX_API_INSTALL $PATH_TO_MAX_API_SOURCE

print "Installing MultiAgentExperience-API in $PATH_TO_MAX_API_INSTALL"
make -j $MAKE_THREADS_NUM install
announce_success "MultiAgentExperience-API successfully installed!"
################################################################################################################################
################################################################################################################################
################################################################################################################################


################################################################################################################################
############################################ MultiAgentExperience-Logger Build #################################################
################################################################################################################################
PATH_TO_MAX_LOGGER_BUILD=${MAX_BUILD_DIR}/MultiAgentExperience-Logger
print "Path to MultiAgentExperience-Logger build directory is : $PATH_TO_MAX_LOGGER_BUILD"

PATH_TO_MAX_LOGGER_SOURCE=${MAX_ARTIFACTS_DIR}/MultiAgentExperience-Logger
print "Path to MultiAgentExperience-Logger source directory is : $PATH_TO_MAX_LOGGER_SOURCE"

PATH_TO_MAX_LOGGER_INSTALL=${MAX_INSTALL_DIR}/MultiAgentExperience-Logger
print "Path to MultiAgentExperience-Logger install directory is : $PATH_TO_MAX_LOGGER_INSTALL"

mkdir -p $PATH_TO_MAX_LOGGER_BUILD
mkdir -p $PATH_TO_MAX_LOGGER_INSTALL

cd $PATH_TO_MAX_LOGGER_BUILD

print "Building MultiAgentExperience-Logger in $PATH_TO_MAX_LOGGER_BUILD"
cmake \
        -DCMAKE_INSTALL_PREFIX=$PATH_TO_MAX_LOGGER_INSTALL $PATH_TO_MAX_LOGGER_SOURCE \
        -DMultiAgentExperience-API_DIR=$PATH_TO_MAX_API_INSTALL/cmake

print "Installing MultiAgentExperience-Logger in $PATH_TO_MAX_LOGGER_INSTALL"
make -j $MAKE_THREADS_NUM install
announce_success "MultiAgentExperience-Logger successfully installed!"
################################################################################################################################
################################################################################################################################
################################################################################################################################


################################################################################################################################
############################################ MultiAgentExperience Library Build ################################################
################################################################################################################################
PATH_TO_MAX_LIB_BUILD=${MAX_BUILD_DIR}/MultiAgentExperience
print "Path to MultiAgentExperience build directory is : $PATH_TO_MAX_LIB_BUILD"

PATH_TO_MAX_LIB_SOURCE=${MAX_ARTIFACTS_DIR}/MultiAgentExperience
print "Path to MultiAgentExperience source directory is : $PATH_TO_MAX_LIB_SOURCE"

PATH_TO_MAX_LIB_INSTALL=${MAX_INSTALL_DIR}/MultiAgentExperience
print "Path to MultiAgentExperience install directory is : $PATH_TO_MAX_LIB_INSTALL"

mkdir -p $PATH_TO_MAX_LIB_BUILD
mkdir -p $PATH_TO_MAX_LIB_INSTALL

cd $PATH_TO_MAX_LIB_BUILD

print "Building MultiAgentExperience in $PATH_TO_MAX_LIB_BUILD"
cmake \
        -DCMAKE_INSTALL_PREFIX=$PATH_TO_MAX_LIB_INSTALL \
        -DMultiAgentExperience-Logger_DIR=$PATH_TO_MAX_LOGGER_INSTALL/cmake \
        -DMultiAgentExperience-API_DIR=$PATH_TO_MAX_API_INSTALL/cmake \
        $PATH_TO_MAX_LIB_SOURCE

print "Installing MultiAgentExperience library artifacts in $PATH_TO_MAX_LIB_INSTALL"
make -j $MAKE_THREADS_NUM install
announce_success "MultiAgentExperience Library successfully installed!"
################################################################################################################################
################################################################################################################################
################################################################################################################################


################################################################################################################################
############################################ AVS SDK Patch & Adapter Build #####################################################
################################################################################################################################
AVS_SDK_BASE_DIR=${MAX_ARTIFACTS_DIR}/AVS-SDK
PATH_TO_ADAPTER_SOURCE=${MAX_ARTIFACTS_DIR}/MultiAgentExperience-Alexa-Adapter
PATH_TO_AVS_SDK_BUILD=${MAX_BUILD_DIR}/AVS-SDK
PATH_TO_AVS_SDK_SOURCE=${AVS_SDK_BASE_DIR}/avs-device-sdk
PATH_TO_AVS_SDK_INSTALL=${MAX_INSTALL_DIR}/AVS-SDK

# Check if the required files/directories exist and are exported to the right environment variables
if [ ! -f "$PORTAUDIO_LIB_PATH" ]; then
    announce_failure "Error: The PORTAUDIO_LIB_PATH environment variable is not set, or is incorrect. Please export the correct path."
    exit 1
fi
if [ ! -d "$PORTAUDIO_INCLUDE_DIR" ]; then
    announce_failure "Error: The PORTAUDIO_INCLUDE_DIR environment variable is not set, or is incorrect. Please export the correct path."
    exit 1
fi
if [ ! -f "$CURL_LIBRARY_PATH" ]; then
    announce_failure "Error: The CURL_LIBRARY_PATH environment variable is not set, or is incorrect. Please export the correct path."
    exit 1
fi
if [ ! -d "$CURL_INCLUDE_DIR" ]; then
    announce_failure "Error: The CURL_INCLUDE_DIR environment variable is not set, or is incorrect. Please export the correct path."
    exit 1
fi

# Check if an "avs-device-sdk" directory is present. If not present, we will clone and apply the patch. If present, we don't want to re-clone.
if [ ! -d "$PATH_TO_AVS_SDK_SOURCE" ]; then
    print "Directory $PATH_TO_AVS_SDK_SOURCE doesn't exist. Creating..."

    cd $AVS_SDK_BASE_DIR

    print "Cloning AVS SDK v1.26.0 into $AVS_SDK_BASE_DIR"
    git clone  --single-branch --branch v1.26.0 https://github.com/alexa/avs-device-sdk.git

    cd avs-device-sdk

    git apply ${AVS_SDK_BASE_DIR}/avs-device-sdk-with-max-1.3.patch
    announce_success "Successfully applied the MultiAgentExperience Library Compatibility patch to AVS SDK v1.26.0"

else
    announce_failure "Directory $PATH_TO_AVS_SDK_SOURCE already exists. Assuming that AVS SDK v1.26.0 is cloned and that the MultiAgentExperience Library Compatibility patch is already applied."
fi

print "Building AVS SDK"

mkdir -p $PATH_TO_AVS_SDK_BUILD
mkdir -p $PATH_TO_AVS_SDK_INSTALL
cd $PATH_TO_AVS_SDK_BUILD

AVS_SDK_CMAKE_FLAGS=(
    "-DCMAKE_INSTALL_PREFIX=$PATH_TO_AVS_SDK_INSTALL"
    "-DGSTREAMER_MEDIA_PLAYER=ON"
    "-DPORTAUDIO=ON"
    "-DPKCS11=OFF"
    "-DPORTAUDIO_LIB_PATH=$PORTAUDIO_LIB_PATH"
    "-DPORTAUDIO_INCLUDE_DIR=$PORTAUDIO_INCLUDE_DIR"
    "-DCURL_LIBRARY=$CURL_LIBRARY_PATH"
    "-DCURL_INCLUDE_DIR=$CURL_INCLUDE_DIR"
    "-DCMAKE_BUILD_TYPE=DEBUG"
    "-DMULTI_AGENT_EXPERIENCE_ENABLED=ON"
    "-DMultiAgentExperience-API_DIR=$PATH_TO_MAX_API_INSTALL/cmake"
    "-DEXTENSION_PATHS=$PATH_TO_ADAPTER_SOURCE"
)

cmake $PATH_TO_AVS_SDK_SOURCE "${AVS_SDK_CMAKE_FLAGS[@]}"

make -j $MAKE_THREADS_NUM install
announce_success "AVS SDK successfully installed!"
################################################################################################################################
################################################################################################################################
################################################################################################################################


################################################################################################################################
#################################### MultiAgentExperience-CommandLine-Orchestrator Build #######################################
################################################################################################################################
PATH_TO_MAX_CLO_BUILD=${MAX_BUILD_DIR}/MultiAgentExperience-CommandLine-Orchestrator
print "Path to MultiAgentExperience-CommandLine-Orchestrator build directory is : $PATH_TO_MAX_CLO_BUILD"

PATH_TO_MAX_CLO_SOURCE=${MAX_ARTIFACTS_DIR}/SampleApp/MultiAgentExperience-CommandLine-Orchestrator
print "Path to MultiAgentExperience-CommandLine-Orchestrator source directory is : $PATH_TO_MAX_CLO_SOURCE"

PATH_TO_MAX_CLO_INSTALL=${MAX_INSTALL_DIR}/MultiAgentExperience-CommandLine-Orchestrator
print "Path to MultiAgentExperience-CommandLine-Orchestrator install directory is : $PATH_TO_MAX_CLO_INSTALL"

mkdir -p $PATH_TO_MAX_CLO_BUILD
mkdir -p $PATH_TO_MAX_CLO_INSTALL

cd $PATH_TO_MAX_CLO_BUILD

print "Building MultiAgentExperience-CommandLine-Orchestrator in $PATH_TO_MAX_CLO_BUILD"
cmake \
        -DCMAKE_INSTALL_PREFIX=$PATH_TO_MAX_CLO_INSTALL $PATH_TO_MAX_CLO_SOURCE

print "Installing MultiAgentExperience-CommandLine-Orchestrator in $PATH_TO_MAX_CLO_INSTALL"
make -j $MAKE_THREADS_NUM install
announce_success "MultiAgentExperience-CommandLine-Orchestrator successfully installed!"
################################################################################################################################
################################################################################################################################
################################################################################################################################


################################################################################################################################
######################################## MultiAgentExperience-Integration-App Build ############################################
################################################################################################################################
PATH_TO_MAX_IA_BUILD=${MAX_BUILD_DIR}/MultiAgentExperience-Integration-App
print "Path to MultiAgentExperience-Integration-App build directory is : $PATH_TO_MAX_IA_BUILD"

PATH_TO_MAX_IA_SOURCE=${MAX_ARTIFACTS_DIR}/SampleApp/MultiAgentExperience-Integration-App
print "Path to MultiAgentExperience-Integration-App source directory is : $PATH_TO_MAX_IA_SOURCE"

PATH_TO_MAX_IA_INSTALL=${MAX_INSTALL_DIR}/MultiAgentExperience-Integration-App
print "Path to MultiAgentExperience-Integration-App install directory is : $PATH_TO_MAX_IA_INSTALL"

mkdir -p $PATH_TO_MAX_IA_BUILD
mkdir -p $PATH_TO_MAX_IA_INSTALL

cd $PATH_TO_MAX_IA_BUILD

print "Building MultiAgentExperience-Integration-App in $PATH_TO_MAX_IA_BUILD"

# The pkg-config path needs to be updated with the AVS SDK pkg-config path. The AVS SDK is discovered by the Integration-App in this manner.
AVS_SDK_PKG_CONFIG_PATH="$PATH_TO_AVS_SDK_BUILD"
export PKG_CONFIG_PATH=$AVS_SDK_PKG_CONFIG_PATH:$PKG_CONFIG_PATH

cmake \
        -DCMAKE_INSTALL_PREFIX=$PATH_TO_MAX_IA_INSTALL \
        -DMULTI_AGENT_EXPERIENCE=ON \
        -DMULTI_AGENT_EXPERIENCE_ENABLED=ON \
        -DMultiAgentExperience-API_DIR=$PATH_TO_MAX_API_INSTALL/cmake \
        -DMultiAgentExperience-Logger_DIR=$PATH_TO_MAX_LOGGER_INSTALL/cmake \
        -DMultiAgentExperience_DIR=$PATH_TO_MAX_LIB_INSTALL/cmake \
        -DMultiAgentExperience-CommandLine-Orchestrator_DIR=$PATH_TO_MAX_CLO_INSTALL/cmake \
        $PATH_TO_MAX_IA_SOURCE

print "Installing MultiAgentExperience-Integration-App in $PATH_TO_MAX_IA_INSTALL"
make -j $MAKE_THREADS_NUM install
announce_success "MultiAgentExperience-Integration-App successfully installed!"
################################################################################################################################
################################################################################################################################
################################################################################################################################


CUSTOM_LD_LIBRARY_PATH="$PATH_TO_MAX_LIB_INSTALL/lib:$PATH_TO_MAX_LOGGER_INSTALL/lib:$PATH_TO_MAX_CLO_INSTALL/lib:$PATH_TO_AVS_SDK_INSTALL/lib"

print "Run the below command, for the IntegrationApp to find the libraries installed. You can add the export command to your ~/.zshrc or ~/.bashrc too."
print "
    Linux:
        ${COLOR_GREEN}export LD_LIBRARY_PATH=\$LD_LIBRARY_PATH:$CUSTOM_LD_LIBRARY_PATH${COLOR_RESET}

    MacOS:
        ${COLOR_GREEN}export DYLD_LIBRARY_PATH=\$DYLD_LIBRARY_PATH:$CUSTOM_LD_LIBRARY_PATH${COLOR_RESET}"

# ASCII ART TEXT, Font - ANSI Regular
print "${COLOR_GREEN}
################################################################################################################################
################################################################################################################################
################################################################################################################################

                        ███    ███  █████  ██   ██             ██    ██  ██    ██████      ██████              
                        ████  ████ ██   ██  ██ ██              ██    ██ ███         ██    ██  ████             
                        ██ ████ ██ ███████   ███               ██    ██  ██     █████     ██ ██ ██             
                        ██  ██  ██ ██   ██  ██ ██               ██  ██   ██         ██    ████  ██             
                        ██      ██ ██   ██ ██   ██               ████    ██ ██ ██████  ██  ██████              


                        ██ ███    ██ ███████ ████████  █████  ██      ██      ███████ ██████  ██               
                        ██ ████   ██ ██         ██    ██   ██ ██      ██      ██      ██   ██ ██               
                        ██ ██ ██  ██ ███████    ██    ███████ ██      ██      █████   ██   ██ ██               
                        ██ ██  ██ ██      ██    ██    ██   ██ ██      ██      ██      ██   ██                  
                        ██ ██   ████ ███████    ██    ██   ██ ███████ ███████ ███████ ██████  ██ 

################################################################################################################################
################################################################################################################################
################################################################################################################################
${COLOR_RESET}"

print "Run the IntegrationApp in the install/MultiAgentExperience-Integration-App/bin/ directory using: 
    ${COLOR_GREEN} GST_PLUGIN_PATH=/opt/homebrew/lib/gstreamer-1.0 ./MultiAgentExperience-Integration-App <path>/<to>/AlexaClientSDKConfig.json ${COLOR_RESET}"