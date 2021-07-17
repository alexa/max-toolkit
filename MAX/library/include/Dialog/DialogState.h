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

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGSTATE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGSTATE_H_

#include <string>

namespace multiAgentExperience {
namespace library {
namespace dialog {

using DialogState = std::string;

class DialogStateFactory {
public:
    static DialogState create(std::string value) {
        return DialogState(value);
    }

    static const DialogState none() {
        return DialogStateFactory::create("none");
    }

    static const DialogState listening() {
        return DialogStateFactory::create("listening");
    }

    static const DialogState thinking() {
        return DialogStateFactory::create("thinking");
    }

    static const DialogState speaking() {
        return DialogStateFactory::create("speaking");
    }

    static const bool isInterruptible(const DialogState& dialogState) {
        return dialogState != listening() && dialogState != thinking() && dialogState != none();
    }
};

}  // namespace dialog
}  // namespace library
}  // namespace multiAgentExperience

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_DIALOG_DIALOGSTATE_H_
