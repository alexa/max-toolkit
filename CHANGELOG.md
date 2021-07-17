# Change Log

## v0.4.0

Initial release of the MAX Toolkit.

### Known Issues

#### Sample Application
- When running the SampleApplication with wakeword engines, you will see false positive errors in the console regarding wakeword engine creation. These errors can be safely ignored.
- The MAX Sample Application will become unresponsive if you attempt to “barge in” on an un-interruptible response (a response that contains either wake word “Alexa” or “Computer”) from Alexa. For example,
  - Say “Alexa, what is Alexa Voice Service?”
  - Then while she is speaking “Alexa, stop”.
- The Alexa agent may lose context in multi-turn interactions. Alexa will respond with “Sorry, I don’t know that” (or something similar) to your response.
- Alexa will sometimes become unresponsive after multiple music or content streaming activities.
- Ubuntu: The Sample Application will sometimes segmentation fault during shut down.
