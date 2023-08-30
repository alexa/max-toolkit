# Multi-Agent Experience (MAX) Toolkit

The MAX Toolkit provides software which supports the integration of multiple voice agents on devices. The Toolkit also provides guidance to both device makers and agent developers towards this goal.

## Contents

The MAX Toolkit consists of the following primary component packages :

1. MultiAgentExperience-API : This source code package consists of the core set of interfaces that can be implemented by the device & agent manufacturers

2. MultAgentExperience (Core MAX Library) : This library is the core of the MAX Toolkit and include implementations of different features concerning the core objects dealt by MAX

3. MultiAgentExperience-Logger : This is a library package used by MAX library to log different details concerning internal MAX API operation

4. AVS SDK Patch & Adapter : This patch consists of changes required to support MultiAgent experiences in Alexa (AVS SDK). See the [README.md](MultiAgentExperience-Alexa-Adapter/README.md) for more information and build instructions

5. MAX Sample Application : This directory consists of two sub-directories namely ```MultiAgentExperience-CommandLine-Orchestrator``` & ```MultiAgentExperience-Integration-App``` which together provide ground for users to be able to test MAX library features using Alexa agent

## Requirements

Each component of the MAX Toolkit has prerequisites that must be met in order to build them. In addition, the following prerequisites are required for all components :

1. C++11 compiler
2. CMake v3.10 or later
3. Cli v2.0.2 or later. 
This can be installed by following the instructions:
[Cli Installation instuctions](https://github.com/daniele77/cli#installation)

Ubuntu 20.04 or MacOS(arm64) is the recommended platform for evaluating the MAX Toolkit

## Automated Interactive Build Script

As an alternative to manually building each of the MAX Toolkit packages, an automated bash building script is provided to fast-track getting the MAX Sample Application up and running.

The script is available in the Scripts directory .

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

The build script can be run once this is done with the following command: :

```./Scripts/buildMAX.sh```

The directory where MAX Sample Application and it's dependencies will be built are named ```cmake-build``` & ```lib``` and they will be located inside the MAX toolkit repository directory on your local machine.

Run the automated build script with no arguments to know more about its execution.

## API Reference

View the MultiAgentExperience-API directory for detailed information.

## Known Issues

See [CHANGELOG.md](CHANGELOG.md) for a list of known issues in each release.

## Security

See [CONTRIBUTING.md](CONTRIBUTING.md#security-issue-notifications) for more information.

## License

This project is licensed under the Apache-2.0 License, and the Amazon Software License. See [LICENSE](LICENSE) and [NOTICE](NOTICE).

