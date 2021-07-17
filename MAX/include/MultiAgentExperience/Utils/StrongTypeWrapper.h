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
