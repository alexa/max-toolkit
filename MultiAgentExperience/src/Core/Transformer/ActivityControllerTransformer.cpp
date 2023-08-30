/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Core/Transformer/ActivityControllerTransformer.h"

#include <MultiAgentExperience/Utils/Logger/Logger.h>

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

static const std::string MODULE_TAG("ActivityControllerTransformer");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ActivityControllerTransformer::ActivityControllerTransformer(std::function<void()> stopCallback) :
        m_stopCallback{stopCallback} {
    LX(DEBUG0, "");
}

void ActivityControllerTransformer::stop() {
    LX(DEBUG0, "");
    m_stopCallback();
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
