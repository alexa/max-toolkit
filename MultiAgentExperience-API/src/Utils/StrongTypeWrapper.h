/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_UTILS_STRONGTYPEWRAPPER_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_UTILS_STRONGTYPEWRAPPER_H_

namespace multiAgentExperience {
namespace utils {

/**
 * A Utility class for creating strongly typed aliases/typenames/wrappers of types.
 *
 * e.g:
 *      using Length = StrongTypeWrapper<double, struct WidthTag>
 *      using Area = StrongTypeWrapper<double, struct AreaTag>
 *
 *      Length l = 5.0;
 *      Area a = l; //Compiler error
 *
 * The "Tag" template parameter is used to differentiate wrappers over the same type.
 * It need not be declared or used elsewhere.
 *
 */
template <typename T, typename Tag>
class StrongTypeWrapper {
public:
    explicit StrongTypeWrapper(T const& value) : m_value(value) {
    }
    explicit StrongTypeWrapper() : m_value{} {
    }
    T get() const {
        return m_value;
    }
    explicit operator T() const {
        return m_value;
    }
    bool operator==(const StrongTypeWrapper& other) const {
        return this->m_value == other.m_value;
    }
    bool operator!=(const StrongTypeWrapper& other) const {
        return this->m_value != other.m_value;
    }

private:
    T m_value;
};

}  // namespace utils
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_UTILS_STRONGTYPEWRAPPER_H_
