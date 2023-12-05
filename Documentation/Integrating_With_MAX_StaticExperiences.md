# Integrating with MAX Experiences

## Static Experiences

Certain Experiences provided by an agent such as DND & Pending Notifications are not tied to any activity or a dialog. These are termed as Static Experiences. These Experiences will always be lower priority than Experiences associated with Activities and Dialogs, and will be communicated to the device integrator in this priority order.

## Requesting a Static Experience

To start a Static Experience, a request is made to the `StaticExperienceManagerInterface`. When requesting a static experience via the `addStaticExperience` API, the agent is expected to provide an `ExperienceId` and a priority for the Static Experience. These will always be lower priority than Experiences (a.k.a Active Experiences). The agent is also provided APIs to stop a particular Static Experience.

 
## Rendering a Static Experience
Static Experiences are rendered in the same manner as Active Experiences, by using the `ExperienceObserverInterface`.
