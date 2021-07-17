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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITY_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITY_H_

#include <memory>

#include "ActivityID.h"
#include "Control/ControlRegistry.h"

namespace multiAgentExperience {
namespace library {
namespace activity {

class Activity {
public:
    Activity();

    virtual ~Activity() = default;

    void onRequestGranted(const ActivityID id);

    virtual void onControlRegistryAvailable(std::shared_ptr<control::ControlRegistry> controlRegistry);

    virtual void onForeground() = 0;

    virtual void onBackground() = 0;

    virtual void onStop() = 0;

    const ActivityID getID();

private:
    ActivityID m_id;
};

}  // namespace activity
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_ACTIVITY_ACTIVITY_H_
