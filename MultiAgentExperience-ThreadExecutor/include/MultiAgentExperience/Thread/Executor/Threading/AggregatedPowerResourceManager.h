/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/
#ifndef MULTI_AGENT_EXPERIENCE_THREADING_THREADEXECUTOR_AGGREGATEDPOWERRESOURCEMANAGER_H_
#define MULTI_AGENT_EXPERIENCE_THREADING_THREADEXECUTOR_AGGREGATEDPOWERRESOURCEMANAGER_H_

#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <iostream>

#include "hash.h"
#include "PowerResourceManagerInterface.h"

namespace multiAgentExperience {
namespace thread {
namespace executor {
namespace threading {

/**
 * NOTE : This implementation has been picked up from : https://tiny.amazon.com/o3oxqm81/codeamazpackCtdlblobmastUtil
 *        and might need to be moved to the "MultiAgentExperience-Testable-Device-Agent-API"
 *        package in the future
 *
 * An AVS SDK implementation of @c PowerResourceManagerInterface which aggregates calls to the application provided
 * @c PowerResourceManagerInterface. This implementation creates a @c PowerResourceManagerInterface::PowerResourceId
 * for each @c PowerResourceLevel, and maps acquire/release/etc calls down to each level-aggregated @c PowerResourceId.
 *
 * This reduces the number of resources that are created from the perspective of the application provided @c
 * PowerResourceManagerInterface. Additionally, it allows optimizations (such as deduping calls to reference counted
 * resources) to be more effective.
 *
 * To reduce latency associated with create/close, aggregated PowerResourceIds are not closed dynamically, and will
 * persist for the lifetime of the @c AggregatedPowerResourceManager.
 *
 * This class does not aggregate the acquirePowerResource/releasePowerResource related APIs.
 */
class AggregatedPowerResourceManager : public PowerResourceManagerInterface {
public:
    /**
     * Create an instance of this class.
     *
     * @param powerResourceManager The application provided @c PowerResourceManagerInterface.
     * @return An instance if successful, else nullptr.
     */
    static std::shared_ptr<AggregatedPowerResourceManager> create(
            std::shared_ptr<PowerResourceManagerInterface> powerResourceManager);

    /// Destructor.
    virtual ~AggregatedPowerResourceManager();

    /// @name PowerResourceManagerInterface Legacy Methods
    /// @{
    void acquirePowerResource(
            const std::string& component,
            const PowerResourceLevel level = PowerResourceLevel::STANDBY_MED) override;
    void releasePowerResource(const std::string& component) override;
    bool isPowerResourceAcquired(const std::string& component) override;
    std::shared_ptr<PowerResourceManagerInterface::PowerResourceId> create(
            const std::string& resourceId,
            bool isRefCounted = true,
            const PowerResourceLevel level = PowerResourceLevel::STANDBY_MED) override;
    bool acquire(
            const std::shared_ptr<PowerResourceManagerInterface::PowerResourceId>& id,
            const std::chrono::milliseconds autoReleaseTimeout = std::chrono::milliseconds::zero()) override;
    bool release(
            const std::shared_ptr<PowerResourceManagerInterface::PowerResourceId>& id) override;
    bool close(
            const std::shared_ptr<PowerResourceManagerInterface::PowerResourceId>& id) override;
    /// @}

private:
    /// This is used to key aggregated PowerResourceId to the level it is aggregated by.
    using AggregatedPowerResourceMap = std::unordered_map<
            PowerResourceManagerInterface::PowerResourceLevel,
            std::shared_ptr<PowerResourceManagerInterface::PowerResourceId>,
            EnumClassHash>;

    /**
     * A struct to track reference counting preference and level for a @c
     * PowerResourceManagerInterface::PowerResourceId.
     */
    struct PowerResourceInfo {
        /**
         * Constructor.
         *
         * @param isRefCounted Whether this resource is reference counted.
         * @param level The power level.
         */
        PowerResourceInfo(
                bool isRefCounted,
                PowerResourceManagerInterface::PowerResourceLevel level);

        /// Whether this resource is reference counted.
        const bool isRefCounted;

        /// The power level.
        const PowerResourceManagerInterface::PowerResourceLevel level;

        /// The current refCount.
        uint64_t refCount;
    };

    /**
     * Constructor
     *
     * @param powerResourceManager The application provided @c PowerResourceManagerInterface.
     */
    AggregatedPowerResourceManager(
            std::shared_ptr<PowerResourceManagerInterface> powerResourceManager);

    /**
     * Generates a @c PowerResourceId for the given power level. If it already exists, this function will return
     * the previously created @c PowerResourceId for the given power level. The lock must be held.
     *
     * @param level The level to create an aggregated object for.
     */
    std::shared_ptr<PowerResourceId> getAggregatedPowerResourceIdLocked(
            const PowerResourceManagerInterface::PowerResourceLevel level);

    /// A mutex for synchronization.
    std::mutex m_mutex;

    /// The underlying application provided @c PowerResourceManagerInterface.
    std::shared_ptr<PowerResourceManagerInterface> m_appPowerResourceManager;

    /// A map of string resource identifier to PowerResourceInfo. The string is stored from the unique id passed into
    /// the PowerResourceManagerInterface::create call.
    std::unordered_map<std::string, PowerResourceInfo> m_ids;

    /// The map of @c PowerResourceId objects that are grouped by level.
    AggregatedPowerResourceMap m_aggregatedPowerResources;
};

} // threading
} // executor
} // thread
} // multiAgentExperience

#endif // MULTI_AGENT_EXPERIENCE_THREADING_THREADEXECUTOR_AGGREGATEDPOWERRESOURCEMANAGER_H_