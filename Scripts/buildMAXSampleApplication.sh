#!/bin/bash

set -e

print_usage() {
  echo "
  Usage: ./buildMAXSampleApplication.sh [options] <path to max toolkit installation directory>

  Note:
      * If you want to perform a clean build of the MAX Sample Application, please make sure that
        the MAX ToolKit installation directory specified is empty before running this script.

  Options:
    -s (Raspberry Pi Only) Enables Kitt.AI Snowboy wakeword engine in the MAX Sample Application
    -l (Raspberry Pi Only) Enables RaspberryPi SenseHAT LED experience rendering (https://www.raspberrypi.org/products/sense-hat/)
        This option requires that you download the SenseHAT LED animation files from the Alexa Developer Portal
  "
}

COLOR_GREEN="\x1b[32;01m"
COLOR_RED="\x1b[31;01m"
COLOR_RESET="\x1b[39;49;00m"

announce_success () {
   echo -e $COLOR_GREEN"
################################################################################################
# $1
################################################################################################
   " $COLOR_RESET
}

announce_failure () {
   echo -e $COLOR_RED"$1"$COLOR_RESET
}

INSTALL_DIR=''
LEDS_ENABLED=false
SNOWBOY_ENABLED=false
MAKE_THREADS_NUM=`nproc`

# Read flags
while getopts 'i:sl' flag; do
  case "${flag}" in
    i) INSTALL_DIR="${OPTARG}" ;;
    s) SNOWBOY_ENABLED=true ;;
    l) LEDS_ENABLED=true ;;
    *) print_usage
       exit 1 ;;
  esac
done

INSTALL_DIR=${@:$OPTIND:1}

# Usage Validation
if [ -z "$INSTALL_DIR" ]; then
   echo "ERROR: No installation directory specified"
   print_usage
   exit 1
fi

if [ ! -d $INSTALL_DIR ]; then
    mkdir -p $INSTALL_DIR
fi

INSTALLATION_DIR=$(cd "$INSTALL_DIR" && pwd)

echo Building MAX Sample Application at $INSTALLATION_DIR

sudo -k
IFS= read -rsp 'Enter your sudo/root password: ' password

sudo -S echo "Sudo Password Correct" <<< $password

###########################################################################################################

THIRD_PARTY_DIR="$INSTALLATION_DIR/third-party"
SNOWBOY_SRC_DIR="$THIRD_PARTY_DIR/snowboy"
AWS_SDK_SRC_DIR="$THIRD_PARTY_DIR/aws-sdk-cpp"
AVS_SDK_SRC_DIR="$THIRD_PARTY_DIR/avs-device-sdk"
PORTAUDIO_DIR="$THIRD_PARTY_DIR/portaudio"

SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"
MAX_TOOLKIT_SRC_DIR="$(dirname $SCRIPT_DIR)" #trim "Scripts/buildMAXToolkit.sh" off the path
echo "Toolkit Source is $MAX_TOOLKIT_SRC_DIR"
MAX_LIB_SRC_DIR="$MAX_TOOLKIT_SRC_DIR/MAX"
COMPUTER_AGENT_SRC_DIR="$MAX_TOOLKIT_SRC_DIR/Agents/Computer"
SAMPLE_APP_SRC_DIR="$MAX_TOOLKIT_SRC_DIR/SampleApplication"

MAX_LIB_BUILD_DIR="$INSTALLATION_DIR/build/max-lib"
AVS_SDK_BUILD_DIR="$INSTALLATION_DIR/build/avs-device-sdk"
COMPUTER_AGENT_BUILD_DIR="$INSTALLATION_DIR/build/computer-agent"
SAMPLE_APP_BUILD_DIR="$INSTALLATION_DIR/build/max-sample-app"
AWS_SDK_BUILD_DIR="$INSTALLATION_DIR/build/aws-sdk"

###########################################################################################################

if $SNOWBOY_ENABLED
then
    if [ -d $SNOWBOY_SRC_DIR ]; then
        announce_failure "FATAL: Please delete the $SNOWBOY_SRC_DIR directory before running the script"
        exit 1
    fi
