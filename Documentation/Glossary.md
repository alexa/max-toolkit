# MAX Toolkit Glossary

See also the [Multi-Agent Design Guide Glossary](https://developer.amazon.com/en-US/alexa/voice-interoperability/design-guide/glossary#glossary).

1. **Activity** - An Activity captures the lifecycle of any audible Agent feature which is not part of a Dialog. This can include making a call, delivering an alarm, and playing music.
2. **Actor** - Either an Agent or the Device. An entity which is able to interact with the MAX Library to request activities, register controls, or start experiences.
3. **Agent** - The VII Multi-Agent Design Guide defines an Agent as: the digital “person” that the customer interacts with through conversation (turn taking). The MAX Toolkit only interacts with part of the Agent: the device side implementation. When Agent is referenced in MAX documents it is always referring to this part of the Agent which is using the MAX Library.
4. **Agent Manager** - A software component that manages the state of each Agent. All the supported Agents are registered with the Agent Manager.
5. **Barge-In** : When an Agent is in an active Dialog with the customer, the user or any Agent can interrupt the ongoing Dialog with a new Dialog. The current Dialog is stopped and never resumed, the second Dialog starts immediately.
6. **Barge-In Policy** - A class component that provides what permutation/combination of dialog barge-in is allowed for a certain application use case
7. **Control** - A Control is a device-global action with a type matching a supported Universal Device Command (UDC) on the device.
8. **Device** - The host for the voice agent software that is responsible for interacting with the end user. Possibly a dedicated device, a multipurpose device like a vehicle’s onboard computer, or a software application on general computing hardware like a phone or desktop computer.
9. **Dialog** - A Dialog captures the lifecycle of any Agent interaction which involves the user or Agent continuously speaking to each other, analogous to a conversation between two people. It may consist of many back and forth responses between the Agent and user before the Dialog is complete. A Dialog may be initiated by the user or an Agent.
10. **Experience** - An Experience is a representation of the state of an Agent which may be shared with the Device to be rendered visibly, physically, or audibly for the user. The same Experience Identifier may be rendered differently per Agent according to the Device and Agent makers. For example ‘listening’ may be a different color for different Agents. Experiences can also represent non-Dialog states of an Agent, such as an active timer being played for the user.
11. **Experience Identifier** - A value which specifies the Experience that is active. These are enumerated between the Device and each Agent maker to determine how an Agent’s experience is rendered on the Device’s Attention System. The set of values is separate for each Agent, and therefore they can share identifier values.
12. **MAX Library** - A software component in the MAX Toolkit which allows multiple agents to co-exist on a device, enables client-side UDCs and Agent Transfers, and multiple Attention Systems. Agent-makers and device-makers use the client-side APIs of the MAX Library to create a multi-agent experience.
13. **MAX Sample Application** - The demo application bundled with the MAX Toolkit to demonstrate possibility of integrating an agent with the MAX Library.
14. **MixingBehavior** - Defines the behavior of an Activity, when mixed with other Activities. For e.g. an Activity like Music can continue to play (at a reduced volume, aka DUCK) when another Activity like an Alert starts.
15. **MixabilityType** - Defines whether an associated Activity can be mixed with other Activities. This enumeration helps in figuring out the MixingBehavior of an associated Activity and also other Activities.
16. **Static Experience** - Certain Experiences provided by an agent such as DND & Pending Notifications are not tied to any activity or a dialog. Hence a component is introduced to enable agents to deliver these static Experiences to the device. These Experiences will always be lower priority than Experiences associated with Activities and Dialogs, and will be communicated to the device integrator in this priority order.