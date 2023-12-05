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

## Pre-requisites

### Hardware and Operating System
The build-script is tested on the below hardware
- A computer running Ubuntu version 20.04 LTS
- M1 Macbook running MacOS Ventura 13.5.2 


### AVS Device SDK
The accompanied build script downloads AVS Device SDK version 1.26. If you wish to download and build AVS Device SDK separately, you may do so using the below command. Please modify the build-script accordingly.
```
git clone --single-branch https://github.com/alexa/avs-device-sdk.git -b v1.26.0
```

While the build script builds and installs the AVS Device SDK, it is important to complete the setup to be able to interact with Alexa, including the steps to run and authorize the AVS SDK SampleApp. Take note of the full path to your updated AlexaClientSDKConfig.json file as it is required after the MAX Sample Application is built. The AVS Device SDK setup guides are linked below. 
* [Ubuntu](https://developer.amazon.com/en-US/docs/alexa/avs-device-sdk-1-2x/ubuntu.html)
* [Mac OS](https://developer.amazon.com/en-US/docs/alexa/avs-device-sdk-1-2x/mac-os.html)

### gRPC C++
The MAX IPC framework leverages gRPC C++ v1.54.0. More information on installing gRPC can be found here - [Installing gRPC C++](https://grpc.io/docs/languages/cpp/quickstart/).

### Other software 
* C++11 compatible compiler
* GNU Make
* CMake v3.10 or later

## Build the MAX Sample Application

Estimated time: 1-2 hours.

This section provides step-by-step instructions to set up the MAX Sample Application using the provided `buildMAX.sh` script. When finished, you will have a working version of the MAX Sample Application to test the interactions with Alexa.

To continue with the automated build process, open a terminal window.

### Download the MAX Toolkit Source Code

You can use the following command to download the MAX Toolkit source code to the `$PATH_TO_MAX_TOOLKIT_SOURCE` directory, which you should choose to contain the MAX Toolkit source.

```
git clone git@github.com:alexa/max-toolkit.git $PATH_TO_MAX_TOOLKIT_SOURCE
```

### Set important environment variables

To build the MAX Sample Application, simply run the Bash script located at - `Scripts/buildMAX.sh`. 

Before running the script, it is mandatory to export few variables from the terminal. The script expects Curl and PortAudio to be installed on the system. The path to the lib and include folders for the mentioned packages can be set as below.

```
export CURL_LIBRARY_PATH=$PATH_TO_CURL_LIB_FOLDER
export CURL_INCLUDE_DIR=$PATH_TO_CURL_INCLUDE_FOLDER
export PORTAUDIO_LIB_PATH=$PATH_TO_PORTAUDIO_LIB_FOLDER
export PORTAUDIO_INCLUDE_DIR=$PATH_TO_PORTAUDIO_INCLUDE_FOLDER
export GRPC_INSTALL_PATH=$PATH_TO_GRPC_INSTALL_FOLDER
```

Where:
* `PATH_TO_CURL_LIB_FOLDER` is the directory containing the CURL library files.
* `PATH_TO_CURL_INCLUDE_FOLDER` is the directory containing the CURL include files.
* `PATH_TO_PORTAUDIO_LIB_FOLDER` is the directory containing the PortAudio library files.
* `PATH_TO_PORTAUDIO_INCLUDE_FOLDER` is the directory containing the PortAudio include files.
* `$PATH_TO_GRPC_INSTALL_FOLDER` is the directory where the gRPC C++ library is installed.


### Run the build script
Once the relevant paths are exported as indicated above, the build script is ready to be run. The following command can be executed from the terminal.

```
cd $PATH_TO_MAX_TOOLKIT_SOURCE/Scripts/
./buildMAX.sh 
```

Where `PATH_TO_MAX_TOOLKIT_SOURCE` is the directory containing the MAX Toolkit repository.


Once the script finishes successfully, the required binaries should be available inside the `$PATH_TO_MAX_TOOLKIT_BUILD` and `$PATH_TO_MAX_TOOLKIT_INSTALL` directories. 
* Where `$PATH_TO_MAX_TOOLKIT_BUILD` is the `$PATH_TO_MAX_TOOLKIT_SOURCE/build` directory.
* Where `$PATH_TO_MAX_TOOLKIT_INSTALL` is the `$PATH_TO_MAX_TOOLKIT_SOURCE/install` directory.


## Executing the MAX Sample Application

As of MAX Toolkit v2.0.0, the recommended approach of testing multi-agent features is via the MAX IPC framework. To test multi-agent features, MAX Toolkit v2.0.0 facilitates the creation of the following 3 processes:
1. MAX process
2. Alexa process (agent 1)
3. Alexa process (agent 2)

To run the MAX process, the MAX Sample Application binary located in the below directory, can be used.
```
$PATH_TO_MAX_TOOLKIT_INSTALL/MultiAgentExperience-Integration-App/bin/MultiAgentExperience-Integration-App
```

To run the Alexa process(es), the AVS SDK SampleApp binary is to be used. It is located here:
```
$PATH_TO_MAX_TOOLKIT_BUILD/AVS-SDK/SampleApp/src/SampleApp
```

Follow the instructions below to run all three processes.

### Setup AVS Device SDK
AVS SDK needs to be setup and the `AlexaClientSDKConfig.json` should be generated before running the sample application. The following links can be used to complete the AVS Device SDK setup.
* [Ubuntu](https://developer.amazon.com/en-US/docs/alexa/avs-device-sdk-1-2x/ubuntu.html)
* [Mac OS](https://developer.amazon.com/en-US/docs/alexa/avs-device-sdk-1-2x/mac-os.html)

Note: since we intend to run two Alexa processes, two `AlexaClientSDKConfig.json` files should be generated using two Amazon accounts.

### Export library paths 
The MAX Sample Application (and AVS SDK SampleApp) will require the paths to libraries that have been built by the script. Run the following command based on the OS to achieve this, before running the sample application.

* Mac OS
```
export DYLD_LIBRARY_PATH=$DYLD_LIBRARY_PATH:$PATH_TO_MAX_TOOLKIT_INSTALL/MultiAgentExperience/lib:$PATH_TO_MAX_TOOLKIT_INSTALL/MultiAgentExperience-Logger/lib:$PATH_TO_MAX_TOOLKIT_INSTALL/AVS-SDK/lib:$PATH_TO_MAX_TOOLKIT_INSTALL/MultiAgentExperience-ThreadExecutor/lib:$PATH_TO_MAX_TOOLKIT_INSTALL/MultiAgentExperience-IPC/lib:$PATH_TO_MAX_TOOLKIT_INSTALL/MultiAgentExperience-IPC-gRPC/lib
```

* Linux
```
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$PATH_TO_MAX_TOOLKIT_INSTALL/MultiAgentExperience/lib:$PATH_TO_MAX_TOOLKIT_INSTALL/MultiAgentExperience-Logger/lib:$PATH_TO_MAX_TOOLKIT_INSTALL/AVS-SDK/lib:$PATH_TO_MAX_TOOLKIT_INSTALL/MultiAgentExperience-ThreadExecutor/lib:$PATH_TO_MAX_TOOLKIT_INSTALL/MultiAgentExperience-IPC/lib:$PATH_TO_MAX_TOOLKIT_INSTALL/MultiAgentExperience-IPC-gRPC/lib
```

Where `$PATH_TO_MAX_TOOLKIT_INSTALL` is the directory where MAX toolkit has been installed by the build script.

### Run the MAX Sample Application and AVS SDK SampleApp

1. Run the MAX process
```
cd $PATH_TO_MAX_TOOLKIT_INSTALL/MultiAgentExperience-Integration-App/bin/
./MultiAgentExperience-Integration-App MyDevice unix:///tmp/alexa1.sock unix:///tmp/max1.sock unix:///tmp/alexa2.sock unix:///tmp/max2.sock
```

2. Run the Alexa process (agent 1)
```
cd $PATH_TO_MAX_TOOLKIT_INSTALL/AVS-SDK/SampleApp/src
GST_PLUGIN_PATH=$PATH_TO_GSTREAMER ./SampleApp $PATH_TO_ALEXA_CLIENT_SDK_CONFIG_FILE/AlexaClientSDKConfig.json DEBUG7 unix:///tmp/max1.sock unix:///tmp/alexa1.sock Alexa1
```

Where:
* `PATH_TO_GSTREAMER` is the directory containing the `Gstreamer` plugin. The GST_PLUGIN_PATH is used to override the `Gstreamer` plugin search path to `$PATH_TO_GSTREAMER`.
* `PATH_TO_ALEXA_CLIENT_SDK_CONFIG_FILE` is the directory containing `AlexaClientSDKConfig.json` file generated in the previous section

3. Run the Alexa process (agent 2)
```
cd $PATH_TO_MAX_TOOLKIT_INSTALL/AVS-SDK/SampleApp/src
GST_PLUGIN_PATH=$PATH_TO_GSTREAMER ./SampleApp $PATH_TO_ALEXA_CLIENT_SDK_CONFIG_FILE/AlexaClientSDKConfig.json DEBUG7 unix:///tmp/max2.sock unix:///tmp/alexa2.sock Alexa2
```

Note: the Unix Domain Sockets URIs represent the gRPC servers for the Alexas and MAX respectively. If the URIs are changed, they need to be updated in all commands accordingly.


### Interacting with the Agents

Once you run the MAX and the Alexa process(es), you can now experience multi-agent features.

* Activate Alexa by pressing `t` and then hitting enter. Do this in the Alexa process.
You should see a series of messages scrolling in your terminal window. One of these messages shows a Listening status. This status indicates that Alexa is listening to a user query.

* Say "Tell me a joke."
Alexa responds with a funny joke. You should see the text change from Listening to Thinking..., then Speaking.
