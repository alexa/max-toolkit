/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGSTATE_H_
#define MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGSTATE_H_

#include <string>

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

class DialogState {
public:
    static DialogState createNoneState();
    static DialogState createListening();
    static DialogState createThinking();
    static DialogState createSpeaking();
    static DialogState create(const std::string& stateName);

    DialogState(const DialogState& dialogState);

    DialogState operator=(const DialogState& otherState);

    std::string getStateName() const;

    bool operator==(const DialogState& otherState) const;

    bool operator!=(const DialogState& otherState) const;

    bool isNone() const;

    bool isListening() const;

    bool isThinking() const;

    bool isSpeaking() const;

private:
    DialogState(const std::string& stateName);

    std::string m_stateName;
};

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience

template <>
struct std::hash<multiAgentExperience::library::core::transformer::DialogState> {
    std::size_t operator()(multiAgentExperience::library::core::transformer::DialogState const& dialogState) const
        noexcept {
        return std::hash<std::string>()(dialogState.getStateName());
    }
};

#endif  // MULTI_AGENT_EXPERIENCE_LIBRARY_INCLUDE_CORE_TRANSFORMER_DIALOGSTATE_H_
