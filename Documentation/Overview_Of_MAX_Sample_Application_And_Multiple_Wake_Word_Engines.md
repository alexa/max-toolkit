# Overview of MAX Sample Application and Multiple Wake Word Engines

## Introduction
A typical multi-agent device has one set of microphones that needs to be shared across multiple device software components. These components can include one or more Wake Word Engines (WWEs), an Audio Front End (AFE), and two or more agents. This document describes our approach to this integration in the MAX Sample Application.
 
In the context of this document, it should be noted that a WWE refers to the software component that is running on the application’s processor, though the MAX Toolkit design does not preclude running the WWE on an alternate processor (a DSP, for example).

## Audio-Sharing Primitives
This section presents a high-level overview of the data structures and classes that a WWE developer needs to be aware of within the MAX Toolkit. More detailed information can be found in the header files for each class.

### Primitives within the MAX Library

#### AudioFormat

The MAX Library provides the AudioFormat structure to define the format which a multi-agent application will use to ensure alignment between various audio devices and readers of data.

#### AudioReaderInterface 
The `AudioReaderInterface` can be implemented by any object which provides audio data.

### Example Implementations in the Sample Application
Please note that the Sample Application implementations are provided only as examples, which may differ from choices you make in your own product. The below is presented to show some of the choices that were made to build the demo functionality which our Sample Application provides.
 
An important detail is that the MAX Sample Application and MAX compatible Alexa agent implementations require that the AVS Device SDK be compiled with WWE support (kitt.ai or other). This is done automatically if using the automated build script on a Raspberry Pi system with the optional wake word engine flag. Refer to the the AVS Device SDK documentation, and the MAX Getting Started guide for further guidance.

#### Audio, Microphone, and WWE Configuration
The Sample Application configuration format includes sections for AudioFormat, Wake Word Engine, and Microphone configuration. See the `max-toolkit/SampleApplication/MAXConfig.json` configuration file for a detailed breakdown of its contents.

#### Class AudioManager
The `AudioManager` is responsible for managing all the components which pertain to audio in our sample multi-agent application. In particular, the `AudioManager` owns:

* The microphone implementation
* The wake word engines
* The audio data buffers

#### Class MicrophoneInterface
The `MicrophoneInterface`  is defined so that the microphone implementations written for the sample application expose a unified interface. Your application may abstract microphones or audio devices in a different way.

#### Class WakewordEngine
The `WakewordEngine` class provides a uniform interface for the AVS Device SDK, and Demo Computer Agent Wakeword Engine implementations used by the MAX Sample Application.
 
#### Class WakeWordEngineFactory
The `WakewordEngineFactory` defines an API used by the sample application to create Wakeword engine handles.
