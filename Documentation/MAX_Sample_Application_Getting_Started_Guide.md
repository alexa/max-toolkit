# MAX Sample Application Getting Started Guide

The Multi Agent Experience (MAX) developer toolkit contains the MAX Library and a
Sample Application that demonstrates interoperability of Alexa and a second
independent voice assistant. The MAX Library facilitates interoperability between
voice assistants according to the guidance provided by the Voice Interoperability
Initiative (VII) [Multi-Agent Design Guide](https://developer.amazon.com/en-US/alexa/voice-interoperability/design-guide).

This guide will walk you through the prerequisite setup steps and instructions for using an automated build script for the MAX Sample Application.

The MAX Library, and the MAX Sample Application supports wake word engines, and using wake words to activate Agents. However support for wake words is not included in the automated build script unless you build on a RaspberryPi system and enable wake word support when running the build script.

Depending on your system, this setup process may take between 1 hour (Desktop computer running Ubuntu) and 4 hours (Raspberry Pi 4).

## What’s inside the MAX Toolkit?

The MAX Toolkit contains:

1. MAX Library (Directory: MAX/): The library that manages
multiple agents, and handles their interaction patterns, consistent with
recommendations in the Multi-Agent Design Guide.
2. Computer Agent (Directory: Agents/Computer/): An AWS Lex based voice assistant that we have created to demonstrate cooperation with Alexa. AWS Lex is a cloud service that allows you to build conversational AI chat bots equipped with automatic speech recognition (ASR) and natural language understanding (NLU).
3. MAX Sample Application (Directory: SampleApplication/): A Sample Application that runs two simultaneous agents (Computer and Alexa), one or more wakeword engines, console and LED-based experience rendering, and uses the MAX Library to enforce correct multi-agent behavior.
  - Note: The WWE Support available through the automated build script (see below) is only available on the Raspberry Pi platform, and must be enabled when running the build script.

In addition, the MAX Toolkit includes a patch that can be used to modify the [AVS Device SDK v1.23.0](https://developer.amazon.com/docs/alexa/avs-device-sdk/overview.html) to support a MAX-integrated Alexa device-side agent implementation.

## Hardware and Software Requirements

### Hardware
- A computer supporting Ubuntu version 20.04 LTS or later (for fast build times)
- or, a [Rasperry Pi 4 system](https://developer.amazon.com/en-US/docs/alexa/avs-device-sdk/raspberry-pi.html#required-hardware)
  - Optional: A Raspberry Pi [Sense HAT Module](https://www.raspberrypi.org/products/sense-hat/) will enable visual display of the Attention System. You must have an account on the Alexa Developer Portal with access to the MAX Sample Application Sense HAT animation files in order to make use of the RPi Sense HAT Module with the MAX Sample Application.

### Software

#### Operating System
- Ubuntu operating system, version 20.04 LTS or later (for quicker build time)
- or, Raspbian Buster if on a Raspberry Pi.

#### AVS Device SDK

##### **Warning**:  On Raspberry Pi: Use the AVS Device SDK v1.23 only

AVS Device SDK Version 1.24 and beyond do not currently work on Raspberry Pi systems do to an error with the Curl library. 

See:
* https://github.com/alexa/avs-device-sdk/issues/1954
* https://github.com/alexa/avs-device-sdk/issues/1931
* https://github.com/alexa/avs-device-sdk/issues/1959

Make sure to download/build version 1.23 when building on a Raspberry Pi. You can use the following command to check out version v1.23 of the AVS Device SDK

```
git clone --single-branch https://github.com/alexa/avs-device-sdk.git -b v1.23.0
```
When following the AVS Device SDK setup guide for Raspberry Pi, ignore the sections on installing a specific version of libCurl

In particular:

* In section 2.4: do not download and install a custom version of curl, only download and build portaudio

```
cd /home/pi/sdk-folder/third-party
wget -c http://www.portaudio.com/archives/pa_stable_v190600_20161030.tgz
tar zxf pa_stable_v190600_20161030.tgz
cd portaudio
./configure --without-jack
make
```

* In section 3:
  * In step 3.1: Download the version 1.23 of the AVS Device SDK
    ```
    git clone --single-branch https://github.com/alexa/avs-device-sdk.git -b v1.23.0
    ```
  * Ignore step 3.2: Do not download the sensory wakeword engine
  * Ignore step 3.3: Do not accept the sensory wakeword license

* In section 4: Modify the CMake parameters for the AVS Device SDK to exclude curl and Sensory WWE options:

```
cd /home/pi/sdk-folder/sdk-build
cmake /home/pi/sdk-folder/sdk-source/avs-device-sdk \
    -DGSTREAMER_MEDIA_PLAYER=ON \
    -DPORTAUDIO=ON \
    -DPORTAUDIO_LIB_PATH=/home/pi/sdk-folder/third-party/portaudio/lib/.libs/libportaudio.a \
    -DPORTAUDIO_INCLUDE_DIR=/home/pi/sdk-folder/third-party/portaudio/include
```

##### Setup Guide

- Set up the AVS SDK following the instructions here:
  - [Ubuntu](https://developer.amazon.com/en-US/docs/alexa/avs-device-sdk/ubuntu.html)
  - [Raspberry Pi](https://developer.amazon.com/en-US/docs/alexa/avs-device-sdk/raspberry-pi.html)

You must fully complete the setup to be able to interact with Alexa, including the steps to run and authorize the AVS SDK sample app. Take note of the full path to your updated AlexaClientSDKConfig.json file as it is referenced in MAXConfig.json after the MAX Sample Application is built.

#### Other software

- A C++11 Compatible compiler
- git
- gnu make
- cmake v3.10 or later

## Setting up the MAX Sample Application

Estimated time: 1-2 hours.

This section provides step-by-step instructions to set up the MAX Sample Application on a Ubuntu PC using the provided **buildMAXSampleApplication.sh** script. When finished, you will have a working version of the MAX Sample Application to test the interactions with Alexa and the Computer Agent.

Alternatively, you may manually build each of the included projects and a patched AVS Device SDK. To do so, follow the instructions in each sub-project's README.md file.

To continue with the automated build process, open a terminal window.

### Download the MAX Toolkit Source Code

You can use the following command to download the MAX Toolkit source code to the `$PATH_TO_MAX_TOOLKIT_SOURCE` directory, which you should choose to contain the MAX Toolkit source.

```
git clone git@github.com:alexa/max-toolkit.git $PATH_TO_MAX_TOOLKIT_SOURCE
```
### Build the MAX Sample Application

Running the build script is quite simple, it is located at `Scripts/buildMAXSampleApplication.sh` and can be run from any working directory. It accepts one mandatory argument, the directory that you would like to build the MAX Sample Application and dependencies in. We will refer to that target directory as `$MAX_TOOLKIT_INSTALL_DIR`:

```
$PATH_TO_MAX_TOOLKIT_SOURCE/Scripts/buildMAXSampleApplication.sh $MAX_TOOLKIT_INSTALL_DIR
```

Where `PATH_TO_MAX_TOOLKIT_SOURCE` is the directory contain the MAX Toolkit repository.

**Note:** The script will ask for your root or sudo password since it installs the modified AVS SDK and the AWS SDK to /usr/local

Once the script finishes successfully, the MAX Sample Application `SampleApplication` should be built in `$MAX_TOOLKIT_INSTALL_DIR/build/max-sample-app/`.

#### Optional Arguments when building on a Raspberry Pi

You can pass flags to the build script to enable optional features of the Sample Application when running on a Raspberry Pi system.

```
$PATH_TO_MAX_TOOLKIT_SOURCE/Scripts/buildMAXSampleApplication.sh -s -l $MAX_TOOLKIT_INSTALL_DIR
```

- `-s` : This flag enables the Kitt.Ai Snowboy Wake Word Engine for the Alexa and Computer agents.
- `-l` : This flag enables the RPi SenseHAT Animation system for Alexa and Computer attention states. You must also:
  - have the [Sense HAT Module](https://www.raspberrypi.org/products/sense-hat/) installed
  - download the Attention System animation files from the Alexa Developer Portal and place them in `SampleApplication/Assets/Animations/`

## Running the MAX Sample Application

* Navigate to the MAX Sample Application build directory:

```
cd $MAX_TOOLKIT_INSTALL_DIR/build/max-sample-app
```

* Create a MAX Config file by copying the provided template:

```
cp $PATH_TO_MAX_TOOLKIT_SOURCE/SampleApplication/MAXConfig.json .
```

* Edit the copied file and update the *“agents”*, *“wakewordEngines”* and optionally the *“runtimeOptions”* JSON objects according to the instructions in the template.

The final config file would look something like this:

```
{
     "runtimeOptions":{
         "logLevels":{
             "global":"ERROR",
             "componentOverrides":{
 //                "application":"ERROR",
 //                "MAX":"DEBUG3"
 //                "avssdk":"NONE"
 //                "computerAgent":"DEBUG3"
             }
         }
     },
     "audioFormat":{
         "sampleRateHz":16000,
         "numInputChannels":1
     },
     "agents":[
         {
             "name":"computer",
             "wakewords":["computer"],
             "configFilePath":""
         },
         {
             "name":"alexa",
             "wakewords":["alexa"],
             // Absolute path of the AlexaClientSDKConfig.json
             // file created during the installation of the AVS SDK.
             // If you followed the exact instructions, this path
             // would be /home/max/sdk-build/Integration/AlexaClientSDKConfig.json
             "configFilePath":"**<path_to_AlexClientSDKConfig.json>**"
         }
     ],
     "wakewordEngines":[],
     "microphone":{
         "suggestedLatencySeconds":0.150
     }
 }
```

If you elected to build Kitt.Ai wake word engine support in, the `wakewordEngines` section of the config would appear as:

```
"wakewordEngines":[
    {
        "name":"kitt.ai",
        "createMethod":"CUSTOM",
        "wakewords":["computer"],
        "resourceFolder":"**<path_to_MAX_TOOLKIT_INSTALL_DIR>**/third-party/snowboy/resources"
    },
    {
        "name":"kitt.ai",
        "createMethod":"AVS_SDK",
        "wakewords":["alexa"],
        "resourceFolder":"**<path_to_MAX_TOOLKIT_INSTALL_DIR>**/third-party/snowboy/resources"
    }
],
```


### Run the MAX Sample Application.

From `$MAX_TOOLKIT_INSTALL_DIR/build/max-sample-app` you can run the Sample Application:

```
./SampleApplication ./MAXConfig.json
```

Note: If the agents do not respond to your queries, or you are unable to hear their responses please consult the **Troubleshooting** section below.

### Testing the MAX Sample Application

* Activate Alexa by pressing `1` and then hitting enter.
You should see a series of messages scrolling in your terminal window. One of these messages shows a Listening status. This status indicates that the wake word you spoke triggered Alexa.


* Say *"Tell me a joke."*
Alexa responds with a funny joke. You should see the text change from Listening to Thinking..., then Speaking.


* Activate Computer by pressing `2`
You should see a series of messages scrolling in your terminal window. One of these messages is a "Computer: Listening...". This status indicates that the wake word you spoke triggered Computer.



* Say *"What can you do?"*
     Computer responds by describing the features of the Computer voice assistant. You should see the text change from Listening to Thinking, then Speaking.


### Interactions


You can trigger Alexa or Computer by using tap-to-talk.

#### Interact with Alexa by using tap-to-talk

Press 1+Enter to talk to Alexa. This command simulates a Tap-to-Talk interaction.

For example:
*You* (1+Enter): "What's the weather like?"
*Alexa*: "Right now in Portland, it's 71 degrees with sun..."

#### Interact with Computer by using tap-to-talk

    Press 2+Enter to talk to Computer. This command simulates a Tap-to-Talk interaction
For example:
*You* (2+Enter): "What can you do?"
*Computer*: “You can ask me questions about my hardware, software, and operating system...”


#### Talk with Computer and Alexa

    Sample utterances to try:
1. Alexa: *who made you?*
2. Alexa: *what’s the weather right now?*
3. Alexa: *tell me a joke.*
4. Computer: *who made you?*
5. Computer: *who is Alexa?*
6. Computer: *what kind of OS do you run on?*

For a full list of the available Computer utterances, see the **Appendix** below.


## Multi-Agent interoperability features

When an agent is in the Speaking state, responding to a customer, the customer can interrupt that agent’s response with any other available agent. (*Barge In*)

**Example:**

 1. Activate Computer and Say “who is the first computer programmer?”
 Computer will respond with an answer. Don’t let the voice assistant finish their response.

 2. Activate Alexa and Say “what time is it?” Alexa will respond with the time.


**What’s supported?**


* Multiple simultaneous wake words are supported, meaning each agent is invocable and identifiable by their own unique wake words.
* “Barge In“ is supported for responses that do not contain either wake word (Alexa or Computer) in the response. Responses that contain the wake words do not support ”barge in“ to prevent self-wake. Please note that this is enabled in the MAX Library with the cmake flag `-DENABLE_DEMO_ONLY_SOFTWARE_CROSSWAKE_DETECTION`, which our installation script enables by default. Self-wake can also be prevented with audio front end processing however this is not included in this demo. Some example utterances that agents can ”barge in” on:
* Computer: how fast can you run?
* Computer: what do you say?
* Alexa: what is the weather?



### Attention System

The Attention System is the combination of all visual and audible cues presented to a customer to communicate a voice agent’s attention. Each agent should have distinctly different visual and audible cues so the customer knows which agent they are talking to.

*Example (Only applicable if you’re using the Raspberry Pi SenseHAT LED Array):*

1. Activate Alexa and say “what time is it?”
 Notice how Alexa renders animations for Listening, Thinking and Speaking states.

 2. Activate Computer and say “what can you do?” Notice how Computer renders animations for Listening, Thinking and Speaking states which are slightly different from Alexa’s animations.


### Universal Device Commands

Universal Device Commands (UDCs) are those commands that a customer may use with any compatible agent to control certain device functions, even if the agent was not used to initiate the experience.

As of the release of this document, Alexa Voice Service does not support UDCs, but the MAX Sample Application implements a few client-side only UDCs.

 *Example:*

1. Activate Alexa and say “play jazz music.”
Alexa will start playing jazz music on your device.

2. Activate Computer and say “stop.”
Computer will stop the music even though it was Alexa playing the music.


**What’s supported?**
Computer supports the “Stop” UDC for several Alexa operations. They are:

* Playing music
* Setting a timer
* Setting an alarm
* Setting a reminder

### Agent Transfer

Agent Transfer occurs when the customer makes a request of an agent (Agent 1) which cannot directly fulfill their request but Agent 1 is aware of another agent (Agent 2) on the device which can likely fulfill that request. Agent 1 can summon the other agent to assist the customer. No data or context is passed between agents during a transfer, and the customer repeats their request directly to Agent 2 without needing to say the wake word.

*Example:*

1. Activate Computer and say “set a timer for 10 seconds.”
 Computer will say “That sounds like something Alexa can help with” and then transfer to Alexa. Alexa will say “Hi, Alexa here. How can I help?”

2. Repeat just the utterance to Alexa: “Set a timer for 10 seconds.” Alexa will then set a timer. You should hear it go off in 10 seconds.

3. Activate Alexa and say “stop.” to cancel the timer.

*What’s supported?*

Computer will Agent Transfer to Alexa for the specific utterances:

- remind me to do laundry
- remind me to take medication
- wake me up at Eight A.M
- wake me up at Noon
- set a reminder
- set an alarm
- set a timer



## Appendix

Available Computer Agent Utterances:

- Howdy.
- How fast can you run?
- Remind me to do laundry.
- Remind me to wash my car.
- Remind me to take medication.
- Set a timer for ten seconds.
- Set a timer for two hours.
- Wake me up at eight AM.
- Wake me up at noon.
- What do I say?
- What is the worlds first computer?
- What kind of computer do you run on?
- What kind of OS do you run on?
- What kind of software do you run?
- What was the first computer mouse?
- What was the worlds first portable PC?
- Which computer first defeated a chess champion?
- Who is Alexa?
- Who is the first computer programmer?


## Troubleshooting Setup

See also the [AVS Device SDK Troubleshooting Guide](https://developer.amazon.com/en-US/docs/alexa/avs-device-sdk/troubleshooting.html).

#### If there’s no audio output on your Raspberry Pi, perform the following:

##### Option 1
- Enter ‘sudo raspi-config’ in a terminal window.
  - Scroll down using the down-arrow key to ‘7 Advanced Options’ and press the Tab key. `Select` should now be highlighted in Red. Press the space bar to select it.
  - Scroll down to ‘A4 Audio’, press the Tab key, and then press the space bar.
  - Scroll to the desired audio output type and press the Tab key. `<Ok>` should be highlighted in red. Press the space bar.
  - The original menu should now appear. Press the Tab key twice to highlight `<Finish>` in red. Press the space bar.
  - Re-run the MAX Sample Application.

##### Option 2

Run

```
alsamixer
sudo alsactl store
```

and then re-run the MAX Sample Application.

#### If you receive the following error when running the MAX Sample Application:

```
MediaPlayer:handleBusMessageError:name=AudioMediaPlayer,source=audio_sink, error=Could not open audio device for playback. Device is being used by another application.,debug=gstalsasink.c(860)\: gst_alsasink_open ()\: /GstPipeline\:audio- pipeline/GstAlsaSink\:audio_sink\: hdmi 1
```

- Open the ~/.asoundrc file
- nano ~/.asoundrc
- Make a backup of the .asoundrc file and replace its contents with the below. The numerical device id's may vary: use the one assigned to the device you intend to use:

```
pcm.dmixed {
     type dmix
     ipc_key 1024
     ipc_key_add_uid 0
     slave.pcm "hw:2,0"
}
 pcm.dsnooped {
     type dsnoop
     ipc_key 1025
     slave.pcm "hw:2,0"
 }
 pcm.duplex {
     type asym
     playback.pcm "dmixed"
     capture.pcm {
         type plug
             slave.pcm "hw:2,0"
     }
 }

 # Instruct ALSA to use pcm.duplex as the default device
pcm.!default {
    type plug
     slave.pcm "duplex"
}
ctl.!default {
     type hw
         card 2
 }
```

#### If audio is being routed to your HDMI monitor and the first few words of every Text-To-Speech response are precluded, enter the following command in a terminal window:

```
vcgencmd force_audio hdmi 1
```

#### If you are experiencing audio output issues on Raspberry Pi, try running the Sample Application with the following environment variable:

```
PA_ALSA_PLUGHW=1 ./SampleApplication $PATH_TO_MAX_CONFIG
```

This environment variable will change the way PortAudio loads the ALSA Plugin. For more information see: https://alsa.opensrc.org/Plugin_Documentation.
