# MAX Sample Application Getting Started Guide

The Multi Agent Experience (MAX) developer toolkit contains the MAX Library and a
Sample Application that demonstrates integration of Alexa with the MAX Library. The MAX Library facilitates interoperability between
voice assistants according to the guidance provided by the Voice Interoperability
Initiative (VII) [Multi-Agent Design Guide](https://developer.amazon.com/en-US/alexa/voice-interoperability/design-guide).

This guide will walk you through the prerequisite setup steps and instructions for using an automated build script for the MAX Sample Application.

Depending on your system, this setup process may take between 1 hour (Desktop computer running Ubuntu) and 4 hours (Raspberry Pi 4).

## What’s inside the MAX Toolkit?

The MAX Toolkit contains:

1. MAX Library (Directory: MultiAgentExperience/): The library that manages
multiple agents, and handles their interaction patterns, consistent with
recommendations in the Multi-Agent Design Guide.
2. MAX Library APIs (Directory: MultiAgentExperience-API/): The APIs that are supported by the MAX Library. Any agents that need to communicate with the MAX Library can do so with the help of these APIs.
3. Alexa-Adapter (Directory: MultiAgentExperience-Alexa-Adapter/): Adapter for AVS-SDK to communicate with MAX Library.
4. MAX Sample Application (Directory: SampleApp/): A Sample Application that runs Alexa, console-based experience rendering, and uses the MAX Library to enforce expected behavior.
5. Logger (Directory: MultiAgentExperience-Logger/): A rudimentary console-logger that can be used to track and debug the use of MAX components.

In addition, the MAX Toolkit includes a patch that can be used to modify the [AVS Device SDK v1.26.0](https://developer.amazon.com/docs/alexa/avs-device-sdk/overview.html) to support a MAX-integrated Alexa device-side agent implementation.

## Hardware and Software Requirements

### Hardware
- A computer supporting Ubuntu version 20.04 LTS or later (for fast build times)

### Software

#### Operating System
- Ubuntu operating system, version 20.04 LTS or later (for quicker build time)

#### AVS Device SDK
Make sure to download/build version 1.26. The accompanied build script will do this for you and you do not need to do this explicitly, if not required.

```
git clone --single-branch https://github.com/alexa/avs-device-sdk.git -b v1.26.0
```

##### Setup Guide

- Set up the AVS SDK following the instructions here:
  - [Ubuntu](https://developer.amazon.com/en-US/docs/alexa/avs-device-sdk/ubuntu.html)

You must fully complete the setup to be able to interact with Alexa, including the steps to run and authorize the AVS SDK sample app. Take note of the full path to your updated AlexaClientSDKConfig.json file as it is required after the MAX Sample Application is built.

#### Other software

- A C++11 Compatible compiler
- git
- gnu make
- cmake v3.10 or later

## Setting up the MAX Sample Application

Estimated time: 1-2 hours.

This section provides step-by-step instructions to set up the MAX Sample Application on a Ubuntu PC using the provided **buildMAX.sh** script. When finished, you will have a working version of the MAX Sample Application to test the interactions with Alexa.

To continue with the automated build process, open a terminal window.

### Download the MAX Toolkit Source Code

You can use the following command to download the MAX Toolkit source code to the `$PATH_TO_MAX_TOOLKIT_SOURCE` directory, which you should choose to contain the MAX Toolkit source.

```
git clone git@github.com:alexa/max-toolkit.git $PATH_TO_MAX_TOOLKIT_SOURCE
```

### Build the MAX Sample Application

Running the build script is quite simple, it is located at `Scripts/buildMAX.sh` and can be run from any working directory. 

Before running the script, it is mandatory to export few variables from the terminal. The script expects Curl and PortAudio to be installed on the system. The path to the lib and include folders for the mentioned packages can be set as below.

```
export CURL_LIBRARY_PATH=$PATH_TO_CURL_LIB_FOLDER
export CURL_INCLUDE_DIR=$PATH_TO_CURL_INCLUDE_FOLDER
export PORTAUDIO_LIB_PATH=$PATH_TO_PORTAUDIO_LIB_FOLDER
export PORTAUDIO_INCLUDE_DIR=$PATH_TO_PORTAUDIO_INCLUDE_FOLDER
```

Where:
* `PATH_TO_CURL_LIB_FOLDER` is the directory containing the CURL library files.
* `PATH_TO_CURL_INCLUDE_FOLDER` is the directory containing the CURL include files.
* `PATH_TO_PORTAUDIO_LIB_FOLDER` is the directory containing the PortAudio library files.
* `PATH_TO_PORTAUDIO_INCLUDE_FOLDER` is the directory containing the PortAudio include files.

Once the relevant paths are exported as indicated above, the build script is ready to be run. Following command can be executed from the Terminal.

```
$PATH_TO_MAX_TOOLKIT_SOURCE/Scripts/buildMAX.sh 
```

Where `PATH_TO_MAX_TOOLKIT_SOURCE` is the directory containing the MAX Toolkit repository.

Once the script finishes successfully, the MAX Sample Application `MultiAgentExperience-Integration-App` should be built in `$MAX_TOOLKIT_INSTALL_DIR/MultiAgentExperience-Integration-App/bin/MultiAgentExperience-Integration-App/`.

***Note:*** All the build libraries and include files are copied to the `install` folder that will be generated within the directory MAX Toolkit is cloned into.

## Running the MAX Sample Application

* Navigate to the MAX Sample Application build directory:

```
cd $MAX_TOOLKIT_INSTALL_DIR/MultiAgentExperience-Integration-App/bin/MultiAgentExperience-Integration-App/
```

### Setup AVS-SDK
AVS SDK needs to be setup and `AlexaClientSDKConfig.json` should be generated before running the Sample App. Following link can be used for the setup.
[Ubuntu - AVS SDK Setup](https://developer.amazon.com/en-US/docs/alexa/avs-device-sdk/ubuntu.html)

### Export the library paths
MAX Sample App will require the paths to libraries that have been built by the script. Run the following command based on the OS to achieve this, before running the sample app.

* ***MAC OS:***
```
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$PATH_TO_INSTALL_DIR/MultiAgentExperience/lib:$PATH_TO_INSTALL_DIR/MultiAgentExperience-Logger/lib:$PATH_TO_INSTALL_DIR/MultiAgentExperience-CommandLine-Orchestrator/lib:$PATH_TO_INSTALL_DIR/AVS-SDK/lib
```

Where `PATH_TO_INSTALL_DIR` is the directory where MAX toolkit has been installed by you / the build script.

* ***Linux:***
```
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PATH_TO_INSTALL_DIR/MultiAgentExperience/lib:$PATH_TO_INSTALL_DIR/MultiAgentExperience-Logger/lib:$PATH_TO_INSTALL_DIR/MultiAgentExperience-CommandLine-Orchestrator/lib:$PATH_TO_INSTALL_DIR/AVS-SDK/lib
```

Where `PATH_TO_INSTALL_DIR` is the directory where MAX toolkit has been installed by you / the build script.

### Run the MAX Sample Application.
From `$MAX_TOOLKIT_INSTALL_DIR/build/max-sample-app` you can run the Sample Application:

```
GST_PLUGIN_PATH=$PATH_TO_GSTREAMER ./MultiAgentExperience-Integration-App $PATH_TO_ALEXA_CLIENT_SDK_CONFIG_FILE/AlexaClientSDKConfig.json
```

Where:
* `PATH_TO_GSTREAMER` is the directory containing the `Gstreamer` plugin.
* `PATH_TO_ALEXA_CLIENT_SDK_CONFIG_FILE` is the directory containing `AlexaClientSDKConfig.json` file generated in previous section
* 
***Note:*** The GST_PLUGIN_PATH is used to override the `Gstreamer` plugin search path to `$PATH_TO_GSTREAMER`.

***Note:*** If the agents do not respond to your queries, or you are unable to hear their responses please consult the **Troubleshooting** section below.

### Testing the MAX Sample Application

* Activate Alexa by pressing `t 1` and then hitting enter.
You should see a series of messages scrolling in your terminal window. One of these messages shows a Listening status. This status indicates that the wake word you spoke triggered Alexa.


* Say *"Tell me a joke."*
Alexa responds with a funny joke. You should see the text change from Listening to Thinking..., then Speaking.


### Interactions

You can trigger Alexa by using tap-to-talk.

#### Interact with Alexa by using tap-to-talk

Press 't 1'+Enter to talk to Alexa. This command simulates a Tap-to-Talk interaction.

For example:
*You* ('t 1'+Enter): "What's the weather like?"
*Alexa*: "Right now in Portland, it's 71 degrees with sun..."

## Troubleshooting Setup

See also the [AVS Device SDK Troubleshooting Guide](https://developer.amazon.com/en-US/docs/alexa/avs-device-sdk/troubleshooting.html).

#### If you receive the following error when running the MAX Sample Application:

```
MediaPlayer:handleBusMessageError:name=AudioMediaPlayer,source=audio_sink, error=Could not open audio device for playback. Device is being used by another application.,debug=gstalsasink.c(860)\: gst_alsasink_open ()\: /GstPipeline\:audio- pipeline/GstAlsaSink\:audio_sink\: hdmi 1
```

- Open the ~/.asoundrc file
- nano ~/.asoundrc
- Make a backup of the .asoundrc file and replace its contents with the below. The numerical device id's may vary: use the one assigned to the device you intend to use:

```
pcm.dmixed {
     type dmix
     ipc_key 1024
     ipc_key_add_uid 0
     slave.pcm "hw:2,0"
}
 pcm.dsnooped {
     type dsnoop
     ipc_key 1025
     slave.pcm "hw:2,0"
 }
 pcm.duplex {
     type asym
     playback.pcm "dmixed"
     capture.pcm {
         type plug
             slave.pcm "hw:2,0"
     }
 }

 # Instruct ALSA to use pcm.duplex as the default device
pcm.!default {
    type plug
     slave.pcm "duplex"
}
ctl.!default {
     type hw
         card 2
 }
```

#### If audio is being routed to your HDMI monitor and the first few words of every Text-To-Speech response are precluded, enter the following command in a terminal window:

```
vcgencmd force_audio hdmi 1
```