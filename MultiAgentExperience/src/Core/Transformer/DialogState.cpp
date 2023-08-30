/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#include "Core/Transformer/DialogState.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {

static const std::string NONE_STATE_NAME = "none";
static const std::string LISTENING_STATE_NAME = "listening";
static const std::string THINKING_STATE_NAME = "thinking";
static const std::string SPEAKING_STATE_NAME = "speaking";

DialogState DialogState::createNoneState() {
    return create(NONE_STATE_NAME);
}

DialogState DialogState::createListening() {
    return create(LISTENING_STATE_NAME);
}

DialogState DialogState::createThinking() {
    return create(THINKING_STATE_NAME);
}

DialogState DialogState::createSpeaking() {
    return create(SPEAKING_STATE_NAME);
}

DialogState DialogState::create(const std::string& stateName) {
    DialogState dialogState(stateName);
    return dialogState;
}

DialogState::DialogState(const DialogState& dialogState) : m_stateName{dialogState.m_stateName} {
}

DialogState DialogState::operator=(const DialogState& otherState) {
    m_stateName = otherState.m_stateName;
    return *this;
}

DialogState::DialogState(const std::string& stateName) : m_stateName{stateName} {
}

std::string DialogState::getStateName() const {
    return m_stateName;
}

bool DialogState::operator==(const DialogState& otherState) const {
    return m_stateName == otherState.m_stateName;
}

bool DialogState::operator!=(const DialogState& otherState) const {
    return m_stateName != otherState.m_stateName;
}

bool DialogState::isNone() const {
    return m_stateName == NONE_STATE_NAME;
}

bool DialogState::isListening() const {
    return m_stateName == LISTENING_STATE_NAME;
}

bool DialogState::isThinking() const {
    return m_stateName == THINKING_STATE_NAME;
}

bool DialogState::isSpeaking() const {
    return m_stateName == SPEAKING_STATE_NAME;
}

}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
