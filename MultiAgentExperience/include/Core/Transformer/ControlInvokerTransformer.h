/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/


#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_CONTROLINVOKERTRANSFORMER_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_CONTROLINVOKERTRANSFORMER_H_

#include "MultiAgentExperience/Control/ControlInvokerInterface.h"
#include "MultiAgentExperience/Actor/ActorId.h"

#include "Control/ControlInvoker.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class ControlInvokerTransformer : public multiAgentExperience::control::ControlInvokerInterface {
public:
    ControlInvokerTransformer(
        const multiAgentExperience::actor::ActorId id,
        std::shared_ptr<multiAgentExperience::library::control::ControlInvoker> invoker);

    void invokeControl(const multiAgentExperience::control::ControlType& controlType) override;

private:
    const multiAgentExperience::actor::ActorId m_id;
    std::shared_ptr<multiAgentExperience::library::control::ControlInvoker> m_invoker;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_CONTROLINVOKERTRANSFORMER_H_
