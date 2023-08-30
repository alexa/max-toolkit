/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROL_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROL_H_

#include <atomic>
#include <functional>
#include <future>
#include <memory>

#include "ControlID.h"
#include "ControlName.h"

namespace multiAgentExperience {
namespace library {
namespace control {

typedef std::packaged_task<void()> ControlTask;

class Control {
public:
    Control(ControlName name, std::shared_ptr<ControlTask> task);

    template <typename Task, typename... Args>
    static std::shared_ptr<Control> create(const ControlName name, Task task, Args&&... args) {
        auto packagedTask = createTask(task, std::forward<Args>(args)...);
        return std::make_shared<Control>(name, packagedTask);
    }

    bool operator==(const Control& rhs) const {
        return m_name == rhs.m_name;
    }

    ControlID getID() const;

    ControlName getName() const;

    void operator()() const;

private:
    // TODO: this should maybe shared in a util shared with Executor instead of here
    /**
     * Specialization of @c forwardPromise() for @c void types.
     *
     * @param promise The @c std::promise to fulfill when @c future is fulfilled.
     * @param future The @c std::future on which to wait before fulfilling @c promise.
     */
    static void forwardPromise(std::shared_ptr<std::promise<void>> promise, std::future<void>* future) {
        future->get();
        promise->set_value();
    }

    template <typename Task, typename... Args>
    static std::shared_ptr<ControlTask> createTask(Task task, Args&&... args) {
        // Remove arguments from the tasks type by binding the arguments to the task.
        auto boundTask = std::bind(std::forward<Task>(task), std::forward<Args>(args)...);

        /*
         * Create a std::packaged_task with the correct return type. The decltype only returns the return value of the
         * boundTask. The following parentheses make it a function call with the boundTask return type. The package task
         * will then return a future of the correct type.
         *
         * Note: A std::packaged_task fulfills its future *during* the call to operator().  If the user of a
         * std::packaged_task hands it off to another thread to execute, and then waits on the future, they will be able
         * to retrieve the return value from the task and know that the task has executed, but they do not know exactly
         * when the task object has been deleted.  This distinction can be significant if the packaged task is holding
         * onto resources that need to be freed (through a std::shared_ptr for example).  If the user needs to wait for
         * those resources to be freed they have no way of knowing how long to wait.  The translated_task lambda below
         * is a workaround for this limitation.  It executes the packaged task, then disposes of it before passing the
         * task's return value back to the future that the user is waiting on.
         */
        auto packaged_task = std::make_shared<ControlTask>(boundTask);

        // Create a promise/future that we will fulfill when we have cleaned up the task.
        auto cleanupPromise = std::make_shared<std::promise<void>>();
        auto cleanupFuture = cleanupPromise->get_future();

        // Remove the return type from the task by wrapping it in a lambda with no return value.
        auto translated_task = [packaged_task, cleanupPromise]() mutable {
            // Execute the task.
            packaged_task->operator()();
            // Note the future for the task's result.
            auto taskFuture = packaged_task->get_future();
            // Clean up the task.
            packaged_task.reset();
            // Forward the task's result to our cleanup promise/future.
            forwardPromise(cleanupPromise, &taskFuture);
        };

        // Release our local reference to packaged task so that the only remaining reference is inside the lambda.
        packaged_task.reset();

        auto final_task = std::make_shared<ControlTask>(translated_task);
        return final_task;
    }

    const ControlName m_name;
    const ControlID m_id;
    const std::shared_ptr<ControlTask> m_task;
    std::shared_ptr<std::atomic_bool> m_invoked;
};

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience

template <>
struct std::hash<multiAgentExperience::library::control::Control> {
    std::size_t operator()(multiAgentExperience::library::control::Control const& control) const noexcept {
        return std::hash<multiAgentExperience::library::control::ControlName>()(control.getName());
    }
};

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROL_H_
