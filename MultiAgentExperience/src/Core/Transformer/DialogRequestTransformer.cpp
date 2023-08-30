/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Core/Transformer/DialogRequestTransformer.h"

#include "Core/Transformer/DialogLifecycleTransformer.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

DialogRequestTransformer::DialogRequestTransformer(
    std::shared_ptr<DialogLifecycleTransformer> dialogLifecycleTransformer,
    const multiAgentExperience::dialog::DialogBargeInPriority& dialogBargeInPriority) :
        library::dialog::DialogRequest(dialogLifecycleTransformer, dialogBargeInPriority),
        m_dialogLifecycleTransformer{dialogLifecycleTransformer} {
}

void DialogRequestTransformer::onGranted() {
    m_dialogLifecycleTransformer->onGranted();
}

void DialogRequestTransformer::onDenied() {
    m_dialogLifecycleTransformer->onDenied();
}

multiAgentExperience::actor::ActorId DialogRequestTransformer::getActorId() const {
    return m_dialogLifecycleTransformer->getActorId();
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
