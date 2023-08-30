/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_API_STARTLISTENINGCALLBACK_H
#define MULTIAGENTEXPERIENCE_API_STARTLISTENINGCALLBACK_H

#include<future>

namespace multiAgentExperience {
namespace dialog {

/**
 * A StartListeningCallback handles the callback to start listening.
 */
class StartListeningCallback{
public:
    /**
     * Constructor.
     */
    explicit StartListeningCallback(std::promise<void> continueListening) :
        m_continueListening(std::move(continueListening)) {
    }

    /**
     * Called when LISTENING state needs to continue after processing ControlTypes.
     */
    void startListening() {
        m_continueListening.set_value();
    }
private:
    std::promise<void> m_continueListening;
};

}  // namespace dialog
}  // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_API_STARTLISTENINGCALLBACK_H
