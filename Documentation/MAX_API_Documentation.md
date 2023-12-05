# MAX-API Documentation

## Notice

This document provides an overview of material changes to the MAX APIs and their usages, post MAX Toolkit v0.4.0.

## Introduction

This document outlines all changes expected to the MAX APIs. All types are referring only to MAX types, and all namespaces are omitted for brevity. For any questions on definitions of terms not included in this document refer to the public [MAX Glossary](Glossary.md).

## Integration Changes

The MAX library will be separated into two libraries. MultiAgentExperience-API and the MultiAgentExperience implementation (library). These libraries will be available separately. Agents are expected to only require a dependency on MultiAgentExperience-API, though MultiAgentExperience may be used for testing. Device integrators will include both dependencies.

## Refactoring / Deprecation

There are a few changes being made to rename or remove some features and change some naming to more accurately reflect the use case of some APIs. This includes:

1. Renaming `Agent.h` to `AgentRegistrationInterface.h`. Included in this change will be removing APIs currently present on `Agent.h` and not aligned with the registration lifecycle features. None of these changes are expected to cause any disruption in partner implementations outside of incremental updates:
    1. The parameter for a ‘wakeword’ will be removed from the constructor.
    2. `Agent::initializeCoreInterfaces()` will be renamed `AgentRegistrationInterface::onReady()` and will no longer store field references for all parameters. More detail on this will be included in Registration Lifecycle Changes below. The implementation shall retain references they intend to use.
    3. `AgentTransferManager` is no longer provided in `AgentRegistrationInterface::onReady()`
    4. The following APIs are removed:
        1. `AgentRegistrationInterface::getWakeword()`
        2. `AgentRegistrationInterface::onWakeWordDetected()`
        3. `AgentRegistrationInterface::onTapDetected()`
        4. `AgentRegistrationInterface::onAgentTransfer()`
        5. `AgentRegistrationInterface::handleOnWakeWordDetected()`
        6. `AgentRegistrationInterface::handleOnTapDetected()`
        7. `AgentRegistrationInterface::handleOnAgentTransfer()`
        8. `AgentRegistrationInterface::onInitialized()`
    5. The following protected fields are removed:
        1. `m_activityManager`
        2. `m_dialogManager`
        3. `m_agentTransferManager`
2. All types under `MultiAgentExperience/Audio` will be removed. This includes:
    1. `AudioFormat.h`
    2. `AudioReaderInterface.h`
3. `MultiAgentExperience/Application/WakeWordObserverInterface.h` will be removed.
4. All types under `MultiAgentExperience/Utils/Data` will be removed. This includes:
    1. `DataObserverInterface.h`
    2. `DataWriterInterface.h`

## Changes to Device Interface

### Stop All Alerts on Button Press

Devices should have an option to stop all alerts through a physical button. This facility is provided through a MAX interface added to  existing  `ControlManagerInterface`.

#### Why is this important?

Since an Alert will still sound even if the microphones have been turned off or if the product has lost its network connection, the product must afford a physical means of dismissing all sounding Alerts. Pushing the button(s) will stop any ringing alerts from any agent. Alert dismissal is its only function when an Alert is sounding.

#### Code Changes

Existing `ControlManagerInterface` is amended to include new API to support dismissal of all Alerts. This API needs to be called by the device integrator to perform the desired function.

```
class ControlManagerInterface {
public:
  ...

  virtual void stopAllAlerts() = 0;

  ...
}
```

### Enable Entering and Exiting Agent Setup Mode


Devices need to have an option to enter agent set up mode. This facility is provided through a new MAX interface `SetupManagerInterface`.


#### Why is this important?

Agent set up is optional, and users can exit the OOBE flow at any time. If only one agent is set up, users will see an option to enable the other from their dashboard. If the users choose to setup the agents later on, we need to make the sure users are not confused by alerts or notifications from one agent while trying to set up the other.

#### Code Changes

New `SetupManagerInterface` will be introduced. Currently this interface will provide ways to enter and exit the setup mode. During this, any request for dialog and activity will be restricted only to the passed actor. Also, all ongoing activities will be stopped to avoid any confusion for the user.

```
class SetupManagerInterface {
public:

  virtual void enterSetupMode(const ActorId& actorId) = 0;

  virtual void exitSetupMode() = 0;

}
```

