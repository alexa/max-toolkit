/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
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