fi

###########################################################################################################

# Create necessary build and install directories

if [ ! -d $INSTALLATION_DIR ]; then
    echo "Creating installation directory $INSTALLATION_DIR..."
    mkdir -p $INSTALLATION_DIR;
fi

echo "Using $INSTALLATION_DIR for MAXToolKit installation..."

echo "Creating build and install directories..."

mkdir -p $MAX_LIB_BUILD_DIR
mkdir -p $AVS_SDK_BUILD_DIR
mkdir -p $COMPUTER_AGENT_BUILD_DIR
mkdir -p $SAMPLE_APP_BUILD_DIR
mkdir -p $AWS_SDK_BUILD_DIR
mkdir -p $THIRD_PARTY_DIR

###########################################################################################################

# Build MAX Library

echo "Building MAX Library in $MAX_LIB_BUILD_DIR"
cd $MAX_LIB_BUILD_DIR

cmake $MAX_LIB_SRC_DIR \
 -DENABLE_DEMO_ONLY_SOFTWARE_CROSSWAKE_DETECTION=ON \

make -j $MAKE_THREADS_NUM

announce_success "MAX Library succesfully built & installed"

###########################################################################################################

# Build Portaudio

echo "Building PortAudio in $PORTAUDIO_DIR"

cd $THIRD_PARTY_DIR
wget -c http://www.portaudio.com/archives/pa_stable_v190600_20161030.tgz
tar zxf pa_stable_v190600_20161030.tgz
cd $PORTAUDIO_DIR
$PORTAUDIO_DIR/configure --without-jack --with-pic
make -j $MAKE_THREADS_NUM

announce_success "PortAudio succesfully downloaded and built"

###########################################################################################################

# Download Snowboy

