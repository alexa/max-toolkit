# MultiAgentExperience Alexa Adapter

The MultiAgentExpereince Alexa Adapter (MAX Alexa Adapter) library enables integration
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
-DEXTENSION_PATHS=<existing-extension-paths>;<path-to-adapter-source-dir>
```

Here is what each argument means:

- `MULTI_AGENT_EXPERIENCE_ENABLED=ON` - Enables the MultiAgentExperience Alexa Adapter.
- `MultiAgentExperience-API_DIR` - Sets the location for cmake find_package to find the MultiAgentExpereince-API
  library. This will be setup after following the MultiAgentExperience API library install directions.
- `EXTENSION_PATHS` - A semi-colon separated list of paths to search for CMake projects.
  Add to this list <the-path-to-this-directory>.

### Building the AVS Device SDK

Follow the rest of the build instructions for the AVS Device SDK normally. Note that the AVS Device SDK does not
currently support multi-agent experiences, and does not use the MultiAgentExperience library itself. This means the
expected behavior when running the AVS Device SDK SampleApp is for Alexa to no longer work.

To use Alexa in a multi-agent experience the MultiAgentExperience Alexa Adapter must be registered to a MAX library.

## Registering with Alexa and MAX

To register with MAX you must create an `AlexaAgentRegistration`. The dependencies for this are the same needed to
integrate with the AVS SDK, and can be created alongside the AVS SDK `DefaultClient` or equivalent setup component.

Once you have an `AlexaAgentRegistration` it can be registered with the `AgentManager::registerAgents` API exposed by
MAX.

```
    // Example Alexa and MAX setup

    auto maxFocusMediator = std::make_shared<multiAgentExperience::mediator::MAXFocusMediator>();
    auto alexaAgentRegistration =
            std::make_shared<multiAgentExperience::agent::AlexaAgentRegistration>(maxFocusMediator);

    auto avsSDKDefaultClient = alexaClientSDK::defaultClient::DefaultClient::create(
    // ...
    // Lots of components are skipped here... See AVS SDK documentation for details.
    // ...
            ...,
            maxFocusMediator);

    // Build MAX with the correct options for your use case.
    auto max = multiAgentExperience::application::MAXBuilder()
            .withNormalPriorityCrossAgentBargeIn(
                    multiAgentExperience::application::NormalPriorityCrossAgentBargeInPolicy::NOT_SUPPORTED)
            .withHighPriorityCrossAgentBargeIn(
                    multiAgentExperience::application::HighPriorityCrossAgentBargeInPolicy::SUPPORTED)
            .build();
    auto agentManager = max->getAgentManager();

    agentManager->registerAgents({alexaAgentRegistration, anyOtherAgentRegistrations...});
```
