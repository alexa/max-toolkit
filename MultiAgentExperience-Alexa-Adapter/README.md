# MultiAgentExperience Alexa Adapter

The MultiAgentExperience Alexa Adapter (MAX Alexa Adapter) library enables integration
with the MultiAgentExperience (MAX) library.

These instructions must be followed as part of setting the correct cmake arguments when
building the AVS Device SDK.

## Building

### Prepare MAX

The MAX Alexa Adapter works with the MultiAgentExperience API library. Ensure you
have a version which matched the expected version in CMakeLists.txt MAX_API_MIN_VER.

Follow instructions to install the MultiAgentExperience API library before continuing.

### Prepare AVS SDK

Ensure you have an AVS Device SDK which matched the expected version found in
CMakeLists.txt AVS_DEVICE_SDK_MIN_VER.

There may also be a required patch to apply to the AVS Device SDK as well. If this
is not applied, the cmake step will fail with further instructions.

### Run cmake for AVS SDK with MAX Adapter Arguments

To build the AVS Device SDK with the MAX Alexa Adapter, these CMake arguments can
be used:

```
-DMULTI_AGENT_EXPERIENCE_ENABLED=ON
-DMultiAgentExperience-API_DIR=<path-to-MultiAgentExperience-API-install>/lib/cmake>
-DMultiAgentExperience-ThreadExecutor_DIR=<path-to-MultiAgentExperience-ThreadExecutor-install>/lib/cmake
-DMultiAgentExperience-Logger_DIR=<path-to-MultiAgentExperience-Logger-install>/lib/cmake
-DMultiAgentExperience-IPC_DIR=<path-to-MultiAgentExperience-IPC-install>/lib/cmake
-DMultiAgentExperience-IPC-gRPC_DIR=<path-to-MultiAgentExperience-IPC-gRPC-install>/lib/cmake
-DEXTENSION_PATHS=<existing-extension-paths>;<path-to-adapter-source-dir>
```

Here is what each argument means:

- `MULTI_AGENT_EXPERIENCE_ENABLED=ON` - Enables the MultiAgentExperience Alexa Adapter.
- `MultiAgentExperience-API_DIR` - Sets the location for CMake find_package to find the MultiAgentExperience-API
  library. This will be setup after following the MultiAgentExperience API library install directions.
- `MultiAgentExperience-ThreadExecutor_DIR` - Sets the location for CMake find_package to find the MultiAgentExperience-ThreadExecutor library.
- `MultiAgentExperience-Logger_DIR` - Sets the location for CMake find_package to find the MultiAgentExperience-Logger library.
- `MultiAgentExperience-IPC_DIR` - Sets the location for CMake find_package to find the MultiAgentExperience-IPC library.
- `MultiAgentExperience-IPC-gRPC_DIR` - Sets the location for CMake find_package to find the MultiAgentExperience-IPC-gRPC library.
- `EXTENSION_PATHS` - A semi-colon separated list of paths to search for CMake projects.
  Add to this list <the-path-to-this-directory>.

### Building the AVS Device SDK

Follow the rest of the build instructions for the AVS Device SDK normally. Note that the AVS Device SDK does not
currently support multi-agent experiences, and does not use the MultiAgentExperience library itself. This means the
expected behavior when running the AVS Device SDK SampleApp (without MAX Alexa Adapter) is for Alexa to no longer work.

To use Alexa in a multi-agent experience the MultiAgentExperience Alexa Adapter must be registered to a MAX library.

## Registering with Alexa and MAX

As of MAX Toolkit v2.0.0, the expected usage of MAX library is via the MAX Inter-Process Communication (IPC) framework. 
Alexa and MAX are expected to run in their own processes. To register Alexa with MAX library, you must create the 
respective connections in each process. The below section explains how this can be done.

### Create two Unix domain sockets

The MAX IPC framework creates two gRPC servers, one each in the MAX and Alexa processes. The recommended transport mechanism
for inter-process communication is Unix domain sockets. Hence, you must create two sockets, one for MAX and one for Alexa.

```
std::string MAX_URI = "unix:///tmp/max.sock"
std::string ALEXA_URI = "unix:///tmp/alexa.sock"
```

### Start the Alexa process

You must create an `AlexaAgentRegistration` which Alexa's representation of a MAX agent. The dependencies for this are the same
needed to integrate with the AVS SDK, and can be created alongside the AVS SDK `DefaultClient` or equivalent setup component.
Once you have an `AlexaAgentRegistration` it can be used to create a connection to the MAX process via the `MAXConnection`
class.

```
    // Example Alexa setup

    auto maxFocusMediator = std::make_shared<multiAgentExperience::mediator::MAXFocusMediator>();
    auto alexaAgentRegistration =
            std::make_shared<multiAgentExperience::agent::AlexaAgentRegistration>(maxFocusMediator);

    auto avsSDKDefaultClient = alexaClientSDK::defaultClient::DefaultClient::create(
    // ...
    // Lots of components are skipped here... See AVS SDK documentation for details.
    // ...
            ...,
            maxFocusMediator);
    
    // Connection to the MAX process
    auto maxConnection = std::make_shared<alexaClientSDK::multiAgentExperience::agent::MAXConnection>(
        alexaAgentRegistration, maxFocusMediator, MAX_URI, ALEXA_URI);     
    maxConnection->connect();
```


### Start the MAX process

To register Alexa with MAX, you must create an `AgentRegistrationAdapter`. This object holds dual responsibilities. It 
serves as the `AgentRegistrationInterface` object (for Alexa) which is required by MAX during agent registration. It also
manages the IPC connection to the Alexa process internally. The example code below explains how agent registration can
be done after creating a MAX object.

```
    // Example MAX setup
    
    // Build MAX with the correct options for your use case.
    auto max = multiAgentExperience::application::MAXBuilder()
            .withNormalPriorityCrossAgentBargeIn(
                    multiAgentExperience::application::NormalPriorityCrossAgentBargeInPolicy::NOT_SUPPORTED)
            .withHighPriorityCrossAgentBargeIn(
                    multiAgentExperience::application::HighPriorityCrossAgentBargeInPolicy::SUPPORTED)
            .build();
    auto agentManager = max->getAgentManager();
    
    // The set of agents to be registered with MAX
    std::set<std::shared_ptr<multiAgentExperience::agent::AgentRegistrationInterface>> agents;
    
    // Create the Alexa agent
    // Note that the URIs are switched here, as compared to the usage in MAXConnection
    auto connectionConfig = multiAgentExperience::ipc::grpc::connection::GrpcConnectionConfiguration(ALEXA_URI, MAX_URI);
    auto alexaAgent = std::make_shared<multiAgentExperience::ipc::grpc::connection::AgentRegistrationAdapter>(
        max->getAgentManager(), connectionConfig);
        
    if (alexaAgent->connect()) {
        agents.insert(alexaAgent);
    }
    
    agents.insert(anyOtherAgentRegistrations);
    
    agentManager->registerAgents(agents);
```