if $SNOWBOY_ENABLED
then
    echo "Downloading Kitt.AI Snowboy wakeword engine..."
    if [ ! -d $THIRD_PARTY_DIR ]; then
        mkdir -p $THIRD_PARTY_DIR
    fi
    cd $THIRD_PARTY_DIR
    git clone --depth 1 https://github.com/Kitt-AI/snowboy.git
    cd $SNOWBOY_SRC_DIR
    git checkout c9ff036e2ef3f9c422a3b8c9a01361dbad7a9bd4
    cp -r resources/alexa/* resources/
    cp -r resources/alexa/alexa-avs-sample-app/* resources/
    echo "Installing Kitt.AI dependency lib-atlas-dev..."
    sudo -S apt -y install libatlas-base-dev <<<"$password"
    announce_success "Kitt.AI Snowboy wakeword engine succesfully downloaded"
fi

###########################################################################################################

# Build AVS SDK

echo "Checking out AVS Device SDK v1.23.0"

cd $THIRD_PARTY_DIR
git clone --single-branch https://github.com/alexa/avs-device-sdk.git -b v1.23.0

echo "Applying MAX Compatibility patch to AVS SDK"

cd $AVS_SDK_SRC_DIR
git apply $MAX_TOOLKIT_SRC_DIR/Agents/Alexa/avs-device-sdk-v1-23-0-max-compatability.patch

echo "Succesfully applied MAX Compatibility patch to AVS SDK"

echo "Building AVS SDK in $AVS_SDK_BUILD_DIR"

cd $AVS_SDK_BUILD_DIR

AVS_DEVICE_SDK_CMAKE_FLAGS=(
 "-DMultiAgentExperience_DIR=$MAX_LIB_BUILD_DIR"
 "-DPORTAUDIO=ON"
 "-DPORTAUDIO_LIB_PATH=$PORTAUDIO_DIR/lib/.libs/libportaudio.a"
 "-DPORTAUDIO_INCLUDE_DIR=$PORTAUDIO_DIR/include"
 "-DGSTREAMER_MEDIA_PLAYER=ON"
 "-DMAX_LIB_PATH=$MAX_LIB_BUILD_DIR/libMultiAgentExperience.so"
 "-DMAX_INCLUDE_DIR=$MAX_LIB_SRC_DIR/include"
)

if $SNOWBOY_ENABLED
then
  AVS_DEVICE_SDK_CMAKE_FLAGS+=( "-DKITTAI_KEY_WORD_DETECTOR=ON" )
  AVS_DEVICE_SDK_CMAKE_FLAGS+=( "-DKITTAI_KEY_WORD_DETECTOR_LIB_PATH=${SNOWBOY_SRC_DIR}/lib/rpi/libsnowboy-detect.a" )
  AVS_DEVICE_SDK_CMAKE_FLAGS+=( "-DKITTAI_KEY_WORD_DETECTOR_INCLUDE_DIR=${SNOWBOY_SRC_DIR}/include" )
fi


cmake $AVS_SDK_SRC_DIR "${AVS_DEVICE_SDK_CMAKE_FLAGS[@]}"

echo "Building and Installing AVS SDK to /usr/local/ ..."

make -j $MAKE_THREADS_NUM

sudo -S make install -j $MAKE_THREADS_NUM <<<"$password"

announce_success "AVS SDK succesfully built and installed"

###########################################################################################################

# Install AWS SDK

echo "Building AWS SDK in $AWS_SDK_BUILD_DIR..."

cd $THIRD_PARTY_DIR
git clone --depth 1 --single-branch --branch 1.8.0 https://github.com/aws/aws-sdk-cpp.git

cd $AWS_SDK_BUILD_DIR
cmake $AWS_SDK_SRC_DIR \
  -DBUILD_ONLY="lex;cognito-identity;sts;identity-management" \
  -DENABLE_TESTING=OFF

echo "Building and Installing AWS SDK..."
make -j $MAKE_THREADS_NUM

sudo -S make install -j $MAKE_THREADS_NUM <<<"$password"

announce_success "AWS SDK succesfully built and installed"

###########################################################################################################

# Build Computer Agent

echo "Building Computer Agent in $COMPUTER_AGENT_BUILD_DIR"

cd $COMPUTER_AGENT_BUILD_DIR

cmake $COMPUTER_AGENT_SRC_DIR \
 -DMultiAgentExperience_DIR=$MAX_LIB_BUILD_DIR

make -j $MAKE_THREADS_NUM

announce_success "Computer agent succesfully built and installed"

###########################################################################################################

# Build MAX Sample Application

echo "Building MAX Sample Application in $SAMPLE_APP_BUILD_DIR"

cd $SAMPLE_APP_BUILD_DIR

cmake_flags=(
 "-DGSTREAMER_MEDIA_PLAYER=ON"
 "-DPORTAUDIO=ON"
 "-DPORTAUDIO_LIB_PATH=$PORTAUDIO_DIR/lib/.libs/libportaudio.a"
 "-DPORTAUDIO_INCLUDE_DIR=$PORTAUDIO_DIR/include"
 "-DMultiAgentExperience_DIR=$MAX_LIB_BUILD_DIR"
 "-DComputerAgent_DIR=$COMPUTER_AGENT_BUILD_DIR"
 "-DOVERRIDE_ALSA_SINK=ON"
)

if $LEDS_ENABLED
then
  cmake_flags+=( "-DRPI_LEDS=ON" )
fi

if $SNOWBOY_ENABLED
then
  cmake_flags+=( "-DSNOWBOY_KEYWORD_DETECTOR=ON" )
  cmake_flags+=( "-DSNOWBOY_KEYWORD_DETECTOR_LIB_PATH=${SNOWBOY_SRC_DIR}/lib/rpi/libsnowboy-detect.a" )
  cmake_flags+=( "-DSNOWBOY_KEYWORD_DETECTOR_INCLUDE_DIR=${SNOWBOY_SRC_DIR}/include" )
fi

cmake $SAMPLE_APP_SRC_DIR "${cmake_flags[@]}"

make -j $MAKE_THREADS_NUM

#chmod 777 "$SAMPLE_APP_BUILD_DIR"

announce_success "MAX Sample Application build successful at $SAMPLE_APP_BUILD_DIR"

# Create the necessary links and cache to newly installed dependencies.
sudo -S ldconfig <<< "$password"
