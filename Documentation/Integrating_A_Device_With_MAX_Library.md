# Integrating a Device with MAX Library
## Introduction
### What is a Device?
A Device is any product that enables users to interact with voice agents. Often this is a dedicated device, but the device could also be a multipurpose product such as a vehicle’s onboard computer. Voice agents can also be accessed through applications on a general computing device like a phone or desktop computer.

For the purpose of this document the device is simply the host for the voice agent software that is responsible for interacting with the end user whether a dedicated or multipurpose device, or an app on a phone or desktop computer.

### The Multi Agent Experience Library

A Device can use the Multi Agent Experience Library (MAX) to enable seamless support for multiple voice agents working cooperatively. Integrating your Device with MAX consists of initializing the MAX system, writing methods to respond to requests from agents that are collected and delivered by MAX, and registering any MAX compatible voice agents with the MAX system.

The device application will create and manage the lifecycle for the `MAXInterface` object, which is the central component of the MAX Library. `MAXInterface` provides an interface to register Agents, register device Activities, control Universal Device Commands (UDCs), and observe Agent user experience requests. Registering an Agent with MAX provides the agent with access to the MAX Dialog and Activity APIs, the Experience System, as well as support for Universal Device Commands and other features.

The Experience System, accessed through the `ExperienceManagerInterface` provided by the `MAXInterface` allows the device to respond to Agent requests for user experience changes.

See the MAX Toolkit Glossary for definitions for the following relevant terms: 
 - Actor
 - Agent
 - Attention System
 - Device
 - Experience
 - Universal Device Commands (UDCs)
 - Wake Word

## MAXInterface

### MAXBuilder
The device application can instantiate the `MAXInterface` (Appendix A: Code 1) using the `MAXBuilder`. The parameters required to create a MAXInterface (because of different device application use cases) are growing, with some potentially optional parameters. For example the device application may specify the policies which enable/disable different kinds of Barge-Ins (cross-agent, same-agent), and many more. To make this easier to provision correctly and clearly, a `MAXBuilder` object has been introduced with documentation on how to build the `MAXInterface`. The device application can choose any combination of policies specified in the `MAXPolicies`. The `MAXInterface` API then provides methods to get access to the `AgentManagerInterface` and `ExperienceManagerInterface` etc.

```C++
class myApplication {
public:
    myApplication() {
        MAXBuilder builder;
        myMax = builder
                    .setIntegratorActorId(actor::ActorId("ExampleAgent"))
                    .withNormalPriorityCrossAgentBargeIn(NOT_SUPPORTED)
                    .withHighPriorityCrossAgentBargeIn(SUPPORTED)
                    .build();
    }
    
 private:
    std::shared_ptr<MAXInterface> myMax;
};
```

### Registering an Agent with the AgentManagerInterface

Agent developers are expected to provide a subclass implementation of the `AgentRegistrationInterface` class provided by MAX. Each Agent can then be registered with MAX via the `AgentManagerInterface` (Appendix A: Code 2).     

```C++
bool AgentManagerInterface::registerAgents(std::set<std::shared_ptr<multiAgentExperience::agent::AgentRegistrationInterface>> agentRegistrations);
```

Important: As of v.1.3.0 of the MAX Toolkit, the device integrator is expected to register all agents at the same time. The registerAgents() API cannot be used to register each agent independently.

```C++
auto agentManager = myMAX->getAgentManager();
auto agentA = ...;
auto agentB = ...;

std::set<AgentRegistrationInterface> agents;
agents.insert(agentA);
agents.insert(agentB);

agentManager->registerAgents(agents);
```

### Attention System

An Experience is the abstract component of a Device responsible for rendering user experiences with the devices hardware. An “Experience“ is the MAX Library’s concrete representation of an Agent’s desired user experience through the Device’s Attention System.

For more information, see the Experience Rendering section of the supplemental documentation Integrating with MAX Experiences.

### Device Initiated Activities

An Activity is a lifecycle for any non-Dialog activities (e.g., audio such as music) and the device (or any actor) should request an Activity before playing any audio which should be coordinated with other audio on the device.

To start an Activity, a request is made to the `ActivityManagerInterface`. This is a request as not all Activities will be granted and some will be denied. To make a request the  `ActivityRequestInterface` is used with `ActivityManagerInterface`. 

For more information on Activities see the supplemental documentation Integrating with MAX Activities.

### Controlling Universal Device Commands with Controls

For an overview of `Control`s and Universal Device Commands see supplemental documentation [Integrating with MAX Controls](Integrating_With_MAX_Controls.md).

Devices have more flexibility to access and invoke controls than Agents. This is to support non-voice invocation of UDCs such as through hardware buttons or other UI. Since these mechanisms will never request a Dialog from MAX they need another way to display available UDCs and take action on them. MAX Library exposes the `ControlInvokerInterface` and `ControlManagerInterface` through the `MAXInterface` to support this. The `ControlInvokerInterface` allows a device to take action on any UDC in response to a non-voice user action corresponding to the UDC. The `ControlManagerInterface` allows a `ControlObserverInterface` to be registered, which will let the device know when available Controls change, and which actor they are for. This allows the device to update the access to affordances for UDCs based on their availability, and associate them with the correct actor if necessary.

## Appendix A: Code References
### Code 0: MultiAgentExperience/Application/MAXBuilder.h
```C++
namespace multiAgentExperience {
namespace application {

class MAXBuilder {
public:

    ...
    
    std::shared_ptr<multiAgentExperience::application::MAXInterface> build();
};

}
}
```

### Code 1: MultiAgentExperience/Application/MAXInterface.h
```C++
namespace multiAgentExperience {
namespace application {

class MAXInterface {
public:
    virtual ~MAXInterface() = default;
    
    virtual std::shared_ptr<multiAgentExperience::agent::AgentManagerInterface> AgentManager() = 0;
    
    virtual std::shared_ptr<multiAgentExperience::experience::ExperienceManagerInterface> ExperienceManager() = 0;
    
    virtual std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> ActivityManager() = 0;
     
    virtual std::shared_ptr<multiAgentExperience::control::ControlManagerInterface> ControlManager() = 0;
    
    virtual std::shared_ptr<multiAgentExperience::control::ControlInvokerInterface> ControlInvoker() = 0;
     
    virtual std::shared_ptr<multiAgentExperience::device::SetupManagerInterface> SetupManager() = 0;
    
    virtual void setLogLevel(multiAgentExperience::utils::Log::Level level) = 0;
};

}
}
```

### Code 2: MultiAgentExperience/Agent/AgentManagerInterface.h
```C++
namespace multiAgentExperience {
namespace agent {

class AgentManagerInterface {
public:
    virtual bool registerAgents(
        std::set<std::shared_ptr<multiAgentExperience::agent::AgentRegistrationInterface>> agentRegistrations) = 0;
    
    virtual void deregisterAgent(
        std::shared_ptr<multiAgentExperience::agent::AgentRegistrationInterface>>) = 0;
};

}
}
```