This new interface will be made available to device application via `MAXInterface`, with following changes.

```
class MAXInterface {
public:
  ...

  virtual std::shared_ptr<SetupManagerInterface> getSetupManager() = 0;

  ...
}
```

## Registration Lifecycle Changes

When MAX will be implemented as an out of process application, the communication to MAX will be through IPC. In this use case the MAX process can go down (ex: crash) while the agents are running. On the process coming up, the agents and device should be able to communicate with MAX the current states of any active Activities or Dialogs in a way which allows these experiences to not be affected by the restart.

For this feature, there are 3 areas which will be affected are

1. Activities
2. Dialog
3. Static Experiences (e.g. DND or Pending Notifications)

To understand how the MAX as a process going down affects the above areas, consider how the experience needs to be in following use cases. The use cases are provided to get some context on the changes and its usage.

***Use Case 1*** - Agent A is playing music and MAX process goes down. Agent B starts a dialog and goes into speaking state. MAX process starts. At this point MAX will have to collect the state of the agents, instruct Agent A to take the music to background, and allow Agent B to show it is speaking.

***Use Case 2*** - Agent A is playing music and Agent B has an alert which goes off. At this point MAX will let Agent A to take the music to background and Agent B to take alert to the foreground. At this point MAX crashes and comes back again. When MAX comes back again the order of registering the activity from both agents should have minimal impact on the UX.

### Registration of Agents

When MAX goes down, restarting will require a new registration of agents by the device integrator. This means the registration APIs will be slightly modified to make it easier to register in these edge cases without impacting user experience more than required.

The only way to minimize impact the user experience is to re-request any Activities and Dialogs which were either active before MAX went down, or started before it restarted. The following changes provide a mechanism for the device and agents to re-request these features before they are all modified by the new instance of MAX. It will be the responsibility of each agent and device to recognize they have pre-existing features to re-request, and ensure the re-request does not interrupt their experience. More detail about where to ensure there are no interruptions is expanded on below.

#### Change to AgentManagerInterface

First the device integrator is expected to register the agents at the same time. Technically they are not required to, but if they do not MAX will not be able to guarantee a minimization of user impact.By registering them at the same time, we can give the agents an opportunity to re-request any activity before all these request are processed and placed in the correct state (i.e. the activities are in the right `ActivityFocus`, and the Dialog is in the active, etc).

```
class AgentManagerInterface {
...
public:
  virtual bool registerAgents(
    std::set<std::shared_ptr<AgentRegistrationInterface>>
    agentRegistrations) = 0;
...
}
```

**Addition of new registerAgent API to AgentManagerInterface**  
To facilitate re-registration of a single agent after the agent has recovered from a process crash, a new registerAgent() API is introduced in the AgentManagerInterface.

```
class AgentManagerInterface {
public:
...
    /**
     * Registers an agent with the manager, if it is not registered already.
     *
     * @param agentRegistration The agent to be registered
     * @return true On success
     * @return false On failure
     */
    virtual bool registerAgent(
        std::shared_ptr<AgentRegistrationInterface> agentRegistration) = 0;      
...        
};
```

#### Changes for the AgentRegistrationInterface

`AgentRegistrationInterface::onReady` will be called any time MAX is newly ready for to be used, which is only expected to be once per registration of the agent. Remember if MAX goes down, the device will be re-registering agents the next time MAX is brought up. The parameters include the MAX APIs ready to use (i.e. `ActivityManagerInterface` and `DialogManagerInterface`, and `StaticExperienceManagerInterface`) as well as an `OnCompletionCallbackInterface`. This callback is expected to be executed when the agent is ready. This either is immediately if there is no re-requesting of Activities or Dialogs, or it is expected to be held until those Activities and Dialogs have been re-requested. The new requests should not be waited on, just placed with the provided APIs. If the callback is not called, there will also be no impact. Once all agents have been registered, given APIs in onReady, and executed the `OnCompletionCallbackInterface`, MAX will evaluate all currently requested items and accept the ones which are still valid, placing them in the correct state. This will minimize user impact, and result in the state these features would have been in if MAX had never been down. `AgentRegistrationInterface` is now a pure virtual class.

