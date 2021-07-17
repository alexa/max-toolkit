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

#include "Core/Transformer/DialogRequestTransformer.h"

#include "Core/Transformer/DialogLifecycleTransformer.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

DialogRequestTransformer::DialogRequestTransformer(
    std::shared_ptr<DialogLifecycleTransformer> dialogLifecycleTransformer) :
        library::dialog::DialogRequest(dialogLifecycleTransformer),
        m_dialogLifecycleTransformer{dialogLifecycleTransformer} {
}

void DialogRequestTransformer::onGranted() {
    m_dialogLifecycleTransformer->onGranted();
}

void DialogRequestTransformer::onDenied() {
    m_dialogLifecycleTransformer->onDenied();
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
