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

#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_WAKEWORDENGINEINTERFACE_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_WAKEWORDENGINEINTERFACE_H_

#include <memory>
#include <ostream>
#include <string>
#include <set>

#include <MultiAgentExperience/Utils/Data/DataObserverInterface.h>
#include <MultiAgentExperience/Application/WakeWordObserverInterface.h>

#include "SampleApplication/AgentManager/GestureHandlerInterface.h"
#include "SampleApplication/AudioManager/Wakeword/CrosswakeDetector/SimpleCrosswakeDetector.h"

namespace multiAgentExperience {
namespace sampleApplication {
namespace audioManager {
namespace wakeword {

namespace MAX = multiAgentExperience;

/**
 * The Wakeword Engine interface to be used by MAX Application engines.
 */
class WakewordEngine : public MAX::utils::data::DataObserverInterface {
public:
    /// Methods by which a @c WakewordEngine may be created.
    enum class CreateMethod {
        /// Create via an AVS SDK Library.
        AVS_SDK,
        /// Create by some other method as defined within this application.
        CUSTOM
    };

    /**
     * Constructor.
     *
     * @param crosswakeDetector The detector to prevent cross wakes.
     * @param observer The MAX Observer to be notified when a wakeword is detected.
     */
    WakewordEngine(
        std::shared_ptr<crosswake::SimpleCrosswakeDetector> crosswakeDetector,
        std::shared_ptr<MAX::application::WakeWordObserverInterface> observer);

    /**
     * Destructor.
     */
    virtual ~WakewordEngine() = default;

    /**
     * Return the name of the wakeword engine.
     *
     * @return The name of the wakeword engine.
     */
    virtual std::string getName() = 0;

    /**
     * Return the create method of the wakeword engine.
     *
     * @return The create method of the wakeword engine.
     */
    virtual CreateMethod getCreateMethod() = 0;

    /**
     * Return the set of wakewords this engine may detect.
     *
     * @return The set of wakewords this engine may detect.
     */
    virtual std::set<std::string> getWakewords() = 0;

    /**
     * Sets the gesture handler to be used.
     *
     * @param gestureHandler The gesture handler to be used.
     */
    virtual void setGestureHandler(std::shared_ptr<agentManager::GestureHandlerInterface> gestureHandler);

protected:
    /// Our MAX wakeword observer.
    std::shared_ptr<crosswake::SimpleCrosswakeDetector> m_crosswakeDetector;
    std::shared_ptr<MAX::application::WakeWordObserverInterface> m_observer;
};

/**
 * Write a @c createMethod value to an @c ostream as a string.
 *
 * @param stream The stream to write the value to.
 * @param state The createMethod value to write to the @c ostream as a string.
 * @return The @c ostream that was passed in and written to.
 */
inline std::ostream& operator<<(std::ostream& stream, const WakewordEngine::CreateMethod createMethod) {
    switch (createMethod) {
        case WakewordEngine::CreateMethod::AVS_SDK:
            return stream << "AVS_SDK";
        case WakewordEngine::CreateMethod::CUSTOM:
            return stream << "CUSTOM";
    }

    return stream << "Unknown WakewordEngine::CreateMethod.";
}

}  // namespace wakeword
}  // namespace audioManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_AUDIOMANAGER_WAKEWORD_WAKEWORDENGINEINTERFACE_H_