```
class AgentRegistrationInterface {
...
public:
  virtual void onReady(
    std::shared_ptr<OnCompletionCallbackInterface> onCompletionCallback,
    std::shared_ptr<ActivityManagerInterface> activityManager,
    std::shared_ptr<DialogManagerInterface> dialogManager,
    std::shared_ptr<StaticExperienceManagerInterface> staticExperienceManager) = 0;
...
}
```

#### OnCompletionCallbackInterface

```
namespace multiAgentExperience {
namespace common {

/**
* A utility callback which can be executed in order to notify MAX of some event
* completion.
 */
class OnCompletionCallbackInterface {
public:

  /// Notifies MAX that the callback was executed.
  virtual void completed() = 0;
};

}  // namespace common
}  // namespace multiAgentExperience
```

## Changes to Utils
### Addition of a new HashableInterface
A new HashableInterface with only one method - getHash() is introduced. The HashableInterface provides a default implementation for the getHash() method which calculates a unique hash for the object.

```
namespace multiAgentExperience {
namespace utils {

/**
 * @brief The HashableInterface class defines an interface for objects that can be hashed.
 *
 * This interface provides a default implementation of the getHash() method,
 * which generates a hash value based on the memory address of the object.
 * Derived classes can override this method to provide custom hash calculation logic.
 */
class HashableInterface {
public:
    /**
     * Destructor.
     */
    virtual ~HashableInterface() = default;

    /**
     * Get the hash value of the object, based on its memory address.
     *
     * @return The hash value of the object.
     */
    virtual std::size_t getHash() const {
        return std::hash<const void*>()(static_cast<const void*>(this));
    }
};

}  // namespace utils
}  // namespace multiAgentExperience
```

The ActivityRequestInterface and the DialogRequestInterface both inherit from the HashableInterface.

```
class ActivityRequestInterface : public utils::HashableInterface {
public:

...

};
```

```
class DialogRequestInterface : public utils::HashableInterface {
public:

...

};
```

### Why was this introduced?
For activity and dialog requests, MAX calculates the hash of the request objects and stores information for that particular hash. With the introduction of the MAX IPC framework, instead of actual request objects, “proxies“ are requested to MAX. The MAX IPC framework may use multiple ”proxies” for the same  request object. By providing a custom `getHash` implementation, the IPC framework can ensure correct functionality in MAX. The corresponding code in MAX is changed to use the new `getHash` APIs.

## Changes to Dialogs

### Adding DialogBargeInPriority for use with DialogRequestInterface

#### DialogBargeInPriority.h

```
/**
* The barge-in priority of the DialogRequest.
*
* Each value has a corresponding policy in MAXPolicies which will be
* checked before allowing a barge-in
*/
enum class DialogBargeInPriority {
  HIGH,
  NORMAL,
};
```

#### DialogRequestInterface Changes

```
class DialogRequestInterface {
public:
  ...
  virtual DialogBargeInPriority getDialogBargeInPriority() const = 0;
  ...
}
```

Each `DialogRequestInterface` should return the barge-in priority for the Dialog. The request will then be evaluated based on the barge-in policy for that barge-in priority type (see Changes to MAX Factory for more information on barge-in policies).

## Changes to Activities

### Adding MixabilityType and MixingBehavior

#### MixabilityType

```
/// Provided with each Activity request to classify its requirements for mixing with
/// other Activity ouput.
enum class MixabilityType {

    /**
    * Indicates that the corresponding Activity is mixable with other channels, and
    * requires Activities in the background to attenuate their output appropriately.
    * For example such Activities may duck, pause, or reduce frequency of ouput.
    */
    MIXABLE_RESTRICTED,
    
    /// Indicates that the corresponding Activity is not mixable with other channels in
    /// any situation.
    NONMIXABLE,
    
    /// Indicates that the corresponding Activity can play without any restrictions
    /// alongside other activity output. This applies to specific Activity use cases.
    MIXABLE_UNRESTRICTED

};
```

#### MixingBehavior

