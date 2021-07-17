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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLSTORE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLSTORE_H_

#include <list>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <unordered_set>

#include "Control.h"
#include "ControlAccessKeys.h"
#include "ControlAccessKey.h"
#include "ControlName.h"
#include "ControlPriority.h"
#include "ControlStoreObserverInterface.h"

namespace multiAgentExperience {
namespace library {
namespace control {

class ControlStore {
public:
    ControlStore(std::shared_ptr<ControlAccessKeys> controlAccessKeys);

    void addObserver(std::shared_ptr<ControlStoreObserverInterface> observer);

    void removeObserver(std::shared_ptr<ControlStoreObserverInterface> observer);

    void clearObservers();

    void store(
        ControlAccessKey controlAccessKey,
        const ControlPriority controlPriority,
        std::unordered_set<std::shared_ptr<Control>> controls);

    bool contains(const ControlAccessKey& controlAccessKey);

    void remove(const ControlAccessKey& controlAccessKey);

    void revokeAccess(const ControlAccessKey& controlAccessKey);

    std::unordered_set<ControlName> getUnionOfControlNames(const ControlAccessKey& controlAccessKey);

    std::shared_ptr<Control> getHighestPriorityControlByName(
        const ControlAccessKey& controlAccessKey,
        const ControlName& controlName);

private:
    std::list<std::shared_ptr<ControlStoreObserverInterface>> m_observers;
    std::shared_ptr<ControlAccessKeys> m_controlAccessKeys;
    std::mutex m_controlsMutex;
    std::unordered_map<ControlAccessKey, std::unordered_set<std::shared_ptr<Control>>> m_controls;
    std::unordered_map<ControlAccessKey, ControlPriority> m_controlPriorities;
    std::unordered_set<ControlName> m_currentControlNamesUnion;

    void computeUnionOfControlNames();

    void notifyObservers();
};

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CONTROL_CONTROLSTORE_H_
