# Multi-Agent Experience (MAX) Toolkit

The MAX Toolkit provides software which supports the integration of multiple voice agents on devices.
The Toolkit also provides guidance to both device makers and agent developers towards this goal.

## Contents

The MAX Toolkit contains three primary components:

1. **MAX Library**: This library is the core of the MAX Toolkit.
   See the [README.md](MAX/README.md) for more information and build instructions.
2. **Computer Agent Library**: This library provides an AWS-powered agent named "Computer", for demonstration purposes, that is able to answer
   simple questions about itself. See the [README.md](Agents/Computer/README.md) for more information and build instructions.
3. **MAX Sample Application**: This Sample Application integrates the Computer Agent with Alexa (via the [AVS Device SDK](https://github.com/alexa/avs-device-sdk)) to demo the MAX Library features. See the [README.md](SampleApplication/README.md) for more information and building instructions.

## Requirements

Each component of the MAX Toolkit has prerequisites that must be met in order to build them.
In addition, the following prerequisites are required for all components:

1. C++11 compiler
2. CMake v3.10 or later

Ubuntu 20.04 is the recommended platform for evaluating the MAX Toolkit, or alternatively Raspbian Buster on a Raspberry Pi 4.

## Automated Build Script

As an alternative to manually building each of the MAX Toolkit projects, an automated `bash` building script is provided to fast-track getting the MAX Sample Application up and running.

The script is available in the `Scripts` directory and can be run with the following command:

```
./Scripts/buildMAXSampleApplication.sh <PATH_TO_BUILD_DIR>
```

Where `PATH_TO_BUILD_DIR` is a relative or absolute path to a directory where the MAX Sample Application and its dependencies will be built. If the directory does not exist it will be created.

Note: The build script provides support for including the Kitt.AI Snowboy wake word engine for Raspberry Pi. If you use this wake word engine in your product, please take note of the Kitt.AI license terms. (You can find the Kitt.AI Snowboy GitHub repository [here](https://github.com/Kitt-AI/snowboy))

## API Reference

View the [C++ API References](https://alexa.github.io/max-toolkit) for detailed information.

## Known Issues

See [CHANGELOG.md](CHANGELOG.md) for a list of known issues in each release.

## Security

See [CONTRIBUTING.md](CONTRIBUTING.md#security-issue-notifications) for more information.

## License

This project is licensed under the Apache-2.0 License, and the Amazon Software License. See [LICENSE](LICENSE) and [NOTICE](NOTICE).
