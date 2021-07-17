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

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_UTILS_DATA_DATAWRITERINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_UTILS_DATA_DATAWRITERINTERFACE_H_

#include <cstddef>
#include <utility>
#include <memory>

#include "MultiAgentExperience/Utils/Data/DataObserverInterface.h"

namespace multiAgentExperience {
namespace utils {
namespace data {

/**
 * A helper interface for actors to write data to data observers.
 */
class DataWriterInterface {
public:
    /**
     * Destructor
     */
    virtual ~DataWriterInterface() = default;

    /**
     * Writes data to the observers.
     *
     * @param buffer The buffer to provide to the observer.
     * @param numWords The size in words of the data. The word size must be well known.
     * @return A bool if the data was accepted, and the amount of data written.
     */
    virtual std::pair<bool, std::size_t> write(const void* buffer, std::size_t numWords) = 0;

    /**
     * Add an observer to receive any data written to the writer.
     * @param observer The observer to add.
     */
    virtual void addObserver(std::shared_ptr<DataObserverInterface> observer) = 0;

    /**
     * Remove an observer from receiving any data written to the writer.
     * @param observer The observer to remove.
     */
    virtual void removeObserver(std::shared_ptr<DataObserverInterface> observer) = 0;
};

}  // namespace data
}  // namespace utils
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_UTILS_DATA_DATAWRITERINTERFACE_H_
