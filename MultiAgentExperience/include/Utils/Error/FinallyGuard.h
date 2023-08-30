/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_UTILS_ERROR_FINALLYGUARD_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_UTILS_ERROR_FINALLYGUARD_H_

#include <functional>

namespace multiAgentExperience {
namespace library {
namespace utils {
namespace error {

/**
 * Define a class that can be used to run a function when the object goes out of scope.
 *
 * This simulates try-finally statements. The following structure:
 *
 * @code
 * try {
 *   <try_block>
 * } finally {
 *   <finally_block>
 * }
 * @endcode
 *
 * can be replaced by:
 *
 * @code
 *   FinallyGuard guard { []{ <finally_block> }};
 *   <try_block>
 * @endcode
 */
class FinallyGuard {
public:
    /**
     * Constructor.
     *
     * @param finallyFunction The function to be executed when the object goes out of scope.
     */
    FinallyGuard(const std::function<void()>& finallyFunction);

    /**
     * Destructor. Runs @c m_function during destruction.
     */
    ~FinallyGuard();

private:
    /// The function to be run when this object goes out of scope.
    std::function<void()> m_function;
};

inline FinallyGuard::FinallyGuard(const std::function<void()>& finallyFunction) : m_function{finallyFunction} {
}

inline FinallyGuard::~FinallyGuard() {
    if (m_function) {
        m_function();
    }
}

}  // namespace error
}  // namespace utils
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_UTILS_ERROR_FINALLYGUARD_H_
