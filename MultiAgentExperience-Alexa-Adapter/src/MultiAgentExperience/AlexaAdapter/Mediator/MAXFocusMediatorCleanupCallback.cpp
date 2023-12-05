/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#include "MultiAgentExperience/AlexaAdapter/Mediator/MAXFocusMediatorCleanupCallback.h"

#include <AVSCommon/Utils/Logger/Logger.h>

#include "MultiAgentExperience/AlexaAdapter/Mediator/MAXFocusMediator.h"

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace mediator {

static const std::string TAG("MAXFocusMediatorCleanupCallback");
#define LX(event) alexaClientSDK::avsCommon::utils::logger::LogEntry(TAG, event)

MAXFocusMediatorCleanupCallback::MAXFocusMediatorCleanupCallback(
    std::weak_ptr<mediator::MAXFocusMediator> maxFocusMediator,
    const std::string& focusRequestId,
    const std::size_t& uniqueRequestId):
        m_maxFocusMediator{std::move(maxFocusMediator)},
        m_focusRequestId{focusRequestId},
        m_uniqueRequestId{uniqueRequestId} {
}

void MAXFocusMediatorCleanupCallback::operator()() {
    ACSDK_DEBUG5(LX(__func__ ));
    if (auto maxFocusMediator = m_maxFocusMediator.lock()) {
        maxFocusMediator->cleanup(m_focusRequestId, m_uniqueRequestId);
    } else {
        ACSDK_ERROR(LX(__func__).m("Unable to acquire a strong reference to the maxFocusMediator for cleanup"));
    }
}

} // namespace mediator
} // namespace multiAgentExperience
} // namespace alexaClientSDK
