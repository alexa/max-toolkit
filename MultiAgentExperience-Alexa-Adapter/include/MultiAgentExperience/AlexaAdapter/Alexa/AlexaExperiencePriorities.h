/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ALEXA_EXPERIENCEPRIORITIES_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ALEXA_EXPERIENCEPRIORITIES_H

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace alexa {

/// Priorities for experiences. A lower value indicates higher priority.
struct AlexaExperiencePriorities {
    static const int DND;
    static const int PENDING_NOTIFICATION;
};

} // namespace alexa
} // namespace multiAgentExperience
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_ALEXA_EXPERIENCEPRIORITIES_H
