/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/
#ifndef MULTI_AGENT_EXPERIENCE_THREADING_THREADEXECUTOR_POWERRESOURCE_H_
#define MULTI_AGENT_EXPERIENCE_THREADING_THREADEXECUTOR_POWERRESOURCE_H_

#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <iostream>

#include "PowerResourceManagerInterface.h"

namespace multiAgentExperience {
namespace thread {
namespace executor {
namespace threading {

/**
 * NOTE : This implementation has been picked up from : https://tiny.amazon.com/11pma85ev/codeamazpackCtdlblobmastUtil
 *        and might need to be moved to the "MultiAgentExperience-Testable-Device-Agent-API"
 *        package in the future
 *
 * An object representing a configuration of power level preferences.
 *
 * Behavior is undefined if direct calls are made to @c PowerResourceManagerInterface using
 * the same component identifier as one associated with a @c PowerResource object.
 */
class PowerResource {
public:
    /**
     * Destructor. This will release all acquired instances.
     */
    ~PowerResource();

    /**
     * Prefix that will be internally appended before calling @c PowerResourceManagerInterface.
     */
    static constexpr const char* PREFIX = "ACSDK_";

    /**
     * Creates an instance of the @c PowerResource.
     *
     * @param identifier The identifier. This identifier must be unique across all instances, as it will be used
     * to call the underlying @c PowerResourceManagerInterface. This will be prefixed internally with
     * ACSDK_ to maintain uniqueness within @c PowerResourceManagerInterface.
     * @param powerManager A pointer to the underlying @c PowerResourceManagerInterface.
     * @param level The level to create this resource with.
     * @param refCounted Whether refcounting is enabled.
     *
     * @return An instance.
     */
    static std::shared_ptr<PowerResource> create(
            const std::string& identifier,
            std::shared_ptr<multiAgentExperience::thread::executor::threading::PowerResourceManagerInterface>
            powerManager,
            PowerResourceManagerInterface::PowerResourceLevel level =
            PowerResourceManagerInterface::PowerResourceLevel::STANDBY_MED,
            bool refCounted = true);

    /**
     * Returns the id. This will equal the identifier passed into the constructor without the internal prefix.
     *
     * @return A string representing the id.
     */
    std::string getId() const;

    /**
     * Returns whether the current resource is refCounted.
     *
     * @return A bool indicating refCount state.
     */
    bool isRefCounted() const;

    /**
     * Returns whether the current resource is frozen.
     *
     * @return A bool indicating frozen state.
     */
    bool isFrozen() const;

    /**
     * Get the current level.
     *
     * @return The current level.
     */
    PowerResourceManagerInterface::PowerResourceLevel getLevel() const;

    /**
     * Acquire a count of the resource.
     */
    void acquire();

    /**
     * Release a count of the resource.
     */
    void release();

    /**
     * Freezes the resource, and caches the current refcount. Any calls to acquire or release will no-op while
     * the @c PowerResource is frozen.
     */
    void freeze();

    /**
     * Thaws the resource, and re-acquires the amount of times the resource has been acquired.
     */
    void thaw();

private:
    /**
     * Constructor
     *
     * @param identifier The identifier.
     * @param powerManager A pointer to the underlying @c PowerResourceManagerInterface.
     * @param level The level to create this resource with.
     * @param refCounted Whether refcounting is enabled.
     */
    PowerResource(
            const std::string& identifier,
            std::shared_ptr<PowerResourceManagerInterface> powerManager,
            PowerResourceManagerInterface::PowerResourceLevel level,
            bool refCounted);

    /// Identifier name.
    const std::string m_identifier;

    /// Identifier name with PREFIX for calling @c PowerResourceManagerInterface.
    const std::string m_prefixedIdentifier;

    /// Whether this resource is refCounted.
    const bool m_isRefCounted;

    /// The PowerResourceId object used to call @c PowerResourceManagerInterface.
    std::shared_ptr<PowerResourceManagerInterface::PowerResourceId> m_powerResourceId;

    /// Thread safety.
    mutable std::mutex m_mutex;

    /// The current refCount.
    uint64_t m_refCount;

    /// Level of the resource. Can be modified as different components may wish to obtain different levels.
    PowerResourceManagerInterface::PowerResourceLevel m_level;

    /// Whether whether the @c PowerResource is frozen.
    bool m_isFrozen;

    /// The underlying @c PowerResourceManagerInterface
    std::shared_ptr<PowerResourceManagerInterface> m_powerManager;
};

} // threading
} // executor
} // thread
} // multiAgentExperience

#endif // MULTI_AGENT_EXPERIENCE_THREADING_THREADEXECUTOR_POWERRESOURCE_H_