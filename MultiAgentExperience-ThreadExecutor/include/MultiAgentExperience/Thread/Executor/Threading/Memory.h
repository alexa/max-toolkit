/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/
#ifndef MULTI_AGENT_EXPERIENCE_THREADING_THREADEXECUTOR_MEMORY_H_
#define MULTI_AGENT_EXPERIENCE_THREADING_THREADEXECUTOR_MEMORY_H_

#include <memory>
#include <utility>

namespace multiAgentExperience {
namespace thread {
namespace executor {
namespace threading {

/**
 * NOTE : This implementation has been picked up from : https://tiny.amazon.com/xt0suiag/codeamazpackCtdlblobmastUtil
 *        and might need to be moved to the "MultiAgentExperience-Testable-Device-Agent-API"
 *        package in the future
 */
// START Herb Sutter code sample adaptation
template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
// END Herb Sutter code sample adaptation

} // threading
} // executor
} // thread
} // multiAgentExperience

#endif // MULTI_AGENT_EXPERIENCE_THREADING_THREADEXECUTOR_MEMORY_H_