```
/// Provided along with ActivityFocus, and changes whenever multiple Activity
/// requirements have impact on each others mixability.
enum class MixingBehavior {

    /**
     * Indicates that the corresponding Activity may attenuate its output instead
     * of pausing it. This may include duck volume, play less frequently,
     * or otherwise reduce output appropriately.
     */
    MUST_ATTENUATE,

    /// Indicates that the corresponding Activity must pause or stop output.
    MUST_PAUSE,
    
    /// Indicates there are no restrictions on output.
    UNRESTRICTED
};
```



A value from the new `MixabilityType` enum will be provided along with each `ActivityRequestInterface`. This will be used when determining a `MixingBehavior` to use in the background when active at the same time as other Activities with their own `MixabilityTypes`. The `MixingBehavior` for an Activity is determined by MAX, and relayed back to the Agent via the `ActivityHandlerInterface::onFocusStateChange()` API.


#### Current State

Currently an Activity can be in the background, but is not shared any other metadata about how it should behave while in the background.


##### Why is this important?

When a feature requires either different behavior in the background for itself, or other activities currently active. For example, media for an audio book may always want to pause in the background. It should use a `MixabilityType::NONMIXABLE`. Music on the other hand may use `MixabilityType::MIXABLE_RESTRICTED`. When an Alert goes off, the `MixingBehavior` for the audio book would be `MUST_PAUSE`, and the music would be `MAY_DUCK`.

***Another example:*** music may be active with `MixabilityType::MIXABLE_RESTRICTED`. It may be mixable, but if a call starts by an agent, and a `COMMUNICATIONS` Activity is requested with `MixabilityType::NONMIXABLE`, the music will be put in the background and given a `MixingBehavior::MUST_PAUSE` to respect the higher priority Activity’s requirements.

All Activities in the Foreground will be given `MixingBehavior::UNRESTRICTED`. There are a few edge cases discussed in this document (i.e. notifications and one option for media alarms) where an activity in the background may also receive `MixingBehavior::UNRESTRICTED`.


##### Code Changes

```
class ActivityRequestInterface {
public:
    ...
    ActivityRequestInterface(
        ActivityType activityType,
        MixabilityType mixabilityType, // New
        ActivityHandlerInterface handler) :
    ...
```

`ActivityHandlerInterface` lifecycle is updated slightly as well with these changes. In the current version `onReady` is called with the starting `ActivityFocus`, and `onFocusStateChanged` is also called immediately afterwards. This is not ideal, and we are moving `onReady` to `onGranted` to match the `onDenied` callback, and using to only deliver the dependencies required for the Activity. `ActivityHandlerInterface::onFocusStateChanged` will still be called immediately afterwards to deliver the `ActivityFocus` and `MixingBehavior`, as well as any time either of these values change.

```
class ActivityHandlerInterface {
public:
    ...
    virtual void onGranted(
        ActivityControllerInterface activityController,
        ControlRegistryInterface controlRegistry,
        ExperienceControllerInterface experienceControl = 0;
    
    virtual void onFocusStateChange(
        ActivityFocus focus,
        MixingBehavior behavior // New
    ) = 0;
    ...
```


### Adding ActivityType::NOTIFICATIONS

A new `ActivityType::NOTIFICATIONS` is introduced,  which is lower priority than `ALERTS` and higher than `CONTENT`. It is expected to be used for short audio experiences which notify the customer to take action. For example, an agent may detect severe weather events in the area and send a notification to the customer’s device to play a ‘chime’ sound and display a CX for the pending notification. When the agent is asked for the pending notifications via a Dialog with the customer, they are told of details of the event and the notification is cleared. Only the ‘chime’ sound will be using the `NOTIFICATIONS` Activity.

#### Why is this important?

Currently there is no support for scheduling a notification after a Dialog. While some existing features could approximate the required CX, they would have side effects. Instead we intend to support the required CX directly.

#### Code Changes

Code snippet for the `ActivityType` class

```
enum class ActivityType {
    /// Communication activities should be used for user communication, such as a
    /// call.
    COMMUNICATION,
    /// Alerts activities should be used for immediate notification of the user,
    /// such as a timer or alarm.
    ALERTS,
    /// Notifications activities should be used for short audio experiences which
    /// notify the customer to take action.
    NOTIFICATIONS,
    /// Content activities should be used for any long form audio which may or may
    /// not have an end, such as music.
    CONTENT
};
```

#### MixabilityType for Notifications

