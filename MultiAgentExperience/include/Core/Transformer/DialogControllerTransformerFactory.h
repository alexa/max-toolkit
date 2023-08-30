/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGCONTROLLERTRANSFORMERFACTORY_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGCONTROLLERTRANSFORMERFACTORY_H_

#include <memory>

#include "Control/ControlInvokerFactory.h"
#include "DialogControllerTransformer.h"
#include "Dialog/DialogController.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class DialogControllerTransformerFactory {
public:
    DialogControllerTransformerFactory(std::shared_ptr<library::control::ControlInvokerFactory> controlInvokerFactory);

    virtual ~DialogControllerTransformerFactory() = default;

    virtual std::shared_ptr<DialogControllerTransformer> create(
        std::shared_ptr<library::dialog::DialogController> dialogController);

private:
    std::shared_ptr<library::control::ControlInvokerFactory> m_controlInvokerFactory;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGCONTROLLERTRANSFORMERFACTORY_H_
