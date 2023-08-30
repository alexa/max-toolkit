/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Core/Transformer/DialogControllerTransformerFactory.h"

#include "Core/Transformer/DialogControllerTransformer.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

DialogControllerTransformerFactory::DialogControllerTransformerFactory(
    std::shared_ptr<multiAgentExperience::library::control::ControlInvokerFactory> controlInvokerFactory) :
        m_controlInvokerFactory{controlInvokerFactory} {
}

std::shared_ptr<DialogControllerTransformer> DialogControllerTransformerFactory::create(
    std::shared_ptr<multiAgentExperience::library::dialog::DialogController> dialogController) {
    return std::make_shared<DialogControllerTransformer>(m_controlInvokerFactory, dialogController);
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
