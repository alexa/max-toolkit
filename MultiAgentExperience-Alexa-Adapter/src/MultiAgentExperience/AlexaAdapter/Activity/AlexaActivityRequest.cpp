/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/AlexaAdapter/Activity/AlexaActivityRequest.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace activity {

void AlexaActivityRequest::release() {
    m_handler->release();
}

} // namespace activity
} // namespace multiAgentExperience
} // namespace alexaClientSDK
