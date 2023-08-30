/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLPRIORITY_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLPRIORITY_H_

namespace multiAgentExperience {
namespace library {
namespace control {

enum class ControlPriority { DEVICE, DIALOG, COMMUNICATIONS, ALERTS, NOTIFICATIONS, CONTENT, NONE, UNDEFINED };

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLPRIORITY_H_
