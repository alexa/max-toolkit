# Integrating with MAX Experiences

## Experiences

An Experience is a representation of the state of an Actor which is shared with the Device. A person being in a call with another person is an example of an Experience. The Device, with support from the Actor, chooses how to render these Experiences (e.g. activating or changing an LED ring color). When one or more Agents have multiple Experiences at the same time, the Device also chooses how to represent them together. There is a lot of flexibility on what these Experiences are for each Agent and how the Device decides to render them.

An `ExperienceControllerInterface` is used to set active ExperienceIdentifiers. Like access to other MAX Library APIs, an `ExperienceControllerInterface` is only available to Actors through an active Dialog or Activity. Each `ExperienceControllerInterface` can be used to start and end a single Experience at a time.

Agents and the Device are expected to share the enumeration of ExperienceIdentifiers that will be used for the Actor. Each identifier takes a string, and can be any non-empty value. There are well known identifiers, namely ‘listening’, ‘thinking’, and ‘speaking’ (see Experiences and Dialogs section for more detail on these well known values). The Device should determine how it will render each defined Experience for each Agent. How the Device does this is covered in detail in the Experience Rendering section. The Agents responsibility is merely to start and end the right Experiences when shown to the user.

### Experiences and Activities

When an `ActivityHandlerInterface::onReady` is called, it is given an `ExperienceControllerInterface`. Any number of Experiences may be started and ended with the controller until the onStop callback is called for the Activity. Like other APIs bound to an Activity lifecycle, the controller may only be used to start Experiences for the associated Activity. In addition when the Activity is stopped, any Experiences started through the controller will be automatically ended.

### Experience and Dialogs

Dialogs are a special case for Experiences because they automatically start and end Experiences in LISTENING and THINKING state. This is done to strongly enforce the Multi-Agent Design Guide suggesting these states should minimally be shown to customers. During these states the Dialog is not given an `ExperienceControllerInterface`, and instead the well known `ExperienceIdentifier::LISTENING` and `ExperienceIdentifier::THINKING` are started automatically.

SPEAKING state has no restriction, and `SpeechHandlerInterface::onStartSpeaking` will be started with the previous experience active. For example if the Dialog was in LISTENING, SPEAKING will start with `ExperienceIdentifier::LISTENING` active (if the Dialog is started in SPEAKING there will be no Experience set). Leaving the Experiences started is important, it ensures the transition between the previous Experience and any Experience you want to set in SPEAKING has no gap between them. If there is a latency gap there may be a brief moment when a lower priority Experience will be incorrectly exposed which can cause customer confusion. MAX does not start `ExperienceIdentifier::SPEAKING` for the SPEAKING state automatically, as much more flexibility on different types or responses are expected for Agents (for example maybe you want a different experience when speaking the news than when answering a question). If your Agent does not have multiple types of responses, using the well known `ExperienceIdentifier::SPEAKING` is recommended, but also not required.

Since the `ExperienceControllerInterface` is bound to the Dialog, any Experience started will automatically be ended when the Dialog is finished.

### Handling Multiple Simultaneous Experiences

Since a Dialog and multiple Activities are possibly active at any time, there may be multiple Experiences active at the same time as well. The Device is responsible for rendering the Experiences correctly in these cases. However what can an Agent expect for their Experiences in this use case? All active Experiences are always given to the Device for rendering. However they may not be able to render all of them given their Devices UX. The Device is required to render the primary Experience for the customer, and can optionally render the remaining Experiences in some way. The ‘primary’ Experience is determined the same way for Experiences as it is for Dialogs, Activities, and Controls. An Experience started for a Dialog is the highest priority, then an experience for a COMMUNICATION Activity is higher than an ALERTS Activity, which in turn, is higher than a CONTENT Activity.

 
## Experience Rendering
The Attention System is the abstract component of a Device responsible for rendering user experiences with the devices hardware. An “Experience“ is the MAX Library’s concrete representation of an Actor’s desired user experience through the Device’s Attention system.

The MAX Library makes no assumptions about what Experiences an Actor may wish to render to the user or how a device will choose to render a particular Experience.

The VII Multi Agent Design Guide asserts that the each Agent should publish at least the following three experiences: 
* Agent Listening - The user should be made aware whenever an Agent is recording and transmitting audio data. If active, a listening Experience will always be the highest priority experience for a Device to render.
* Agent Thinking - Whenever an Agent is processing a request, the device should render a thinking experience to the user to indicate that the request was heard.
* Agent Speaking - Whenever an Agent is speaking, the user experience of the device should make it clear which Agent is speaking.

### Agent Device Coordination

It is up to the Device manufacturer and Agent developers to coordinate which Agent User Experiences should be available, and how best to render them given a particular device’s hardware capabilities.

#### Implementing an Experience Observer

The device application component responsible for managing the device attention system should implement the ExperienceObserverInterface interface (Appendix B: Code 1).  This interface declares a callback void onExperienceChange(const std::vector<Experience>& experiences) which will be called by the MAX Library whenever the list of active experiences change. The MAX Library handles gathering all Agent user experience requests and provides the list of active Experiences in priority order, where the first Experience in the list is highest priority and must be rendered if the device is has the capability to do so, and any subsequent experiences in the list may be rendered if the Device UX Capabilities allow it. For example, the first experience in the list might be an Agent Speaking experience, which should be rendered if possible, and the second experience might be a “music playing” experience which is optional to be rendered if the device is capable. Agent Listening and Speaking experiences will always be the highest priority experiences presented, and are the most important for the device to render.

