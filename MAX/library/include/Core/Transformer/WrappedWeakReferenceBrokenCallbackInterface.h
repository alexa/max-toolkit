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


#ifndef MULTI_AGENT_EXPERIENCE_INCLUDE_CONTROL_WRAPPEDWEAKREFERENCEBROKENCALLBACKINTERFACE_H_
#define MULTI_AGENT_EXPERIENCE_INCLUDE_CONTROL_WRAPPEDWEAKREFERENCEBROKENCALLBACKINTERFACE_H_

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

template <typename T>
class WrappedWeakReferenceBrokenCallbackInterface {
public:
    virtual ~WrappedWeakReferenceBrokenCallbackInterface() = default;

    virtual void onBroken(std::shared_ptr<T> wrappingReference) = 0;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_INCLUDE_CONTROL_WRAPPEDWEAKREFERENCEBROKENCALLBACKINTERFACE_H_
