# Integrating an Agent with MAX Library
## Introduction
An Agent uses the Multi Agent Experience (MAX) Library v1.3.0 to collaborate with other Agents to create a cohesive experience for customers. Each part of MAX Library helps facilitate this by providing tools Agents can use to help enable a multi-agent experience. The library also surfaces multi-agent features such as client-side support for Universal Device Commands, which enable experiences that are not possible without device side inter-agent coordination. This document describes the capabilities an Agent has available through the MAX Library, as well as suggestions of what any Agent will have to consider during integration.

### Terms
Many of the concepts in this document are defined in the [VII Multi-Agent Design Guide](https://developer.amazon.com/en-US/alexa/voice-interoperability/design-guide) but also expanded upon in this document. For concepts which are explored in depth in this document, there will be a reference to the relevant section. For other terms see the [Glossary](Glossary.md).

## What is an Agent
 The [VII Multi-Agent Design Guide](https://developer.amazon.com/en-US/alexa/voice-interoperability/design-guide) defines an Agent as: the digital “person” that the customer interacts with through conversation (turn taking). However, the MAX library does not interact with this entire ‘person’. When the MAX library references an Agent, it means the device side component that implements `AgentRegistrationInterface` (see Appendix A: Code 1). Creating an Agent in this context therefore means any object which implements this interface.

The `AgentRegistrationInterface` exposes APIs to retrieve information about the agent like the agent's name and ID. It also contains an important callback API called `onReady`, which is invoked by MAX, in order to give the agents important interfaces for requesting Dialogs, Activities etc. These concepts are expanded upon in later sections.  

## Preparing for Integration
This section is about identifying the parts of your existing Agent which may be affected by integration with MAX Library. The rest of the document dives deep into how each of these integrations could be done.

As an Agent developer, it is best to think of the MAX Library as primarily a focus management library. Like any focus management, requests are made before starting an interaction to ensure other interactions are not conflicting with yours. These requests may occasionally be denied, and when granted can occasionally be interrupted before they are completed. In addition to this, the MAX Library is also used to enable specific multi-agent features. Many of these features are only available when an Agent has focus.

Which parts of your Agent will need to request focus? Any interaction which records user speech, or plays audio should be identified, and are candidates for integrating with the MAX Library. For each of these features the first choice before requesting focus is whether your interaction is a Dialog or an Activity. Dialogs are reserved for interactions between the user through speech and the Agent through its speech. All other interactions are Activities.

Using Dialogs and Activities for your features will coordinate your audio interactions with any other Agents on the same device also using MAX Library. The next step of integration is to identify which of these also require an Experience (explained further in the **Experiences** section below). When a Dialog or Activity is active for your Agent, they will have access to setting Experiences with the MAX Library. These Experiences are shared with the Device along with any other Experiences set by other Agents. The Device can then represent each Agent correctly in its Attention System.

The final set of features made available when a Dialog or Activity is active is access to Universal Device Commands (UDCs). Dialogs and Activities will give your Agent access to all UDCs available, registries to make your own controls available to others, and APIs to invoke the controls of others.

Lastly, while thinking of MAX Library as a focus management system is useful, it is not necessarily the only focus management system on your device. For the best experience, it is recommended you use MAX Library to first establish multi-agent focus, then use any other focus management system afterwards.

## Registering an Agent
Agents must be registered to use MAX APIs and be part of the multi-agent experience. To register, simply use the registration APIs in the `AgentManagerInterface`. This either must be created, or is given to you by some other partner in the multi-agent software. Typically, the Device is registering the Agents, and more detail about registration is found in the [Integrating a Device with MAX Library](Integrating_A_Device_With_MAX_Library.md) document.

The `AgentRegistrationInterface` exposes APIs to retrieve information about the agent like the agent's name and ID. It also contains an important callback API called `onReady`. This will be invoked by MAX, in order to give the agents important interfaces like `DialogManagerInterface`, `ActivityManagerInterface` etc. using which, Agents can request Dialogs and Activities. MAX provides four important interfaces in `onReady`: 
1. `ActivityManagerInterface`: A MAX Library component using which, an Agent can request Activities like music, alarms etc.
2. `DialogManagerInterface`: A MAX Library component using which, an Agent can request Dialogs.
3. `StaticExperienceManagerInterface`: A MAX Library component using which, an Agent can request Static Experiences. More details can be found in [Integrating with MAX StaticExperiences](Integrating_With_MAX_StaticExperiences.md)
4. `OnCompletionCallbackInterface`: An Agent is expected to execute this callback once it has determined that it is ready to start interacting with MAX. The usage of this callback becomes apparent in the scenario that an Agent process crashes and comes back up. In such cases, once `onReady` is invoked again, an Agent can re-request any prior Activities etc. before executing the OnCompletionCallback. MAX will wait until it receives the callback from the Agent before processing any requests in the correct priority order.

Agents will remain registered until the application terminates or the Agent is manually deregistered using `AgentManagerInterface`.

## Agent Invocation
A device may have multiple means of invoking any Agent. This can range from dedicated hardware buttons or software buttons to novel inputs specific to the device type. Each of these invocations are implemented by the application.

## MAX Library APIs
### Dialogs
A Dialog is the lifecycle of a conversation between a user and an Agent. An Agent must request a Dialog **any time the user or Agent wants to speak**. This lifecycle can be in one of three states: `LISTENING`, `THINKING`, and `SPEAKING` each of which should be handled by the Agent. Only one Dialog is allowed to be active at any time across all Agents, and there are clear rules about when it can and cannot be interrupted by new Dialog requests (see **Barge-In** section below). One important side effect of starting a Dialog is any active Activities, across all Agents, will be notified that they are in the BACKGROUND state while the user is doing a more important task. The MAX library exposes the `DialogManagerInterface` API for Agents to use Dialogs.

### Requesting a Dialog
To start a Dialog, a request is made to the `DialogManagerInterface`. This is a request because not all Dialogs will be started, some will be denied. A request for a Dialog is denied if an existing Dialog is already in `LISTENING` or `THINKING` state with your Agent or another Agent. This is to prevent any experiences where an Agent interrupts what the user is doing (more detail on how this relates to the Barge-In features is discussed next). To make a request, an implementation of  `DialogRequestInterface` (see Appendix A: Code 2 for a reference) is used with `DialogManagerInterface`. The `DialogRequestInterface` is itself a lifecycle used to track whether or not the request was denied, and if a started Dialog is still active or finished.

#### DialogRequestInterface Lifecycle
![The DialogRequestInterface Lifecycle](images/DialogRequestInterfaceLIFECYCLE.png)

For example, here is how an Example Agent both implements the `DialogRequestInterface` and uses it to request Dialogs.

#### Implementing DialogRequestInterface

UserDialogRequest.h
```C++
//...

class UserDialogRequest : public multiAgentExperience::agent::dialog::DialogRequestInterface {
//...
};

//...
```
UserDialogRequest.cpp
```C++
//...
void UserDialogRequest::onDenied(const std::string& denialMessage) {
    /*
     * Example Agent has nothing to clean up here, but your Agent may
     * need to do so.
     */
}

void UserDialogRequest::onDialogStarted(std::shared_ptr<DialogControllerInterface> controller) {
    /*
     * The dialog is started, and since it is a 'user' initiated
     * Dialog request,
     * we immediately start listening.
     */
    controller->startListening();
}

void UserDialogRequest::onError(const std::string& errorMessage) {
    /*
     * Errors give messages to help understand what happened when
     * something is wrong with the Dialog or request. None of these
     * errors are recoverable, the message is included to help with
     * debugging.
     */
}

void UserDialogRequest::onDialogStopped() {
    /*
     * Example Agent has nothing to clean up here, but your Agent may
     * need to do so.
     */
}

multiAgentExperience::dialog::DialogBargeInPriority UserDialogRequest::getDialogBargeInPriority() const {
    /*
     * Example Agent uses DialogBargeInPriority::NORMAL for all Dialogs. Your agent may decide to mark critical Dialogs
     * with DialogBargeInPriority::HIGH, to take advantage of Dialog barge-in, based on the respective policies set via 
     * the MAXBuilder.
     */
    return multiAgentExperience::dialog::DialogBargeInPriority::NORMAL;
}
//...
```
ExampleAgent.cpp
```C++
//...
void ExampleAgent::requestDialog() {
    auto userDialogRequest = std::make_shared<UserDialogRequest>();
    m_dialogManager->request(userDialogRequest);
}
//...
```

Once the `DialogRequestInterface` is `DENIED` or `FINISHED`, the request is done and must not be reused.


### Controlling a Started Dialog
After a Dialog is started it can transition between the `LISTENING`, `THINKING` and `SPEAKING` states of the Dialog. To transition to these states MAX provides a `DialogControllerInterface` (see Appendix A: Code 3). The first transition happens in response to `DialogRequestInterface::onDialogStarted`, which provides a `DialogControllerInterface` for the new Dialog. Each state is handled by a Dialog State Handler, which is also given the same `DialogControllerInterface` to continue controlling the current Dialog (Dialog State Handlers are expanded on next). This controller contains all APIs for changing the state of a Dialog as well as some other related Dialog features. The Dialog lifecycle which can be used with this controller is as follows:

![The DialogRequestInterface Started](images/DialogRequestInterfaceSTARTED.png)

### Dialog State Handlers
 By default there is nothing which handles Dialog states. Transitioning to any state without a previously registered handler will result in an error in `DialogRequestInterface` and the Dialog will be finished. Therefore the Agent must register a handler for the states it will use in a Dialog. There are handlers for each state: `ListeningHandlerInterface`, `ThinkingHandlerInterface`, and `SpeakingHandlerInterface`. In addition to the above state handlers, `ControlReceiverInterface` is provided to obtain the set of available `ControlType`s during a dialog. These are each set using the `DialogManagerInterface`.

### Registering Handlers
There are two recommended models for registering the handlers: once for all Dialogs or once per started Dialog (a combination of these approaches is also possible). The ‘right’ way to do so will be up to the Agent using the handlers & Control Receiver.

Either way the **registration** of the handlers requires a `DialogManagerInterface` and the handlers you are registering. For example:

```C++
// Registration
dialogManager->setControlReceiver(controlReceiver);
dialogManager->setListeningHandler(listeningHandler);
dialogManager->setThinkingHandler(thinkingHandler);
dialogManager->setSpeakingHandler(speakingHandler);

// or
dialogManager->setAllHandlers(
    controlReceiver,
    listeningHandler,
    thinkingHandler,
    speakingHandler);
```

Handlers are **deregistered** similarly:
```C++
// Deregistration
dialogManager->removeControlReceiver();
dialogManager->removeListeningHandler();
dialogManager->removeThinkingHandler();
dialogManager->removeSpeakingHandler();

// or
dialogManager->removeAllHandlers();
```

Registering handlers once should happen during registration of the Agent with the MAX library (see **Registering an Agent** above). Minimally they must be registered before a Dialog is requested. It is safe to set these once because MAX library will only activate a single Dialog at a time and therefore each handler will only need to handle one Dialog at a time.

Registering handlers for each Dialog should happen in the `onDialogStarted` callback of the `DialogRequestInterface`. Again because MAX library will only activate one Dialog at a time, it is safe to set handlers in `onDialogStarted` with the confidence that any other Dialog is already stopped. Likewise if you are removing handlers, it is necessary to do this before or within `onDialogStopped` or risk removing your next Dialog’s handlers.

### LISTENING state
`ControlReceiver` is used obtain available set of `ControlType`s during a dialog(see **Controls** section below for more detail on `Control` and `ControlType`), just before LISTENING. This is the only way to get this set of `ControlType`s for recognizing Universal Device Command requests from user (see the **Multi-Agent Features, Universal Device Commands** section for more detail).

`ListeningHandlerInterface` is used to handle `LISTENING` state. In this state an Agent should be recording a user's speech for recognition by the Agents voice recognition components. It should start the listening state as soon as it starts reading or recording user speech, and transition to the next state as soon as it stops. `LISTENING` state has two special features as well:

* Transitioning to `LISTENING` state will add the "listening" Experience (explained further in the **Experiences** section below) for your Agent automatically, showing the user that your Agent is actively listening to them.
* `ListeningHandlerInterface.onStartListening` is also given a `DialogControllerInterface`. This can be used by an Agent to take action on the current Dialog, like transitioning it to a new state etc.

### THINKING state

`ThinkingHandlerInterface` is used to handle the `THINKING` state. This state is meant to represent any and all states where the Agent is 'processing' a request. Typically, processing means the state where any network calls are made to services to recognize voice requests. However, processing can extend to any process your Agent takes which delays a `SPEAKING` or `LISTENING` state of the Dialog. It is also possible this state does not apply to your Agent, and is entirely optional. There are special features when in `THINKING` as well:

* Transitioning to `THINKING` state will add the "thinking" Experience (explained further in the **Experiences** section below) for your Agent automatically, showing the user that your Agent is actively working for them.
* `ThinkingHandlerInterface.onStartThinking` is also given a `DialogControllerInterface`. This can be used by an Agent to take action on the current Dialog, like transitioning it to a new state etc.

### SPEAKING state

`SpeakingHandlerInterface` is used to handle the `SPEAKING` state. This state is meant to represent any and all experiences where the Agent is responding to the customer with their voice in some way. The restrictions on this state are less restrictive than the others. However, the state should still be reserved for experiences which are part of your Agent's response. Playing any content which is not your Agent is more likely better represented as an Activity (see the **Activities** section below). Speaking has several special features:

* `SpeakingHandlerInterface.onStartSpeaking` is given a `DialogControllerInterface`. This can be used by an Agent to take action on the current Dialog, like transitioning it to a new state etc.
* `SpeakingHandlerInterface.onStartSpeaking` is also given a `ControlRegistryInterface`. This is used to register `Control`s which impact the response. This use case is described further in the **Universal Device Commands, Registering with a Dialog** use case section.

### Barge-In

Aligned with the “Barge-In” guidance from the VII Design Guide, Dialogs must be only intermittently interruptible. This means in a `LISTENING` or `THINKING` state a user cannot interrupt a Dialog. This is to prevent a user from accidentally cancelling a request they just made, or otherwise cutting off a response which was about to be delivered. In `SPEAKING` state Dialogs are interruptible. However, this is conditional on the DialogBargeInPriority of the interrupting Dialog and also the barge-in policy set by the device integrator.

Barge-In has been commonly confused with other features. Notice that Barge-In only applies to Dialogs, and is only enabled on `SPEAKING` Dialogs. When an Agent is playing non-Dialog audio (e.g. through an Activity, see **Activities** section) and a Dialog for any Agent starts, this is not Barge-In. The new Dialog does become the primary user experience over the other content, and the other content is allowed to resume as the primary experience after the Dialog completes, but this is part of an entirely different feature. It is part of what Activities enables, and is instead referred to as the original content being 'backgrounded' or 'attenuated'.

False Barge-Ins (where one Agent invokes another Agent by speaking its wake word) should be prevented in order to maintain the customer experience. Device hardware and software solutions can be built to either recognize when a wake word is about to be played as output, to eliminate the output from the recorded input, or otherwise mitigating these issues.

Any agent that is requesting a Dialog, may specify a `DialogBargeInPriority`. This `DialogBargeInPriority` is an enum whose values can be `HIGH` or `NORMAL`. If an agent deems a Dialog to be critical (and hence requires barge-in), it may specify the DialogBargeInPriority as HIGH. Such dialogs are allowed to interrupt the ongoing dialog regardless of the state it is in. Refer to Appendix B Diagram 1 to understand how MAX grants/denies different kinds of barge-ins. 

When an agent attempts to interrupt its own Dialog, this barge-in is termed as same-agent barge-in. A cross-agent barge-in is used to describe the scenario when the ongoing dialog is interrupted by another agent. The device integrator can choose to either allow or disallow these types of barge-ins by setting the appropriate policies via the MAXBuilder. As of v1.3.0, two such policies are available - the HighPriorityCrossAgentBargeInPolicy and the NormalPriorityCrossAgentBargeInPolicy. These define whether cross-agent barge-ins are allowed for Dialogs with DialogBargeInPriority set as HIGH/NORMAL respectively.


### Activities

An Activity is a lifecycle for any non-Dialog activities (e.g., audio such as music) from an Agent or Device (referred to generally as an ‘actor’), and an actor should request an Activity before playing any audio which should be coordinated with other audio on the device.

For more information, see the supplemental documentation [Integrating with MAX Activities](Integrating_With_MAX_Activities.md)

### Controls

    A `Control` is an action with a `ControlType` matching a supported Universal Device Command (UDC) on the device. `Control`s are used to:

* Register actions for other Agents to access for UDCs
* Invoked when a user request is recognized as a UDC request

They also contain the only data shared from MAX Library to other Agents when making voice requests. Specifically the `ControlType` of all currently available `Control`s are shared with an Agent when in the `LISTENING` state of a Dialog. This set of `ControlType`s must be the only data necessary for your speech recognition to evaluate if the user request was for your Agent own features, or for your Agent to take action on an available UDC.

For more information, see the supplemental documentation [Integrating with MAX Controls](Integrating_With_MAX_Controls.md)

### Experiences

An Experience (a.k.a an Active Experience) is a representation of the state of an Actor which is shared with the Device. A person being in a call with another person is an example of an Experience. The Device, with support from the Actor, chooses how to render these Experiences (e.g. activating or changing an LED ring color). When one or more Agents have multiple Experiences at the same time, the Device also chooses how to represent them together. There is a lot of flexibility on what these Experiences are for each Agent and how the Device decides to render them.

For more information, see the supplemental documentation [Integrating with MAX Experiences](Integrating_With_MAX_Experiences.md).

### Static Experiences

Any experience provided by an agent, which is not tied to any activity or a dialog, is termed as a Static Experience. For example, a Visual Experience that indicates to the user of a pending notification, can be a candidate for a Static Experience.

For more information, see the supplemental documentation [Integrating with MAX Static Experiences](Integrating_With_MAX_StaticExperiences.md).


## Multi-Agent Features

### Coordinated Experiences

The specifications of the MAX Library APIs allows MAX to take care of the relative co-ordination of multi-agent experiences without requiring Agents be aware of each other. This includes audio experiences and some visual experiences (specifically the Attention System of the Agent). When Agents follow the guidance around MAX library Dialogs and Activities, audio of different types from different Agents will be able to be played together without ruining each others experiences for the customer. This coordination is the core multi-agent feature MAX relies on to enable the others.

### Universal Device Commands

The Multi-Agent Design Guide (MADG) defines Universal Device Commands (UDCs) as: those 'commands' and 'controls' that a customer may use with any compatible agent to control certain device functions, even if the agent was not used to initiate the experience. Like other parts of the MADG, the MAX Library does not interact with every part of UDCs. Specifically, it interacts only with the Device side features of registering and invoking 'controls', and has no part in recognizing the 'commands' given by users to invoke the controls. Both Agents and Devices (referred to generally as ‘actors’) can both register and invoke UDCs.

For more information, see section 2 (Universal Device Commands) of the supplemental documentation [Integrating with MAX Controls](Integrating_With_MAX_Controls.md)

## Notes on Threading Model

All inbound calls to MAX Interfaces APIs are thread safe. All outbound calls to callbacks registered with MAX Library components are not guaranteed to be called from any specific thread. For this reason any implementations of MAX Interface types should ensure they may be safely called from any thread.

## Appendix A: Code References
### Code 1: Agent
```C++
#include <MultiAgentExperience/Agent/AgentRegistrationInterface.h>

namespace multiAgentExperience {
namespace agent {

class ExampleAgentRegistration : public multiAgentExperience::agent::AgentRegistrationInterface {
public:
    ExampleAgentRegistration(...);
    ~ExampleAgentRegistration();
    
    void onReady(
        std::shared_ptr<multiAgentExperience::common::OnCompletionCallbackInterface> onCompletionCallback,
        std::shared_ptr<multiAgentExperience::activity::ActivityManagerInterface> activityManager,
        std::shared_ptr<multiAgentExperience::dialog::DialogManagerInterface> dialogManager,
        std::shared_ptr<multiAgentExperience::experience::StaticExperienceManagerInterface> staticExperienceManager) override;
    
    actor::ActorId getId() override;
    std::string getName() override;
};

}
}
```

### Code 2: DialogRequestInterface

```C++
namespace multiAgentExperience {
namespace dialog {

/**
 * DialogRequestInterface contains callbacks for a dialog request's lifecycle. Each request is either denied or started,
 * and any request which is started is also stopped. Following these lifecycle callbacks allows Agents to interact with
 * any other multi-agent experiences.
 */
class DialogRequestInterface {
public:

    /**
     * Destructor.
     */
    virtual ~DialogRequestInterface() = default;

    /**
     * The request to start a dialog was denied. A denied request is not recoverable and should be dropped.
     *
     * @param denialMessage - A message explaining the cause of denial.
     */
    virtual void onDenied(const std::string& denialMessage) = 0;

    /**
     * The request to start a dialog succeeded and the dialog is started. The provided DialogControllerInterface can
     * be used to control the state of the dialog.
     *
     * @param controller - The controller for this dialog.
     */
    virtual void onDialogStarted(std::shared_ptr<DialogControllerInterface> controller) = 0;

    /**
     * There was an error during the lifecycle of the dialog.
     *
     * @param errorMessage - A message explaining the cause of the error.
     */
    virtual void onError(const std::string& errorMessage) = 0;

    /**
     * A previously started dialog was stopped. This is called whether or not the dialog was stopped by the Agent which
     * requested the dialog, or some other multi-agent experience interrupted it. All registered Universal Device
     * Commands, Experiences, or other multi-agent features associated with the dialog will be automatically cleaned up.
     */
    virtual void onDialogStopped() = 0;

    /**
     * @return The barge-in priority of the requested dialog.
     */
    virtual DialogBargeInPriority getDialogBargeInPriority() const = 0;
};

}  // namespace dialog
}  // namespace multiAgentExperience
```
### Code 3: DialogControllerInterface

```C++
namespace multiAgentExperience {
namespace dialog {

/**
 * DialogControllerInterface is used to take action on the current dialog. This includes starting different dialog
 * states, stopping the dialog, and invoking Universal Device Commands during some state changes.
 * A DialogControllerInterface is no longer usable after it is stopped.
 */
class DialogControllerInterface {
public:
    /**
     * Destructor.
     */
    virtual ~DialogControllerInterface() = default;

    /**
     * Starts the LISTENING state of the dialog.
     */
    virtual void startListening() = 0;

    /**
     * Starts the THINKING state of the dialog.
     */
    virtual void startThinking() = 0;

    /**
     * Starts the SPEAKING state of the dialog.
     */
    virtual void startSpeaking() = 0;

    /**
     * Invokes a Universal Device Command (if it is valid) before starting SPEAKING.
     *
     * @param controlType - The type of Universal Device Command to invoke. If it is not a control which is available
     *                      then the invocation does nothing but SPEAKING is still started.
     */
    virtual void invokeControlAndStartSpeaking(const multiAgentExperience::control::ControlType& controlType) = 0;

    /**
     * Stops the dialog immediately. Once stopped the DialogControllerInterface cannot be used to enter any other dialog
     * state.
     */
    virtual void stop() = 0;

    /**
     * Stops the dialog immediately and then invokes a Universal Device Command (if it is valid).  Once stopped the
     * DialogControllerInterface cannot be used to enter any other dialog state.
     *
     * @param controlType - The type of Universal Device Command to invoke. If it is not a control which is available
     *                      then the invocation does nothing but SPEAKING is still started.
     */
    virtual void stopAndInvokeControl(const multiAgentExperience::control::ControlType& controlType) = 0;
};

}  // namespace dialog
}  // namespace multiAgentExperience
```

## Appendix B: Barge-In Sequence Diagrams

Everything which looks like a function call maps to an existing function either implemented by an Agent implementation or the MAX Library. Any other text is generally describing what task needs to be implemented by an Agent. The sequence shown is only one example, and may differ from your Agent’s logic.

### Diagram 1: Barge-In Usecases
This table describes all the different barge-in scenarios. It is assumed the `HighPriorityCrossAgentBargeInPolicy` is `SUPPORTED`, while the `NormalPriorityCrossAgentBargeInPolicy` is `NOT_SUPPORTED`.

![Barge-in Usecases](images/BargeInUsecases.png)

### Diagram 2: Successful Barge-In

 Use case: The user asks one Agent (AgentA) for the weather, but realizes they may be running late and asks the other Agent (Agent B) how much time they have, interrupting the weather report.

![Successful Barge-in](images/SuccessfulBargeIn.png)

Note: The two Agents do not have precisely the same internal sequence flow. This is to showcase some of the flexibility an Agent has in implementation. Specifically:

* Agent A has a different implementation for each state handler: `ListeningHandlerInterface`, `ThinkingHandlerInterface`, and `SpeakingHandlerInterface`. Agent B on the other hand has a single component handling each state lifecycle.
* Additionally, Agent A can recognize the end of speech during voice recognition, and uses this state to enter `THINKING` state while the request finishes processing. Agent B on the other hand does not support this feature and skips the `THINKING` state entirely.

Again these are merely examples of how Agents may work, and should not be considered as particular guidance.

### Diagram 3: Denied Barge-In

![Denied Barge-in](images/DeniedBargeIn.png)
