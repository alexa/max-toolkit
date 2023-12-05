/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "MultiAgentExperience/Thread/Executor/Threading/PowerResource.h"

namespace multiAgentExperience {
namespace thread {
namespace executor {
namespace threading {

static const std::string MODULE_TAG("PowerResource");
#define LX(logCommand, message) std::cout << #logCommand << ":" << MODULE_TAG << ":" << __func__ << ":" << message << std::endl;

std::shared_ptr<PowerResource> PowerResource::create(
        const std::string& identifier,
        std::shared_ptr<PowerResourceManagerInterface> powerManager,
        PowerResourceManagerInterface::PowerResourceLevel level,
        bool refCounted) {
    if (!powerManager) {
        LX(ERROR, "nullPowerManager");
        return nullptr;
    }

    return std::shared_ptr<PowerResource>(new PowerResource(identifier, powerManager, level, refCounted));
}

PowerResource::~PowerResource() {
    LX(DEBUG3, "");

    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_isFrozen) {
        LX(WARN, "isFrozen");
    }

    if (m_powerManager) {
        for (uint64_t i = 0; i < m_refCount; i++) {
            m_powerManager->release(m_powerResourceId);
        }
    }

    m_powerManager->close(m_powerResourceId);
}

PowerResource::PowerResource(
        const std::string& identifier,
        std::shared_ptr<PowerResourceManagerInterface> powerManager,
        PowerResourceManagerInterface::PowerResourceLevel level,
        bool refCounted) :
        m_identifier{identifier},
        m_prefixedIdentifier{std::string(PREFIX) + m_identifier},
        m_isRefCounted{refCounted},
        m_refCount{0},
        m_level{level},
        m_isFrozen{false},
        m_powerManager{powerManager} {
    m_powerResourceId = m_powerManager->create(m_prefixedIdentifier, m_isRefCounted, m_level);
    if (!m_powerResourceId) {
        LX(DEBUG3, "reason : createFailed in method PowerResourceManagerInterface::create");
    }
}

bool PowerResource::isRefCounted() const {
    LX(DEBUG3, "id : " + m_identifier);

    return m_isRefCounted;
}

std::string PowerResource::getId() const {
    LX(DEBUG3, "id : " + m_identifier);

    return m_identifier;
}

bool PowerResource::isFrozen() const {
    std::lock_guard<std::mutex> lock(m_mutex);

    LX(DEBUG3, "id : " + m_identifier + " isFrozen : " + std::to_string(m_isFrozen) + " refCount : "
                                                                                      "" +
               std::to_string(m_refCount));

    return m_isFrozen;
}

PowerResourceManagerInterface::PowerResourceLevel PowerResource::getLevel() const {
    LX(DEBUG3, "id : " + m_identifier);

    std::lock_guard<std::mutex> lock(m_mutex);
    return m_level;
}

void PowerResource::acquire() {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_isFrozen) {
        LX(DEBUG3, "reason : frozen");

        return;
    }

    if (m_powerManager) {
        if (m_isRefCounted) {
            m_refCount++;
        } else {
            m_refCount = 1;
        }

        m_powerManager->acquire(m_powerResourceId);
    }

    LX(DEBUG3, "id : " + m_identifier + "refCount : " + std::to_string(m_refCount));
}

void PowerResource::release() {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_isFrozen) {
        LX(DEBUG3, "reason : frozen");

        return;
    }

    if (m_powerManager) {
        if (m_isRefCounted) {
            if (m_refCount > 0) {
                m_refCount--;
            }
        } else {
            m_refCount = 0;
        }

        m_powerManager->release(m_powerResourceId);
    }

    LX(DEBUG3, "id : " + m_identifier + "refCount : " + std::to_string(m_refCount));
}

void PowerResource::freeze() {
    LX(DEBUG3, "id : " + m_identifier + "refCount : " + std::to_string(m_refCount));

    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_isFrozen) {
        LX(DEBUG3, "reason : alreadyFrozen");

        return;
    }

    if (m_powerManager) {
        m_isFrozen = true;

        for (uint64_t i = 0; i < m_refCount; i++) {
            m_powerManager->release(m_powerResourceId);
        }
    }
}

void PowerResource::thaw() {
    LX(DEBUG3, "id : " + m_identifier + "refCount : " + std::to_string(m_refCount));

    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_isFrozen) {
        LX(DEBUG3, "reason : notFrozen");

        return;
    }

    if (m_powerManager) {
        for (uint64_t i = 0; i < m_refCount; i++) {
            m_powerManager->acquire(m_powerResourceId);
        }
    }

    m_isFrozen = false;
}

} // threading
} // executor
} // thread
} // multiAgentExperience