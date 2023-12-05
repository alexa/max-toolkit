# Change Log

## v2.0.0
MAX Toolkit v2.0.0 is a major release that now allows Agents to communicate with MAX via Inter-Process Communication (IPC). This is facilitated by the MAX IPC framework which leverages gRPC C++ to provide IPC capabilities. 

### MAX-API Changes
* Added a new `HashableInterface` which is used by the `ActivityRequestInterface` and the `DialogRequestInterface` (required for use cases introduced with IPC).
* Methods in `StartListeningCallback` and `ActivityRequestInterface` are made virtual.
* A new `registerAgent()` API is introduced in the `AgentManagerInterface`, to support single agent registration use cases like agent process crash recovery.

### Enhancements
* The MAX IPC framework is introduced along with two major packages - `MultiAgentExperience-IPC` and `MultiAgentExperience-IPC-gRPC`. The MAX IPC framework facilitates inter-process communication between the MAX process and any agent processes, and enhances security by isolating processes.  
* Added a new package - `MultiAgentExperience-ThreadExecutor`.
* The MAX SampleApplication is updated to incorporate the MAX IPC framework. Read more here - [MAX_IPC.md](Documentation/MAX_IPC.md).

### Issue fixes
* Added a fix to address an issue which did not allow Alexa alerts to be stoppable after a power-cycling the device.

### Known Issues

## v1.3.0

### MAX-API Changes

APIs supported by MAX Library are provided in a separate MAX-API Directory with this release. The details of what has changed in the APIs with respect to v0.4.0 can be found in the below document.
[MAX_API_Documentation.md](Documentation/MAX_API_Documentation.md)

### Enhancements
* Added the ability to temporarily store any activity/dialog requests in a buffer, during agent re-registration, when the MAX process recovers from a crash. After all agents have executed their OnCompletionCallback (received in `AgentRegistrationInterface::onReady`), the requests stored in the buffer will be processed in a priority order based on the activity type of the request. This helps restore correct state of activities/dialogs when after a crash.
* Changed the set of shared ControlTypes given to an agent during a dialog from “any controls available for other actors” to “only the controls for foreground experiences of other actors”.
* The logger has been extracted out of `MAX` and bundled separately in this package named `MultiAgentExperience-Logger`. This doesn't disturb any client operation but helps make the code more modular.
* Added MAX integration for pending notifications.
* Added MAX integration for 'Do Not Disturb'.
* Added integration for UDC in Alexa Cloud and AVS-SDK.

### Issue fixes
* Added a fix in AVS-SDK to address a race condition causing Alexa alerts to not stop on invoking a UDC STOP command.

### Known Issues

All issues listed here are the behaviour/ issues observed with one agent as Alexa.

* Alexa alert is not stoppable using UDC after power cycle -  If a user restarts the device while Alexa is ringing alert, after the device boot up, Alexa alert is not stoppable using UDC.
* Content(News) mixability type is set as mixable-restricted instead of non-mixable in some cases - If a user plays music from Alexa app, then the user requests for news from Alexa followed by a dialog from the other agent, then news gets attenuated while the dialog is ongoing. News is supposed to be paused instead. This happens when “Amazon Music” or “Tune-in Radio” is played from Alexa app.
* Content(Music) mixability type set as non-mixable instead of mixable restricted in some cases - If a user plays news first and then music(“Amazon Music” or “Tune-in Radio”) from Alexa app, then music gets paused insted of getting attenuated.
* Reminder's dialog/TTS is not delivered when reminder is enqueued with timer - A reminder has an audio cue followed by TTS indicating a reminder message. If user sets the timer first and then a reminder, timer starts ringing first and reminder is enqueued. When the user stops the timer, reminder audio cue is played but the TTS is not delivered.
* Music does not attenuate when notification is received in some cases-  If a user plays music (“Amazon Music” or “Tune-in Radio”) from Alexa app, and then if a notification is received, music does not get attenuated and plays in full volume. The music is supposed to get attenuated in this case.

## v0.4.0

Initial release of the MAX Toolkit.

### Known Issues

#### Sample Application

* When running the SampleApplication with wakeword engines, you will see false positive errors in the console regarding wakeword engine creation. These errors can be safely ignored.
* The MAX Sample Application will become unresponsive if you attempt to “barge in” on an un-interruptible response (a response that contains either wake word “Alexa” or “Computer”) from Alexa. For example,
  * Say “Alexa, what is Alexa Voice Service?”
  * Then while she is speaking “Alexa, stop”.
* The Alexa agent may lose context in multi-turn interactions. Alexa will respond with “Sorry, I don’t know that” (or something similar) to your response.
* Alexa will sometimes become unresponsive after multiple music or content streaming activities.
* Ubuntu: The Sample Application will sometimes segmentation fault during shut down.

