/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_DIALOGMANAGERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_DIALOGMANAGERINTERFACE_H_

#include <memory>

#include "MultiAgentExperience/Dialog/DialogRequestInterface.h"
#include "MultiAgentExperience/Dialog/ListeningHandlerInterface.h"
#include "MultiAgentExperience/Dialog/SpeakingHandlerInterface.h"
#include "MultiAgentExperience/Dialog/ThinkingHandlerInterface.h"
#include "MultiAgentExperience/Dialog/ControlReceiverInterface.h"

namespace multiAgentExperience {
namespace dialog {

/**
 * The DialogManagerInterface is used to configure how dialogs are handled by an Agent. This includes requesting new
 * dialogs and stopping active dialogs.
 */
class DialogManagerInterface {
public:
    /**
     * Destructor.
     */
    virtual ~DialogManagerInterface() = default;

    /**
     * Requests a dialog to be started.
     *
     * @param request - The handler for the request lifecycle.
     */
    virtual void request(std::shared_ptr<DialogRequestInterface> request) = 0;

    /**
     * Immediately stops a dialog which was started for the given request. If the dialog is not active for this request
     * it has no effect.
     *
     * @param request - The handler for the request lifecycle which should be stopped.
     */
    virtual void stop(std::shared_ptr<DialogRequestInterface> request) = 0;

    /**
     * Allows registering handler for all of the dialog states at once. Any existing handler for each state will be
     * overridden.
     *
     * @param controlReceiver - The new interface to receive available ControlTypes before LISTENING state.
     * @param listeningHandler - The new handler for LISTENING state.
     * @param thinkingHandler - The new handler for THINKING state.
     * @param speakingHandler - The new handler for SPEAKING state.
     */
    virtual void setAllHandlers(
        std::shared_ptr<ControlReceiverInterface> controlReceiver,
        std::shared_ptr<ListeningHandlerInterface> listeningHandler,
        std::shared_ptr<ThinkingHandlerInterface> thinkingHandler,
        std::shared_ptr<SpeakingHandlerInterface> speakingHandler) = 0;

    /**
     * Removes all registered handlers for the dialog states.
     */
    virtual void removeAllHandlers() = 0;

    /**
     * Registers the receiver for collecting available ControlTypes before LISTENING state. Existing receiver for each state will be overridden.
     *
     * @param handler - The new handler for LISTENING state.
     */
    virtual void setControlReceiver(std::shared_ptr<ControlReceiverInterface> receiver) = 0;

    /**
     * Removes the receiver for collecting available ControlTypes before LISTENING state.
     */
    virtual void removeControlReceiver() = 0;

    /**
     * Registers the handler for LISTENING state. existing handler for each state will be overridden.
     *
     * @param handler - The new handler for LISTENING state.
     */
    virtual void setListeningHandler(std::shared_ptr<ListeningHandlerInterface> handler) = 0;

    /**
     * Removes the handler for LISTENING state.
     */
    virtual void removeListeningHandler() = 0;

    /**
     * Registers the handler for THINKING state. existing handler for each state will be overridden.
     *
     * @param handler - The new handler for THINKING state.
     */
    virtual void setThinkingHandler(std::shared_ptr<ThinkingHandlerInterface> handler) = 0;

    /**
     * Removes the handler for THINKING state.
     */
    virtual void removeThinkingHandler() = 0;

    /**
     * Registers the handler for SPEAKING state. existing handler for each state will be overridden.
     *
     * @param handler - The new handler for SPEAKING state.
     */
    virtual void setSpeakingHandler(std::shared_ptr<SpeakingHandlerInterface> handler) = 0;

    /**
     * Removes the handler for SPEAKING state.
     */
    virtual void removeSpeakingHandler() = 0;
};

}  // namespace dialog
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_DIALOG_DIALOGMANAGERINTERFACE_H_
