/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_DIALOGBARGEINPRIORITY_H
#define MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_DIALOGBARGEINPRIORITY_H

namespace multiAgentExperience {
namespace dialog {

/**
 * The barge-in priority of the DialogRequest.
 *
 * Each value has a corresponding policy in MAXPolicies which will be checked before allowing for a barge-in
 */
enum class DialogBargeInPriority {
    HIGH,
    NORMAL,
};

}  // namespace dialog
}  // namespace multiAgentExperience

#endif // MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_DIALOGBARGEINPRIORITY_H
