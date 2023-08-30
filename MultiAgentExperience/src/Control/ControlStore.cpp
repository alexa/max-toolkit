/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <list>

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Control/ControlStore.h"

#include "Control/ControlAccessKeys.h"
#include "Control/Control.h"

namespace multiAgentExperience {
namespace library {
namespace control {

static const std::string MODULE_TAG("ControlStore");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

struct ControlRecord {
    ControlRecord(ControlPriority priority, std::shared_ptr<Control> control, ControlAccessKey controlAccessKey) :
            m_priority{priority},
            m_control{control},
            m_controlAccessKey{controlAccessKey}{
    }

    ControlPriority m_priority;
    std::shared_ptr<Control> m_control;
    ControlAccessKey m_controlAccessKey;
};

struct CompareControlRecordsByPriority {
    bool operator()(const ControlRecord& lhs, const ControlRecord& rhs) const {
        return lhs.m_priority < rhs.m_priority;
    }
};

struct CompareControlRecordsByPriorityAndAccessKey {
    bool operator()(const ControlRecord& lhs, const ControlRecord& rhs) const {
        // We need to sort Controls by lowest value of ControlPriority and highest value of ControlAccessKey.
        // Hence, ControlPriority of lhs is paired up with ControlAccessKey of rhs, and vice-versa.

        return std::tie(lhs.m_priority, rhs.m_controlAccessKey)
               < std::tie(rhs.m_priority, lhs.m_controlAccessKey);
    }
};

ControlStore::ControlStore(std::shared_ptr<ControlAccessKeys> controlAccessKeys) :
        m_controlAccessKeys{controlAccessKeys},
        m_controlsMutex{},
        m_controls{},
        m_controlPriorities{},
        m_activityIds{} {
}

void ControlStore::store(
    const ControlAccessKey controlAccessKey,
    const activity::ActivityID& activityId,
    const ControlPriority controlPriority,
    std::unordered_set<std::shared_ptr<Control>> controls) {
    LX(DEBUG3, "");
    if (m_controlAccessKeys->hasAccess(controlAccessKey)) {
        std::unique_lock<std::mutex> lock(m_controlsMutex);
        if (controls.empty()) {
            m_controls.erase(controlAccessKey);
            m_activityIds.erase(controlAccessKey);
            m_controlPriorities.erase(controlAccessKey);
        } else {
            m_controls.insert(std::make_pair(controlAccessKey, controls));
            m_activityIds.insert(std::make_pair(controlAccessKey, activityId));
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
        m_activityIds.erase(controlAccessKey);
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
            for (auto& control : controlsSet) {
                if (control->getName() == controlName) {
                    auto priority = m_controlPriorities[accessKey];
                    controlRecordsOfName.emplace_back(priority, control, accessKey);
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
    std::size_t currentSize = 0;
    {
        std::unique_lock<std::mutex> lock(m_controlsMutex);
        before.insert(m_currentControlNamesUnion.begin(), m_currentControlNamesUnion.end());
        m_currentControlNamesUnion.clear();
        for (auto const& entry : m_controls) {
            auto controls = entry.second;
            for (auto const& control : controls) {
                m_currentControlNamesUnion.insert(control->getName());
            }
        }
        currentSize = m_currentControlNamesUnion.size();
    }

    if (before.size() != currentSize) {
        notifyObservers();
        return;
    }

    {
        std::unique_lock<std::mutex> lock(m_controlsMutex);
        for (auto controlName : m_currentControlNamesUnion) {
            before.erase(controlName);
        }
    }

    if (!before.empty()) {
        notifyObservers();
    }
}

void ControlStore::notifyObservers() {
    if (!m_observers.empty()) {
        std::list<std::shared_ptr<ControlStoreObserverInterface>> observers(m_observers);
        std::unordered_set<ControlName> copy;
        {
            std::unique_lock<std::mutex> lock(m_controlsMutex);
            copy.insert(m_currentControlNamesUnion.begin(), m_currentControlNamesUnion.end());
        }

        for (auto& observer : observers) {
            observer->onControlsUpdated(copy);
        }
    }
}

std::unordered_map<ControlName, std::weak_ptr<Control>> filterHighestPriorityControls(std::unordered_map<ControlName, std::list<ControlRecord>>& controlRecords) {
    std::unordered_map<ControlName, std::weak_ptr<Control>> requestedControls;

    for (auto &entry: controlRecords) {
        auto curName = entry.first;
        auto curControlRecords = entry.second;

        // For Alerts, there is a possibility that two controls have same priority.
        // The next check is for such a case.
        // If this happens, we will consider the latest control that is present.
        // Right now, we will use the ControlAccessKey to decide this.
        // But in future if we find more such cases, we can invest on finding a more robust mechanism to do this.

        curControlRecords.sort(CompareControlRecordsByPriorityAndAccessKey());

        requestedControls.insert(std::make_pair(curName, curControlRecords.front().m_control));
    }

    return requestedControls;
}

std::unordered_map<ControlName, std::weak_ptr<Control>> ControlStore::getControlsOfActivity(
    const ControlAccessKey& controlAccessKey,
    const activity::ActivityID& activityId) {
    LX(DEBUG3, "");
    std::unordered_map<ControlName, std::list<ControlRecord>> availableControlRecords;

    if (m_controlAccessKeys->hasAccess(controlAccessKey)) {
        std::unique_lock<std::mutex> lock(m_controlsMutex);

        for (auto& entry : m_controls) {
            auto curAccessKey = entry.first;
            auto controlsSet = entry.second;
            auto curActivityId = m_activityIds[curAccessKey];
            auto curControlPriority = m_controlPriorities[curAccessKey];

            for (auto& control: controlsSet) {
                if (activityId == curActivityId) {
                    availableControlRecords[control->getName()].emplace_back(curControlPriority, control, curAccessKey);
                }
            }
        }
    }

    return filterHighestPriorityControls(availableControlRecords);
}

}  // namespace control
}  // namespace library
}  // namespace multiAgentExperience
