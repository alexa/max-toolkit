/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

/*
 * Portions of this file adapted from a code sample by Herb Sutter at https://herbsutter.com/gotw/_102/,
 * retrieved Dec. 21, 2016, as indicated below.
 */
#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_UTILS_MEMORY_MEMORY_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_UTILS_MEMORY_MEMORY_H_

#include <memory>
#include <utility>

namespace multiAgentExperience {
namespace library {
namespace utils {
namespace memory {

// START Herb Sutter code sample adaptation
template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
// END Herb Sutter code sample adaptation

}  // namespace memory
}  // namespace utils
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_UTILS_MEMORY_MEMORY_H_
