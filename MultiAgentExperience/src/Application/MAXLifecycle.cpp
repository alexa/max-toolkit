/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Application/MAXLifecycle.h"

static const std::string MODULE_TAG("MAXLifecycle");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

namespace multiAgentExperience {
namespace library {
namespace application {

MAXLifecycle::MAXLifecycle():
    m_state{MAXState::NOT_READY} {
}

void MAXLifecycle::addObserver(std::shared_ptr<MAXLifecycleObserverInterface> observer) {
    LX(DEBUG3, "");
    m_observers.push_back(observer);
}

void MAXLifecycle::transitionToReady() {
    LX(DEBUG3, "");

    // Change the state to READY
    m_state = MAXState::READY;

    for (const auto& weakObserver: m_observers) {
        if (auto observer = weakObserver.lock()) {
            observer->onTransitionToReady();
        }
    }
}

bool MAXLifecycle::isReady() {
    LX(DEBUG3, "");
    return m_state == MAXState::READY;
}

}  // namespace application
}  // namespace library
}  // namespace multiAgentExperience