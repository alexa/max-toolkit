/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGREQUESTLIFECYCLE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGREQUESTLIFECYCLE_H_

#include <atomic>
#include <memory>

#include <MultiAgentExperience/Dialog/DialogControllerInterface.h>
#include <MultiAgentExperience/Dialog/DialogRequestInterface.h>

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

/**
 * A DialogRequestLifecycle maintains a lifecycle for a registered DialogRequestInterface, ensuring its lifeycle is
 * completed and no illegal transitions are made.
 */
class DialogRequestLifecycle {
public:
    DialogRequestLifecycle(std::shared_ptr<multiAgentExperience::dialog::DialogRequestInterface> dialogRequest);

    /**
     * Start the request dialog.
     *
     * Note: A previously denied or stopped request can never be started.
     *
     * @param dialogController - Controller for the started dialog
     * @return True if the dialog was started.
     */
    bool start(std::shared_ptr<multiAgentExperience::dialog::DialogControllerInterface> dialogController);

    /**
     * @return whether or not the dialog is currently started.
     */
    bool isStarted();

    /**
     * Sends an error message to the request, but does not change the lifecycle of the Dialog. If the error is fatal to
     * the request, also call stop.
     *
     * Note: Only started dialogs can receive errors.
     * @param errorMessage
     */
    void error(const std::string& errorMessage);

    /**
     * Denies the request and provides a message explaining the reason.
     *
     * Note: Only an unstarted and unstopped request can be denied.
     *
     * @param denialMessage - A message explaining the denial.
     */
    void deny(const std::string& denialMessage);

    /**
     * Intermediate step between a started and stopped request. This must always be followed buy a call to stop. It is
     * useful for taking the dialog out of a started state while some cleanup is being done before stop is called.
     *
     * Note: An unstarted request will be denied instead.
     */
    void beforeStop();

    /**
     * Stops a started dialog for the request.
     *
     * Note: An unstarted request will be denied instead.
     */
    void stop();

private:
    enum class RequestLifecycleState { REQUESTED, STARTED, STOPPING, STOPPED };

    bool trySwitchState(RequestLifecycleState from, const RequestLifecycleState& to);

    bool isInState(const RequestLifecycleState& state);

    std::atomic<RequestLifecycleState> m_requestLifecycleState;
    std::shared_ptr<multiAgentExperience::dialog::DialogRequestInterface> m_dialogRequest;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGREQUESTLIFECYCLE_H_
