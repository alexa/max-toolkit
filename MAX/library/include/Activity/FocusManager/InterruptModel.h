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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGER_INTERRUPTMODEL_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGER_INTERRUPTMODEL_H_

#include <map>
#include <memory>

#include "ContentType.h"
#include "MixingBehavior.h"

namespace multiAgentExperience {
namespace library {
namespace activity {
/**
 * This class contains the interrupt model implementation
 * for the device. This class uses the @c InterruptModelConfiguration
 * passed in during creation to determine the MixingBehavior
 * During Focus State transitions, the AFML shall invoke this class to
 * determine the MixingBehavior to be taken by the ChannelObservers
 * corresponding to the lower priority channel being backgrounded when
 * a higher priority channel barges-in.
 */
class InterruptModel {
public:
    /**
     * Creates an instance of @c InterruptModel
     * @param interactionConfiguration interrupt model configuration for device.
     * @return instance of @c InterruptModel.
     */
    static std::shared_ptr<InterruptModel> create();

    /**
     * get Mixing Behavior for the lower priority channel
     * @param lowPriorityChannel the lower priority channel
     * @param lowPriorityContentType the current content type
     * @param highPriorityChannel the channel barging in
     * @param highPriorityContentType the content type barging in
     * @return MixingBehavior which must be taken by the lower priority channel
     */
    MixingBehavior getMixingBehavior(
        const std::string& lowPriorityChannel,
        ContentType lowPriorityContentType,
        const std::string& highPriorityChannel,
        ContentType highPriorityContentType) const;
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_FOCUSMANAGER_INTERRUPTMODEL_H_
