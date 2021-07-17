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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_ALEXA_NOOPCBLAUTHREQUESTER_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_ALEXA_NOOPCBLAUTHREQUESTER_H_

#include <CBLAuthDelegate/CBLAuthRequesterInterface.h>

namespace multiAgentExperience {
namespace sampleApplication {
namespace agentManager {
namespace alexa {

/**
 * This class is an empty implementation of the AVS SDK CBL Auth handler. This facilitates trivial instantiation
 * of the AVS SDK DefaultClient under the assumption that the CBL flow has already been handled.
 */
class NoopCBLAuthRequester : public alexaClientSDK::authorization::cblAuthDelegate::CBLAuthRequesterInterface {
public:
    /// @name CBLAuthRequesterInterface methods.
    /// @{
    void onRequestAuthorization(const std::string& url, const std::string& code) override {
    }
    void onCheckingForAuthorization() override {
    }
    /// @}
};

}  // namespace alexa
}  // namespace agentManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AGENTMANAGER_ALEXA_NOOPCBLAUTHREQUESTER_H_
