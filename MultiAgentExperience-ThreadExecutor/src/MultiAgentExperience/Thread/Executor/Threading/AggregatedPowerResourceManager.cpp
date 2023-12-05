/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/Thread/Executor/Threading/AggregatedPowerResourceManager.h"

namespace multiAgentExperience {
namespace thread {
namespace executor {
namespace threading {

/// String to identify log entries originating from this file.
static const std::string MODULE_TAG("AggregatedPowerResourceManager");
#define LX(logCommand, message) std::cout << #logCommand << ":" << MODULE_TAG << ":" << __func__ << ":" << message << std::endl;

/// Prefix to uniquely identify the resource.
static const std::string PREFIX = "ACSDK_";

AggregatedPowerResourceManager::PowerResourceInfo::PowerResourceInfo(
        bool isRefCounted,
        PowerResourceManagerInterface::PowerResourceLevel level) :
        isRefCounted{isRefCounted},
        level{level},
        refCount{0} {
}

std::shared_ptr<AggregatedPowerResourceManager> AggregatedPowerResourceManager::create(
        std::shared_ptr<PowerResourceManagerInterface> powerResourceManager) {
    LX(DEBUG3, "");

    if (!powerResourceManager) {
        LX(ERROR, "reason : nullPowerResourceManager");
        return nullptr;
    } else {
        return std::shared_ptr<AggregatedPowerResourceManager>(
                new AggregatedPowerResourceManager(powerResourceManager));
    }
}

AggregatedPowerResourceManager::~AggregatedPowerResourceManager() {
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto it : m_aggregatedPowerResources) {
        auto id = it.second;
        m_appPowerResourceManager->close(id);
    }
}

AggregatedPowerResourceManager::AggregatedPowerResourceManager(
        std::shared_ptr<PowerResourceManagerInterface> powerResourceManager) :
        m_appPowerResourceManager{powerResourceManager} {
}

void AggregatedPowerResourceManager::acquirePowerResource(
        const std::string& component,
        const PowerResourceLevel level) {
    LX(DEBUG3, "");

    std::lock_guard<std::mutex> lock(m_mutex);
    m_appPowerResourceManager->acquirePowerResource(component, level);
}

void AggregatedPowerResourceManager::releasePowerResource(const std::string& component) {
    LX(DEBUG3, "");

    std::lock_guard<std::mutex> lock(m_mutex);
    m_appPowerResourceManager->releasePowerResource(component);
};

bool AggregatedPowerResourceManager::isPowerResourceAcquired(const std::string& component) {
    LX(DEBUG3, "");

    std::lock_guard<std::mutex> lock(m_mutex);
    return m_appPowerResourceManager->isPowerResourceAcquired(component);
}

std::shared_ptr<PowerResourceManagerInterface::PowerResourceId> AggregatedPowerResourceManager::
getAggregatedPowerResourceIdLocked(const PowerResourceManagerInterface::PowerResourceLevel level) {
    LX(DEBUG3, "");

    auto it = m_aggregatedPowerResources.find(level);
    if (m_aggregatedPowerResources.end() != it) {
        return it->second;
    }

    LX(DEBUG0, "reason : generatingNewAggregateResource level : ")
    // ACSDK_DEBUG0(LX(__func__).d("reason", "generatingNewAggregateResource").d("level", level));

    auto aggregatedPowerResourceId =
            m_appPowerResourceManager->create(PREFIX + powerResourceLevelToString(level), true, level);

    m_aggregatedPowerResources.insert({level, aggregatedPowerResourceId});
    return aggregatedPowerResourceId;
}

std::shared_ptr<PowerResourceManagerInterface::PowerResourceId> AggregatedPowerResourceManager::create(
        const std::string& resourceId,
        bool isRefCounted,
        const PowerResourceManagerInterface::PowerResourceLevel level) {
    LX(DEBUG3, "id : " + resourceId);

    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_ids.count(resourceId) != 0) {
        LX(ERROR, "reason : resourceIdExists id : " + resourceId);
        return nullptr;
    }

