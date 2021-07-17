# Sample Application

This is a Sample Application demonstrating correct usage of the MAX Library, while integrating two agents -
the MAX Computer Agent, as provided within this Toolkit, and the Alexa agent as provided by the
[AVS Device SDK](https://github.com/alexa/avs-device-sdk).

This Sample Application will show how a user may interact with different agents at different times, and how the
MAX Library solves the problems which arise in scenarios when agents may compete for the user's attention, and when
agents might need to co-operate with each other on the user's behalf.

## Prerequisites
### PortAudio
PortAudio is required to build the Sample Application.

```
mkdir $PORTAUDIO_DOWNLOAD_PATH
cd $PORTAUDIO_DOWNLOAD_PATH
wget -c http://www.portaudio.com/archives/pa_stable_v190600_20161030.tgz
tar zxf pa_stable_v190600_20161030.tgz
cd portaudio
./configure --without-jack
make -j $(nproc)
```

### GStreamer
GStreamer development libraries are required to build the Sample Application.

On Ubuntu, the required packages can be installed via apt:

```
sudo apt-get install -y \
 libgstreamer1.0-0 libgstreamer-plugins-base1.0-dev \
 gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad \
 gstreamer1.0-plugins-ugly gstreamer1.0-libav gstreamer1.0-doc gstreamer1.0-tools
```

### AVS Device SDK v1.23.0
#### Downloading the AVS Device SDK v1.23.0
The AVS Device SDK v1.23.0 is required to build the MAX Sample Application. The AVS Device SDK must then be updated with our provided patch, to support MAX.

First, follow the instructions to download and build the AVS Device SDK for your platform (Ubuntu Recommended): [AVS Device SDK Ubuntu Quick Start Guide](https://developer.amazon.com/en-US/docs/alexa/avs-device-sdk/ubuntu.html).

When checking out the AVS Device SDK source code, be sure to check out the v1.23.0 release.

- with `git clone`:
```
git clone --single-branch https://github.com/alexa/avs-device-sdk.git -b v1.23.0
```

- with `git checkout` after cloning the repository:
```
git clone --single-branch https://github.com/alexa/avs-device-sdk.git
cd avs-device-sdk
git checkout v1.23.0
```

#### Building and Setting Up the AVS Device SDK Sample Application
After you have downloaded the correct version of the AVS Device SDK, proceed with building the AVS Device SDK Sample Application, setting up a Configuration file, and running and authorizing the Sample Application.

You can follow the instructions on the Amazon Developer Portal for your platform (Ubuntu Recommended): [AVS Device SDK Ubuntu Quick Start Guide](https://developer.amazon.com/en-US/docs/alexa/avs-device-sdk/ubuntu.html).

Ensure that you are able to ask Alexa simple questions such as "What time is it?" before proceeding to the next steps.

#### Applying the MAX Compatability Patch to the AVS Device SDK source
The AVS Device SDK must be patched for MAX Compatibility, and then rebuilt in order to run the MAX Sample Application.

```
cd $AVS_DEVICE_SDK_SOURCE_DIRECTORY
git apply $MAX_TOOLKIT_SOURCE_DIRECTORY/Agents/Alexa/avs-device-sdk-v1-23-0-max-compatability.patch
```

Once patched, reconfigure, rebuild, and install the AVS Device SDK:
```
cd $AVS_DEVICE_SDK_BUILD_DIRECTORY
cmake . \
          -DMAX_LIB_PATH=$MAX_LIB_BUILD_DIR/libMultiAgentExperience.so \
          -DMAX_INCLUDE_DIR=$MAX_TOOLKIT_SOURCE/MAX/include/
make -j $(nproc)
sudo make install
```

## Build Instructions
Out of source builds are required:

    PATH_TO_PA=$PORTAUDIO_DOWNLOAD_PATH/portaudio
    mkdir $PATH_TO_SAMPLEAPP_BUILD
    cd $PATH_TO_SAMPLEAPP_BUILD
    cmake $PATH_TO_SAMPLEAPP_SOURCE \
        -DPORTAUDIO \
        -DPORTAUDIO_INCLUDE_DIR=$PATH_TO_PA/include \
        -DPORTAUDIO_LIB_PATH=$PATH_TO_PA/lib/.libs/libportaudio.so \
        -DGSTREAMER_MEDIA_PLAYER \
        -DMultiAgentExperience_DIR=$PATH_TO_MAX_BUILD \
        -DComputerAgent_DIR=$PATH_TO_COMPUTER_BUILD \
        -DOVERRIDE_ALSA_SINK
    make -j $(nproc)

### CMake Options
#### required

    -DMultiAgentExperience_DIR=$PATH_TO_MAX_BUILD

Required iff you did not install the MAX Library to a location where CMake can automatically find it.

    -DComputerAgent_DIR=$PATH_TO_COMPUTER_BUILD

Required iff you did not install the Computer Agent Library to a location where CMake can automatically find it.

    -DCMAKE_PREFIX_PATH=$CUSTOM_INSTALL_PATH

Alternative to the above, you can set the Prefix Path to include `~/max` or wherever you have installed the MAX Library and Computer Agent Library.

#### optional

    -DRPI_LEDS

Enables Raspberry Pi SenseHAT LED experience rendering. You must download the MAX Sample 
Application Alexa animation files from the Alexa Developer Portal, and place them in the 
`SampleApplication/Assets` directory.

    -DOVERRIDE_ALSA_SINK

Instructs audio rendering to direct to the ALSA sink.

    -DENABLE_DEMO_ONLY_SOFTWARE_CROSSWAKE_DETECTION

Enables a DEMO-ONLY implementation to prevent cross-wake detection.