The Experience objects (Appendix B: Code 0) in the active experience list are made up of three parts:
1. The Actor identifier – identifies the source of the experience and uniquely identifies either an agent or the device application.
1. The Experience identifier - identifies an experience that is unique among all other experiences provided by that actor. Some identifiers are common such as the ‘listening’ and ‘thinking’ experiences (defined as common experiences in MultiAgentExperience/Experience/ExperienceIdentifier.h) which are required for agent’s to publish during dialogs. An actor may also define and publish any number of custom experiences, it is up to the device application and the Agent implementation to coordinate which experiences will published and what sort of UX the device will render.
1. The Session identifier – identifies the session which produced this experience. Only one experience can be active per session at a time, and recognizing when a session experience is replaced, or all experiences for the session are removed, give opportunities for the device application to also represent transition between experiences.

Important: The device application should return quickly from the onExperienceChange callback. Any long running or blocking function calls should be passed off to a different thread to allow the MAX Library to unblock. The callback may also be called from an arbitrary thread, do not assume it is called from the same thread that instantiated the MAX components.

Once the device application Experience Observer is implemented, device Attention System testing can be performed without any input from the Max Library or a real Agent. Simply call onExperienceChanged in your test routines to verify the correct attention state is being rendered.

### Registering the Experience Observer
In order for the MAX Library to call the Experience Observer onExperienceChange callback, the Experience Observer implementation must be registered with the ExperienceManagerInterface (Appendix B: Code 2) that is accessible as part of of the MAXInterface object created by the device application.

For example:
```C++
std::shared_ptr<ExperienceObserverInterface> myExperienceObserver = ...;
    
auto experienceManager = myMAX->getExperienceManager();

experienceManager->addObserver(myExperienceObserver);
```

Important: The Experience Manager will not take on ownership of the Experience Observer object, it will only store a `std::weak_ptr` to that object internally. The device application must manage the life cycle of the observer object. If the observer object is destructed, it will automatically be removed from the list of Experience Observers kept by the Experience Manager.

 
# Appendix A: Experience Rendering Examples
## Example 1: Simple Device
```C++
// Given a simple device with an LED Ring capable of displaying solid colors
// or a flashing animation of one color
class myExperienceObserver : public ExperienceObserverInterface {
public:
    void onExperienceChange(const std::vector<Experience>& experiences) override {
        if (experiences.empty()) {
            myLEDRing->disable();
            return;
        }

        auto& experience = experiences.front();
        if (experience.agentName == "alexa") {
            if (experience.identifier == ExperienceIdentifier::LISTENING) {
                myLEDRing->enable(ledRing::color::BLUE, ledRing::animation::SOLID);
            } else if (experience.identifier == ExperienceIdentifier::RESPONDING) {
                myLEDRing->enable(
                    ledRing::color::BLUE, ledRing::animation::FLASHING);
            }
        } else if (experience.agentName == "computer") {
            if (experience.identifier == ExperienceIdentifier::LISTENING) {
                myLEDRing->enable(ledRing::color::GREEN, ledRing::animation::SOLID);
            } else if (experience.identifier == ExperienceIdentifier::RESPONDING) {
                myLEDRing->enable(
                    ledRing::color::GREEN, ledRing::animation::FLASHING);
            }
        }
    }
};
```
## Example 2: Complex Device
```C++
// Given a complex device with an attention system capable of simultaneously
// rendering an interaction (an agent speaking, listening, or thinking) via for 
// example an LED Ring, and music or other media an agent is playing via for 
// example a colored backlight
class myExperienceObserver : public ExperienceObserverInterface {
public:
    void onExperienceChange(const std::vector<Experience>& experiences) override {
        auto findFirstInteraction = [](const Experience& experience) {
            return (
                experience.identifier == ExperienceIdentifier::LISTENING ||
                experience.identifier == ExperienceIdentifier::RESPONDING ||
                experience.identifier == ExperienceIdentifier::THINKING);
        };

        // Find and render the first interaction in the experience list,
        // or stop rendering interactions if none is found.
        auto interactionIt = std::find(experiences.begin(), experiences.end(), findFirstInteraction);
        if (interactionIt == experiences.end()) {
            attentionSystem->stopInteraction();
        } else {
            attentionSystem->renderInteraction(interactionIt->agentName, interactionIt->identifier);
        }

        auto findFirstMusic = [](const Experience& experience) {
            return (experience.identifier == ExperienceIdentifier("music"));
        };

        // Find and render the first music experience in the experience list,
        // or stop rendering any music experience if none is found.
        auto musicIt = std::find(experiences.begin(), experiences.end(), findFirstMusic);
        if (musicIt == experiences.end()) {
            attentionSystem->stopMusic();
        } else {
            attentionSystem->renderMusic(musicIt->agentName);
        }
    }
};
```

# Appendix B: Code References
## Code 0: MultiAgentExperience/Experience/Experience.h
```
namespace multiAgentExperience {
namespace experience {
struct Experience {
    /// The id of the actor requesting the 'user experience'
    actor::ActorId actorId;
    /// The id of the experience session corresponding to this experience
    SessionId sessionId;
    /// The name or unique identifier for the experience among any other experiences the agent may request
    ExperienceId experienceId;
};

}
}
```
## Code 1: MultiAgentExperience/Experience/ExperienceObserverInterface.h
```C++
namespace multiAgentExperience {
namespace experience {

class ExperienceObserverInterface {
public:
    virtual ~ExperienceObserverInterface() = default;
    virtual void onExperienceChange(const std::vector<Experience>& experiences) = 0;
};

} 
}
```
## Code 2: MultiAgentExperience/Experience/ExperienceManagerInterface.h
```C++
namespace multiAgentExperience {
namespace experience {

class ExperienceManagerInterface {
public:
    virtual ~ExperienceManagerInterface() = default;
    virtual void addObserver(std::weak_ptr<ExperienceObserverInterface> observer) = 0;
    virtual void clearObservers() = 0;
};

}
}
```
