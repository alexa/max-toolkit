# Multi-Agent Experience (MAX) Toolkit

The MAX Toolkit provides software which supports the integration of multiple voice agents on devices. The Toolkit also provides guidance to both device makers and agent developers towards this goal.

## Overview of the MAX Library
MAX Library exposes client-side APIs to enable control of multiple Agents. These APIs enable developers to coordinate multi-agent experiences both visually and audibly, and implement client-side Universal Device Commands (UDCs).

The diagram below illustrates the interactions between Agents, Device applications, and the MAX Library. The Device application represents the software owned by a Device-maker to initialize the MAX Library and Agents. The Multi-Agent Sample Application is a concrete example of a Device application. Through the use of MAX Library, Agent experiences are coordinated through the use of common focus and activity managers. The Device application is responsible for rendering these experiences and handling user input. Both Agents and the Device application make calls to and from the MAX Library. The Device application also makes calls to Agents for operations that do not require use of the MAX Library. For example, handling a button which triggers a specific Agent’s feature.

It is important to note that:

* Agents never directly call each other. They must use  the MAX Library for use cases that require interaction such as for Universal Device Commands.
* The MAX Library does not interact with the Agent  backend services. It only interacts with the device-side implementation for each Agent.
* Multiple Agents may also share the same backend service.

![Overview](Documentation/images/MAXOverviewAgentsAndDevices.png)

## Contents

The MAX Toolkit consists of the following primary component packages:

1. MultiAgentExperience-API - This source code package consists of the core set of interfaces that can be implemented by the device & agent manufacturers.

2. MultiAgentExperience (Core MAX Library) - This library is the core of the MAX Toolkit and include implementations of different features concerning the core objects dealt by MAX.

3. AVS SDK Patch & Alexa Adapter - This patch consists of changes required to support MultiAgent experiences in Alexa (AVS SDK). See the [README.md](MultiAgentExperience-Alexa-Adapter/README.md) for more information and build instructions

4. MAX Sample Application - This directory consists of one package - MultiAgentExperience-Integration-App which provides ground for users to be able to test MAX library features using the Alexa agent.

5. MultiAgentExperience-IPC and MultiAgentExperience-IPC-gRPC - These are the library packages that form the MAX IPC framework, which facilitates inter-process communication between MAX and the agents.

6. MultiAgentExperience-Logger - This is a library package used by MAX library to log different details concerning internal MAX API operation

7. MultiAgentExperience-ThreadExecutor - This is a library package used by MAX for multi-threading.

## Requirements

Each component of the MAX Toolkit has pre-requisites that must be met in order to build them. Read more about this in the [MAX_Sample_Application_Getting_Started_Guide - Pre-requisites](Documentation/MAX_Sample_Application_Getting_Started_Guide.md#pre-requisites) section.

## Building the MAX library

As an alternative to manually building each of the MAX Toolkit packages, an automated BASH build script is provided to fast-track getting the MAX Sample Application up and running. Read more about this in the [MAX_Sample_Application_Getting_Started_Guide](Documentation/MAX_Sample_Application_Getting_Started_Guide.md).

## MAX APIs

See the [MultiAgentExperience-API](MultiAgentExperience-API) directory to see the APIs exposed by MAX. The [Documentation](Documentation) section has information on how agents and devices can use the MAX APIs to provide multi-agent features for their products.

## Known Issues

See [CHANGELOG.md](CHANGELOG.md) for a list of known issues in each release.

## Security

See [CONTRIBUTING.md](CONTRIBUTING.md#security-issue-notifications) for more information.

## License

This project is licensed under the Apache-2.0 License, and the Amazon Software License. See [LICENSE](LICENSE) and [NOTICE](NOTICE).