The `MixabilityType` for `NOTIFICATIONS` Activities will be `MIXABLE_UNRESTRICTED`. This will result in some edge cases where a `CONTENT` Activity will be in the `BACKGROUND` but have `MixingBehavior::UNRESTRICTED`. This is expected, and can be implemented to play at full volume while `UNRESTRICTED`, or optionally can still duck if that is what the agent prefers.


### Adding support for Simultaneous Activities

Simultaneous activities of the same type can now be scheduled by MAX. A corresponding scheduling policy for each activity type is added to `MAXPolicies.h`. The policy allows for simultaneous activities to either replace an ongoing activity or stack on top of an ongoing activity.

#### Why is this important?

Currently, the default activity behavior is to allow only a single activity of a particular type to be active at once. This means that any simultaneous activity across agents will always be stopped. Consider the use case of multiple simultaneous alerts (like timers, alarms, and reminders). If these alerts become active at the same time, each new activity will replace the older one. Hence, by adding an option to stack these activities, MAX will handle each requested activity until it is stopped by the user/agent.

### Making methods virtual in ActivityRequestInterface
All methods in the ActivityRequestInterface are made virtual.

```
class ActivityRequestInterface : public utils::HashableInterface {
public:
    ...

    /**
     * Destructor.
     */
    virtual ~ActivityRequestInterface() = default;

    /**
     * @return The type of the requested activity.
     */
    virtual ActivityType getType() const {
        return m_activityType;
    }

    /**
     * @return The handler for the requested activity.
     */
    virtual std::shared_ptr<ActivityHandlerInterface> getHandler() const {
        return m_handler;
    }

    /**
     * @return The MixabilityType for the requested activity.
     */
    virtual MixabilityType getMixabilityType() const {
        return m_mixabilityType;
    }
```

## Changes to Controls

### Adding new ControlReceiverInterface

Controls need to be collected before the start of Listening state and after Dialog request. This interface can be used to collect ControlType definitively before the start of listening state.

#### Current State

Currently, `ControlType` is coupled with `ListeningHandlerInterface::onStartListening`. Right now, there is a need to send Controls along with `onStartListening`, which means set of Controls are necessary to be collected in listening state. This has proven to be burdensome in some implementations.

#### Why is this important?

Decoupling delivery of shared active Controls from the handler for listening state gives flexibility to agents to implement their Dialog lifecycle correctly, while still only sharing this state at the right time. Additionally it allows the agent to choose when not to receive this data (by simply not registering the listener) but still use Dialog features. A callback is given along with the API of this interface to let MAX know that processing of ControlTypes is completed.

#### Code Change

##### ControlReceiverInterface

```
class ControlReceiverInterface {
public:
    virtual void onControlsReceived(
        std::shared_ptr<StartListeningCallback> startListeningCallback,
        std::set<ControlType> controls) = 0;
```

Along with this new interface, there needs to be a way to inject and remove this object from MAX. These changes will be part of already existing `DialogManagerInterface`.

```
class DialogManagerInterface {
public:
...

    virtual void setControlReceiver(
        std::shared_ptr<ControlReceiverInterface> controlReceiver) = 0;
        
    virtual void removeControlReceiver() = 0;

    virtual void setAllHandlers(
        std::shared_ptr<ControlReceiverInterface> controlReceiver,
        std::shared_ptr<ListeningHandlerInterface> listeningHandler,
        std::shared_ptr<ThinkingHandlerInterface> thinkingHandler,
        std::shared_ptr<SpeakingHandlerInterface> speakingHandler) = 0;
...
```

Since we have a dedicated interface for collecting Controls, we can decouple it from `ListeningHandlerInterface`. The changes will look something like below.

```
class ListeningHandlerInterface {
public:
...
        
    virtual void onStartListening(
        std::shared_ptr<DialogControllerInterface> controller) = 0;

...
```

##### StartListeningCallback
The `StartListeningCallback` is now executed via the `startListening()` method. This is a breaking change in Release 1.3.0.

```
class StartListeningCallback{
public:
...
    
    void startListening() {
        ...
    }
};
```

Example code snippet for execution of the StartListeningCallback.

```
startListeningCallback->startListening();
```

##### Making the method virtual in StartListeningCallback
The StartListeningCallback::startListening method is made virtual.
```
class StartListeningCallback{
public:
    ...
    
    virtual void startListening() {
        ...
    }
};
```

