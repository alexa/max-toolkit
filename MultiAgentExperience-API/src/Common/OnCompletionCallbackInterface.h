/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_COMMON_ONCOMPLETIONCALLBACKINTERFACE_H
#define MULTI_AGENT_EXPERIENCE_INCLUDE_COMMON_ONCOMPLETIONCALLBACKINTERFACE_H

namespace multiAgentExperience {
namespace common {

/**
 * A utility callback which can be executed in order to notify MAX of some event completion.
 */
class OnCompletionCallbackInterface {
public:

    /// Notifies MAX that the callback was executed.
    virtual void completed() = 0;
};

}  // namespace common
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_COMMON_ONCOMPLETIONCALLBACKINTERFACE_H
