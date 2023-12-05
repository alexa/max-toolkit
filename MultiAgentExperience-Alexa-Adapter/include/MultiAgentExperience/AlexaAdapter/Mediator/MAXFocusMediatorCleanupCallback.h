/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_MEDIATOR_CLEANUPCALLBACK_H
#define MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_MEDIATOR_CLEANUPCALLBACK_H

#include <memory>
#include <string>
#include <utility>

namespace alexaClientSDK {
namespace multiAgentExperience {
namespace mediator {
// Forward declare AlexaFocusRequestBuffer to address a circular reference: CleanupCallback -> MAXFocusMediator -> CleanupCallback
class MAXFocusMediator;

/**
 * A callback (functor), which when executed, cleanups any objects for the respective focusRequestId.
 */
struct MAXFocusMediatorCleanupCallback {
public:
    /**
     * Constructor.
     *
     * @param maxFocusMediator A weak_ptr to the maxFocusMediator object
     * @param focusRequestId The focusRequestId whose related objects are cleaned up
     * @param uniqueRequestId The uniqueRequestId that is to be checked before cleanup
     */
    MAXFocusMediatorCleanupCallback(
        std::weak_ptr<MAXFocusMediator> maxFocusMediator,
        const std::string& focusRequestId,
        const std::size_t& uniqueRequestId);

    /**
     * Cleans up the entry for the focus request ID in m_focusRequestId on the condition that the m_uniqueRequestId
     * is the same as the uniqueRequestId in the entry to be cleaned up.
     */
    void operator()();

private:
    /// We hold a weak_ptr here, because of a circular reference between related classes. The circular reference is -
    /// CleanupCallback -> MAXFocusMediator -> CleanupCallback
    std::weak_ptr<MAXFocusMediator> m_maxFocusMediator;

    /// The FocusRequestId associated with this CleanupCallback. This FocusRequestId also represents the activity/dialog requested by AVS SDK.
    std::string m_focusRequestId;

    /// The unique integer that is created for each activity/dialog request.
    std::size_t m_uniqueRequestId;
};

} // namespace mediator
} // namespace multiAgentExperience
} // namespace alexaClientSDK

#endif //MULTIAGENTEXPERIENCE_ALEXA_ADAPTER_MEDIATOR_CLEANUPCALLBACK_H