## Changes to MAXFactory

The parameters required to create a `MAXInterface` by the device integrator is growing, with some potentially optional parameters. For example the device integrator may specify the policies which enable/disable different kinds of Barge-Ins (cross-agent, same-agent). To make this easier to provision correctly and clearly, the MAXFactory will be replaced by a `MAXBuilder` with clearer documentation on how to build the `MAXInterface`. The device integrator may set any of the policies mentioned in `MAXPolicies.h`, while building the `MAXInterface`.

### Why is this important?

Ease of creating a `MAXInterface` provisioned correctly for the product is essential.


### MAXPolicies.h

```
/// Cross-agent barge-in policy for Dialogs with DialogBargeInPriority::HIGH.
enum class HighPriorityCrossAgentBargeInPolicy { SUPPORTED, NOT_SUPPORTED };

/// Cross-agent barge-in policy for Dialogs with DialogBargeInPriority::NORMAL
enum class NormalPriorityCrossAgentBargeInPolicy { SUPPORTED, NOT_SUPPORTED };

/**
* Policy for scheduling simultaneous activities of a particular activity type
*/
enum class ActivitySchedulingPolicy {
  /// Simultaneous activities will stack. A new activity will put any ongoing
  /// activity of the same type in the BACKGROUND. The new activity is moved
  /// to the FOREGROUND. On its completion, the most recent BACKGROUND activity
  /// is moved back to the FOREGROUND. The maximum number of activities that may
  /// be stacked is 100.
  STACK,

  /// Simultaneous activities will replace the ongoing activity
  REPLACE
};
```

#### Sample Code to build the MAXInterface

```
MAXBuilder builder;
auto max = builder
  .withNormalPriorityCrossAgentBargeIn(NOT_SUPPORTED)
  .withHighPriorityCrossAgentBargeIn(SUPPORTED)
  .build();
```

## Changes to Experiences

### Addition of a new StaticExperienceManagerInterface

Certain Experiences provided by an agent such as DND & Pending Notifications are not tied to any activity or a dialog. Hence this new interface is required to enable agents to deliver these static Experiences to the device. These Experiences will always be lower priority than Experiences associated with Activities and Dialogs, and will be communicated to the device integrator in this priority order.

#### Current State

In the current state all experiences are delivered through MAX’s `ExperienceManagerInterface` through the use of an `ExperienceControllerInterface`. The device application’s experience renderers register observers with MAX’s `ExperienceManagerInterface` and hence get notified about any changes to experiences which they can render on the device. `ExperienceControllerInterface`s are made available to agents when they have an active Activity or Dialog, but not outside of those lifecycle elements.

#### Why is this important?

In the current state all experiences are tied to Dialogs and Activities. Experiences like DND & Pending Notifications are inherently static experiences associated and offered by a specific agent. Hence an implementation of `StaticExperienceManagerInterface` is required that decouples the delivery of static experiences from Dialogs and Activities.

#### Code Changes

The `StaticExperienceManagerInterface` is added, and will be provided as part of the `AgentRegistrationInterface::onReady` parameter list. 
***A reminder:*** this is all a preview of what may be actually designed.

```
class StaticExperienceManagerInterface {
public:
  virtual void addExperience(
    const ExperienceId& experience,
    int relativeStaticPriority) = 0;
  virtual void removeExperience(const ExperienceId& experience) = 0;

  virtual void removeAllExperiences() = 0;
}
```

The use of these APIs is left extremely flexible. Any value for `ExperienceId` will be valid except for “listening”, “thinking”, and “speaking”. The `relativeStaticPriority` is also only roughly defined. The priority is owned by the agent, and the values are expected to be worked out per product with partners to ensure the resulting CX matches the PRD. For example Alexa intends a Pending Notification to be higher priority than a DND static Experience. This means a lower integer value should be provided for a PendingNotification than DND. If there were static Experiences between agents on the same device, the device integrator would ensure the values were correctly set to represent the priority between them as well.

The priority of all static Experiences is lower than any Activity or Dialog Experience.

The priority is still communicated to the device integrator through the ordering of the vector given in `ExperienceObserverInterface::onExperienceChange()`. 
