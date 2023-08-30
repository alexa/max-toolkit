/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include <MultiAgentExperience/Utils/Logger/Logger.h>

#include "Core/Transformer/ControlInvokerTransformer.h"

#include <sstream>

#include "Core/Transformer/TransformerUtils.h"

#include "Utils/ConversionUtils.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

static const std::string MODULE_TAG("ControlInvokerTransformer");
#define LX(logCommand, message) MAX_LIBRARY_LOG_##logCommand("", MODULE_TAG, __func__, message)

ControlInvokerTransformer::ControlInvokerTransformer(
    const multiAgentExperience::actor::ActorId id,
    std::shared_ptr<multiAgentExperience::library::control::ControlInvoker> invoker) :
        m_id{id},
        m_invoker{invoker} {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(id);
    LX(DEBUG0, ss.str());
}

void ControlInvokerTransformer::invokeControl(const multiAgentExperience::control::ControlType& controlType) {
    std::stringstream ss;
    ss << "details:"
       << " actorId=" << multiAgentExperience::library::utils::getObfuscatedActorId(m_id)
       << " controlType=" << multiAgentExperience::library::utils::toString(controlType);
    LX(DEBUG0, ss.str());

    auto controlName = TransformerUtils::convertControlTypeToControlName(controlType);
    m_invoker->invoke(controlName);
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience