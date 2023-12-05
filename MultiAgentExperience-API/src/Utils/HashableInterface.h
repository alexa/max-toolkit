/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_UTILS_HASHABLEINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_UTILS_HASHABLEINTERFACE_H_

namespace multiAgentExperience {
namespace utils {

/**
 * @brief The HashableInterface class defines an interface for objects that can be hashed.
 *
 * This interface provides a default implementation of the getHash() method,
 * which generates a hash value based on the memory address of the object.
 * Derived classes can override this method to provide custom hash calculation logic.
 */
class HashableInterface {
public:
    /**
     * Destructor.
     */
    virtual ~HashableInterface() = default;

    /**
     * Get the hash value of the object, based on its memory address.
     *
     * @return The hash value of the object.
     */
    virtual std::size_t getHash() const {
        return std::hash<const void*>()(static_cast<const void*>(this));
    }
};

}  // namespace utils
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_UTILS_HASHABLEINTERFACE_H_
