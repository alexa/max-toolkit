/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_UTILS_DATA_DATAOBSERVERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_UTILS_DATA_DATAOBSERVERINTERFACE_H_

#include <cstddef>
#include <utility>

namespace multiAgentExperience {
namespace utils {
namespace data {

/**
 * A helper interface for writing actors to use to observe buffered data.
 */
class DataObserverInterface {
public:
    /**
     * Destructor
     */
    virtual ~DataObserverInterface() = default;

    /**
     * Provides data to the observer.
     *
     * @param buffer The buffer provided to the observer.
     * @param numWords The size in words of the data. The word size must be well known.
     * @return A bool if the data was accepted, and the amount of data consumed.
     */
    virtual std::pair<bool, std::size_t> onData(const void* buffer, std::size_t numWords) = 0;
};

}  // namespace data
}  // namespace utils
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_UTILS_DATA_DATAOBSERVERINTERFACE_H_
