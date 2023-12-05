/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/Thread/Executor/Threading/AggregatedPowerResourceManager.h"
#include "MultiAgentExperience/Thread/Executor/Threading/PowerMonitor.h"

namespace multiAgentExperience {
namespace thread {
namespace executor {
namespace threading {

/// String to identify log entries originating from this file.
static const std::string MODULE_TAG("PowerMonitor");
#define LX(logCommand, message) std::cout << #logCommand << ":" << MODULE_TAG << ":" << __func__ << ":" << message << std::endl;

std::mutex PowerMonitor::m_mutex;
std::shared_ptr<PowerMonitor> PowerMonitor::m_monitor;

std::shared_ptr<PowerMonitor> PowerMonitor::getInstance() {
    LX(DEBUG3, "");

    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_monitor) {
        PowerMonitor::m_monitor = std::shared_ptr<PowerMonitor>(new PowerMonitor());
    }

    return m_monitor;
}

void PowerMonitor::activate(std::shared_ptr<PowerResourceManagerInterface> powerManager) {
    LX(DEBUG3, "");

    std::lock_guard<std::mutex> lock(m_mutex);
    if (isActiveLocked()) {
        LX(ERROR, "reason : alreadyActive");
        return;
    }

    if (powerManager) {
        m_powerManager = AggregatedPowerResourceManager::create(powerManager);
    } else {
        LX(ERROR, "reason : nullPowerManager");
    }
}

bool PowerMonitor::isActive() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return isActiveLocked();
}

bool PowerMonitor::isActiveLocked() {
    bool active = m_powerManager != nullptr;
    LX(DEBUG3, "isActiveLocked : " + std::to_string(active));
    return active;
}

void PowerMonitor::deactivate() {
    LX(DEBUG3, "");

    std::lock_guard<std::mutex> lock(m_mutex);
    m_powerManager.reset();
    m_threadPowerResources.clear();
}

std::shared_ptr<PowerResourceManagerInterface> PowerMonitor::getPowerResourceManager() {
    LX(DEBUG3, "");

    std::lock_guard<std::mutex> lock(m_mutex);
    return m_powerManager;
}

std::shared_ptr<PowerResource> PowerMonitor::createLocalPowerResource(
        const std::string& identifier,
        PowerResourceManagerInterface::PowerResourceLevel level) {

    LX(DEBUG3, "identifier : " + identifier);

    std::lock_guard<std::mutex> lock(m_mutex);
    if (!isActiveLocked()) {
        return nullptr;
    }

    return PowerResource::create(identifier, m_powerManager, level);
}

std::shared_ptr<PowerResource> PowerMonitor::getThreadPowerResource() {
    /// ToDo : add a log statement here that has std::this_thread::get_id()
    std::lock_guard<std::mutex> lock(m_mutex);

    if (!isActiveLocked()) {
        return nullptr;
    }

    auto threadId = std::this_thread::get_id();
    std::shared_ptr<PowerResource> resource;

    auto it = m_threadPowerResources.find(threadId);
    if (m_threadPowerResources.end() != it) {
        resource = it->second;
    }

    return resource;
}

std::shared_ptr<PowerResource> PowerMonitor::assignThreadPowerResource(std::shared_ptr<PowerResource> powerResource) {
    /// ToDo : add a log statement here that has std::this_thread::get_id()
    //ACSDK_DEBUG9(LX(__func__).d("threadId", std::this_thread::get_id()));

    auto threadId = std::this_thread::get_id();
    std::shared_ptr<PowerResource> ret;

    std::lock_guard<std::mutex> lock(m_mutex);
    if (!isActiveLocked()) {
        return ret;
    } else if (!powerResource) {
        LX(ERROR, "reason : nullPowerResource");
        return ret;
    }

    if (m_threadPowerResources.count(threadId) != 0) {
        auto existingResource = m_threadPowerResources.at(threadId);

        /*ACSDK_ERROR(LX(__func__)
                        .d("threadId", threadId)
                        .d("reason", "threadAlreadyHasResource")
                        .d("resourceId", existingResource->getId()));
                        */
    } else {
        m_threadPowerResources.insert({threadId, powerResource});
        ret = powerResource;
    }

    return ret;
}

std::shared_ptr<PowerResource> PowerMonitor::getThreadPowerResourceOrCreate(
        const std::string& identifier,
        PowerResourceManagerInterface::PowerResourceLevel level) {
    LX(DEBUG3, "");

    if (!isActive()) {
        return nullptr;
    }

    auto powerResource = getThreadPowerResource();

    // Either the wrong identifier was passed in or the thread did not cleanup its resource.
    // Will fail gracefully, but this is not behavior guaranteed by the method.
    if (powerResource && powerResource->getId() != identifier) {
        /*ACSDK_ERROR(LX(__func__)
                        .d("reason", "mismatchedIdentifier")
                        .d("existingIdentifier", powerResource->getId())
                        .d("identifier", identifier)
                        .d("action", "deletingExistingResource")); */

        removeThreadPowerResource();
        powerResource.reset();
    }

    if (!powerResource) {
        std::lock_guard<std::mutex> lock(m_mutex);
        if (!m_powerManager) {
            LX(ERROR, "reason : nullPowerManager");
            return nullptr;
        }

        /*ACSDK_DEBUG9(LX(__func__)
                         .d("reason", "creatingPowerResource")
                         .d("identifier", identifier)
                         .d("threadId", std::this_thread::get_id()));
                         */
        powerResource = PowerResource::create(identifier, m_powerManager, level);

        m_threadPowerResources.insert({std::this_thread::get_id(), powerResource});
    }

    return powerResource;
}

void PowerMonitor::removeThreadPowerResource() {
    //ACSDK_DEBUG9(LX(__func__).d("threadId", std::this_thread::get_id()));
    std::lock_guard<std::mutex> lock(m_mutex);
    m_threadPowerResources.erase(std::this_thread::get_id());
}

} // threading
} // executor
} // thread
} // multiAgentExperience