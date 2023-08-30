# Overview of MAX Sample Application

## Introduction
A typical multi-agent device has one set of microphones that needs to be shared across multiple device software components. These components can include an Audio Front End (AFE) and two or more agents. This document describes our approach to this integration in the MAX Sample Application.

## Audio-Sharing Primitives
This section presents a high-level overview of the data structures and classes that a developer needs to be aware of within the MAX Toolkit. More detailed information can be found in the header files for each class.

### Primitives within the MAX Library

### Example Implementations in the Sample Application
Please note that the Sample Application implementations are provided only as examples, which may differ from choices you make in your own product. The below is presented to show some of the choices that were made to build the demo functionality which our Sample Application provides.

#### Audio and Microphone Configuration
The Sample Application configuration format takes in Alexa configuration file, that includes sections for AudioFormat, and Microphone configuration.