    m_ids.insert({resourceId, PowerResourceInfo(isRefCounted, level)});

    getAggregatedPowerResourceIdLocked(level);

    auto powerId = std::make_shared<PowerResourceId>(resourceId);
    return powerId;
}

bool AggregatedPowerResourceManager::acquire(
        const std::shared_ptr<PowerResourceId>& id,
        const std::chrono::milliseconds autoReleaseTimeout) {
    if (!id) {
        LX(ERROR, "reason : nullId");
        return false;
    }

    LX(DEBUG3, "id : " + id->getResourceId());
    std::lock_guard<std::mutex> lock(m_mutex);

    auto callerIt = m_ids.find(id->getResourceId());
    if (m_ids.end() == callerIt) {
        LX(ERROR, "reason : nonExistentId id : " + id->getResourceId());
        return false;
    }

    auto& callerPowerResourceInfo = callerIt->second;
    std::shared_ptr<PowerResourceId> aggregatedPowerResourceId =
            getAggregatedPowerResourceIdLocked(callerPowerResourceInfo.level);

    // Do not handle any auto release timer cases.
    if (autoReleaseTimeout != std::chrono::milliseconds::zero()) {
        return m_appPowerResourceManager->acquire(aggregatedPowerResourceId, autoReleaseTimeout);
    }

    // Do not dedupe  acquire calls if refcount enabled. Let the application PowerResourceManagerInterface
    // handle that if desired.
    if (callerPowerResourceInfo.isRefCounted || callerPowerResourceInfo.refCount == 0) {
        callerPowerResourceInfo.refCount++;
        m_appPowerResourceManager->acquire(aggregatedPowerResourceId);
    }

    return true;
}

bool AggregatedPowerResourceManager::release(const std::shared_ptr<PowerResourceId>& id) {
    if (!id) {
        LX(ERROR, "reason : nullId");
        return false;
    }

    std::lock_guard<std::mutex> lock(m_mutex);
    LX(DEBUG3, "id : " + id->getResourceId());

    auto callerIt = m_ids.find(id->getResourceId());
    if (m_ids.end() == callerIt) {
        LX(ERROR, "reason : nonExistentId id : " + id->getResourceId());
        return false;
    }

    auto& callerPowerResourceInfo = callerIt->second;
    std::shared_ptr<PowerResourceId> aggregatedPowerResourceId =
            getAggregatedPowerResourceIdLocked(callerPowerResourceInfo.level);

    if (callerPowerResourceInfo.refCount > 0) {
        callerPowerResourceInfo.refCount--;
        m_appPowerResourceManager->release(aggregatedPowerResourceId);
    }

    return true;
}

bool AggregatedPowerResourceManager::close(const std::shared_ptr<PowerResourceId>& id) {
    if (!id) {
        LX(ERROR, "reason : nullId");
        return false;
    }

    std::lock_guard<std::mutex> lock(m_mutex);
    const std::string idString = id->getResourceId();
    LX(DEBUG3, "id : " + id->getResourceId());

    auto callerIt = m_ids.find(idString);
    if (m_ids.end() == callerIt) {
        LX(ERROR, "reason : nonExistentId id : " + idString);
        return false;
    }

    auto& callerPowerResourceInfo = callerIt->second;
    auto level = callerPowerResourceInfo.level;

    std::shared_ptr<PowerResourceId> aggregatedPowerResourceId = getAggregatedPowerResourceIdLocked(level);

    for (unsigned int i = 0; i < callerPowerResourceInfo.refCount; i++) {
        m_appPowerResourceManager->release(aggregatedPowerResourceId);
    }

    // We do not close the underlying aggregated PowerResource to prevent any latency hit from dynamically
    // creating/closing.
    m_ids.erase(idString);

    return true;
}

} // threading
} // executor
} // thread
} // multiAgentExperience