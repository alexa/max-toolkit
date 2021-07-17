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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_WAKEWORDMETADATACACHE_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_WAKEWORDMETADATACACHE_H_

#include <AVSCommon/SDKInterfaces/KeyWordMetadataAccessorInterface.h>

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {
namespace wakeword {

/**
 * Implements a trivial way to store and retrieve KWD metadata. May be subject to race conditions on extreme edge
 * cases where multiple wakeword engines detect the same word, and both generate metadata, and only of impact should
 * the metadata be of significant difference.
 *
 * To be replaced by a more generalized audio data management system in later MAX Toolkit releases.
 */
class WakewordMetadataCache : public alexaClientSDK::avsCommon::sdkInterfaces::KeyWordMetadataAccessorInterface {
public:
    /**
     * Set the current kwd metadata.
     *
     * @param data The kwd metadata to be set.
     */
    void setMetadata(const alexaClientSDK::avsCommon::sdkInterfaces::KeyWordMetadataAccessorInterface::Metadata& data);

    /// @name KeyWordMetadataAccessorInterface method overrides.
    /// @{
    Metadata getKeywordMetadata() override;
    /// @}
private:
    /// The current kwd metadata.
    alexaClientSDK::avsCommon::sdkInterfaces::KeyWordMetadataAccessorInterface::Metadata m_currentMetadata;
};

}  // namespace wakeword
}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_WAKEWORDMETADATACACHE_H_
