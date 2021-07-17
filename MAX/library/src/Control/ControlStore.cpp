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

#include <list>

#include "Control/ControlStore.h"

#include "Control/ControlAccessKeys.h"
#include "Control/Control.h"
#include "Utils/Logger/Logger.h"

namespace multiAgentExperience {
namespace library {
namespace control {

static const std::string MODULE_TAG("ControlStore");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

struct ControlRecord {
    ControlRecord(ControlPriority priority, std::shared_ptr<Control> control) :
            m_priority{priority},
            m_control{control} {
    }

    ControlPriority m_priority;
    std::shared_ptr<Control> m_control;
};

struct CompareControlRecordsByPriority {
    bool operator()(const ControlRecord& lhs, const ControlRecord& rhs) const {
        return lhs.m_priority < rhs.m_priority;
    }
};

ControlStore::ControlStore(std::shared_ptr<ControlAccessKeys> controlAccessKeys) :
        m_controlAccessKeys{controlAccessKeys},
        m_controlsMutex{},
        m_controls{},
        m_controlPriorities{} {
}

void ControlStore::store(
    const ControlAccessKey controlAccessKey,
    const ControlPriority controlPriority,
    std::unordered_set<std::shared_ptr<Control>> controls) {
    LX(DEBUG3, "");
    if (m_controlAccessKeys->hasAccess(controlAccessKey)) {
        std::unique_lock<std::mutex> lock(m_controlsMutex);
        if (controls.empty()) {
            m_controls.erase(controlAccessKey);
            m_controlPriorities.erase(controlAccessKey);
        } else {
            m_controls.insert(std::make_pair(controlAccessKey, controls));
            m_controlPriorities.insert(std::make_pair(controlAccessKey, controlPriority));
        }
    }

    computeUnionOfControlNames();
}

bool ControlStore::contains(const ControlAccessKey& controlAccessKey) {
    LX(DEBUG3, "");

    if (m_controlAccessKeys->hasAccess(controlAccessKey)) {
        std::unique_lock<std::mutex> lock(m_controlsMutex);
        return m_controls.find(controlAccessKey) != m_controls.end();
    }
    return false;
}

void ControlStore::remove(const ControlAccessKey& controlAccessKey) {
    LX(DEBUG3, "");
    {
        std::unique_lock<std::mutex> lock(m_controlsMutex);
        // no need to check access as this operation is always allowed.
        m_controls.erase(controlAccessKey);
        m_controlPriorities.erase(controlAccessKey);
    }
    computeUnionOfControlNames();
}

void ControlStore::revokeAccess(const ControlAccessKey& controlAccessKey) {
    LX(DEBUG3, "");

    remove(controlAccessKey);
    m_controlAccessKeys->revokeAccess(controlAccessKey);
}

std::unordered_set<ControlName> ControlStore::getUnionOfControlNames(const ControlAccessKey& controlAccessKey) {
    LX(DEBUG3, "");

    if (m_controlAccessKeys->hasAccess(controlAccessKey)) {
        std::unique_lock<std::mutex> lock(m_controlsMutex);
        return m_currentControlNamesUnion;
    }
    return std::unordered_set<ControlName>();
}

std::shared_ptr<Control> ControlStore::getHighestPriorityControlByName(
    const ControlAccessKey& controlAccessKey,
    const ControlName& controlName) {
    LX(DEBUG3, "");

    std::list<ControlRecord> controlRecordsOfName;
    if (!m_controlAccessKeys->hasAccess(controlAccessKey)) {
        return nullptr;
    }

    {
        std::unique_lock<std::mutex> lock(m_controlsMutex);
        for (auto& entry : m_controls) {
            auto accessKey = entry.first;
            auto controlsSet = entry.second;
            for (auto control : controlsSet) {
                if (control->getName() == controlName) {
                    auto priority = m_controlPriorities[accessKey];
                    controlRecordsOfName.emplace_back(priority, control);
                }
            }
        }
    }

    if (controlRecordsOfName.empty()) {
        return nullptr;
    }

    controlRecordsOfName.sort(CompareControlRecordsByPriority());
    return controlRecordsOfName.front().m_control;
}

void ControlStore::addObserver(std::shared_ptr<ControlStoreObserverInterface> observer) {
    m_observers.push_back(observer);
    observer->onControlsUpdated(m_currentControlNamesUnion);
}

void ControlStore::removeObserver(std::shared_ptr<ControlStoreObserverInterface> observer) {
    m_observers.remove(observer);
}

void ControlStore::clearObservers() {
    m_observers.clear();
}

void ControlStore::computeUnionOfControlNames() {
    std::unordered_set<ControlName> before;
    before.insert(m_currentControlNamesUnion.begin(), m_currentControlNamesUnion.end());

    {
        std::unique_lock<std::mutex> lock(m_controlsMutex);
        m_currentControlNamesUnion.clear();
        for (auto const& entry : m_controls) {
            auto controls = entry.second;
            for (auto const& control : controls) {
                m_currentControlNamesUnion.insert(control->getName());
            }
        }
    }

    if (before.size() != m_currentControlNamesUnion.size()) {
        notifyObservers();
        return;
    }

    for (auto controlName : m_currentControlNamesUnion) {
        before.erase(controlName);
    }

    if (!before.empty()) {
        notifyObservers();
    }
}

void ControlStore::notifyObservers() {
    if (!m_observers.empty()) {
        std::list<std::shared_ptr<ControlStoreObserverInterface>> observers(m_observers);
        for (auto observer : observers) {
            observer->onControlsUpdated(m_currentControlNamesUnion);
        }
    }
}

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience
