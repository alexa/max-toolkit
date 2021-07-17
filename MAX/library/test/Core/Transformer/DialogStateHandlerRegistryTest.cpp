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

#include "Core/Transformer/DialogStateHandlerRegistry.h"

#include <gmock/gmock.h>
#include <memory>

#include "Mocks/MockListeningHandlerInterface.h"
#include "Mocks/MockThinkingHandlerInterface.h"
#include "Mocks/MockSpeakingHandlerInterface.h"

namespace multiAgentExperience {
namespace library {
namespace core {
namespace transformer {
namespace test {

using namespace multiAgentExperience::dialog::test;
using testing::_;

class DialogStateHandlerRegistryTest : public ::testing::Test {
protected:
    std::shared_ptr<DialogStateHandlerRegistry> m_registry;

    virtual void SetUp() override {
        m_registry = std::make_shared<DialogStateHandlerRegistry>();
    }
};

TEST_F(DialogStateHandlerRegistryTest, test_get_listening_handler_returns_nullptr_initially) {
    ASSERT_EQ(m_registry->getListeningHandler(), nullptr);
}

TEST_F(DialogStateHandlerRegistryTest, test_get_thinking_handler_returns_nullptr_initially) {
    ASSERT_EQ(m_registry->getThinkingHandler(), nullptr);
}

TEST_F(DialogStateHandlerRegistryTest, test_get_speaking_handler_returns_nullptr_initially) {
    ASSERT_EQ(m_registry->getSpeakingHandler(), nullptr);
}

TEST_F(DialogStateHandlerRegistryTest, test_get_listening_handler_returns_registered_handler) {
    auto mockListeningHandler = std::make_shared<testing::StrictMock<MockListeningHandlerInterface>>();
    m_registry->setListeningHandler(mockListeningHandler);
    ASSERT_EQ(m_registry->getListeningHandler(), mockListeningHandler);
}

TEST_F(DialogStateHandlerRegistryTest, test_get_thinking_handler_returns_registered_handler) {
    auto mockThinkingHandler = std::make_shared<testing::StrictMock<MockThinkingHandlerInterface>>();
    m_registry->setThinkingHandler(mockThinkingHandler);
    ASSERT_EQ(m_registry->getThinkingHandler(), mockThinkingHandler);
}

TEST_F(DialogStateHandlerRegistryTest, test_get_speaking_handler_returns_registered_handler) {
    auto mockSpeakingHandler = std::make_shared<testing::StrictMock<MockSpeakingHandlerInterface>>();
    m_registry->setSpeakingHandler(mockSpeakingHandler);
    ASSERT_EQ(m_registry->getSpeakingHandler(), mockSpeakingHandler);
}

TEST_F(DialogStateHandlerRegistryTest, test_get_listening_handler_returns_nullptr_after_removing_registered_handler) {
    auto mockListeningHandler = std::make_shared<testing::StrictMock<MockListeningHandlerInterface>>();
    m_registry->setListeningHandler(mockListeningHandler);
    m_registry->removeListeningHandler();
    ASSERT_EQ(m_registry->getListeningHandler(), nullptr);
}

TEST_F(DialogStateHandlerRegistryTest, test_get_thinking_handler_returns_nullptr_after_removing_registered_handler) {
    auto mockThinkingHandler = std::make_shared<testing::StrictMock<MockThinkingHandlerInterface>>();
    m_registry->setThinkingHandler(mockThinkingHandler);
    m_registry->removeThinkingHandler();
    ASSERT_EQ(m_registry->getThinkingHandler(), nullptr);
}

TEST_F(DialogStateHandlerRegistryTest, test_get_speaking_handler_returns_nullptr_after_removing_registered_handler) {
    auto mockSpeakingHandler = std::make_shared<testing::StrictMock<MockSpeakingHandlerInterface>>();
    m_registry->setSpeakingHandler(mockSpeakingHandler);
    m_registry->removeSpeakingHandler();
    ASSERT_EQ(m_registry->getSpeakingHandler(), nullptr);
}

TEST_F(DialogStateHandlerRegistryTest, test_remove_listening_handler_only_removes_listening_handler) {
    auto mockListeningHandler = std::make_shared<testing::StrictMock<MockListeningHandlerInterface>>();
    m_registry->setListeningHandler(mockListeningHandler);
    auto mockThinkingHandler = std::make_shared<testing::StrictMock<MockThinkingHandlerInterface>>();
    m_registry->setThinkingHandler(mockThinkingHandler);
    auto mockSpeakingHandler = std::make_shared<testing::StrictMock<MockSpeakingHandlerInterface>>();
    m_registry->setSpeakingHandler(mockSpeakingHandler);

    m_registry->removeListeningHandler();

    ASSERT_EQ(m_registry->getListeningHandler(), nullptr);
    ASSERT_EQ(m_registry->getThinkingHandler(), mockThinkingHandler);
    ASSERT_EQ(m_registry->getSpeakingHandler(), mockSpeakingHandler);
}

TEST_F(DialogStateHandlerRegistryTest, test_remove_thinking_handler_only_removes_thinking_handler) {
    auto mockListeningHandler = std::make_shared<testing::StrictMock<MockListeningHandlerInterface>>();
    m_registry->setListeningHandler(mockListeningHandler);
    auto mockThinkingHandler = std::make_shared<testing::StrictMock<MockThinkingHandlerInterface>>();
    m_registry->setThinkingHandler(mockThinkingHandler);
    auto mockSpeakingHandler = std::make_shared<testing::StrictMock<MockSpeakingHandlerInterface>>();
    m_registry->setSpeakingHandler(mockSpeakingHandler);

    m_registry->removeThinkingHandler();

    ASSERT_EQ(m_registry->getListeningHandler(), mockListeningHandler);
    ASSERT_EQ(m_registry->getThinkingHandler(), nullptr);
    ASSERT_EQ(m_registry->getSpeakingHandler(), mockSpeakingHandler);
}

TEST_F(DialogStateHandlerRegistryTest, test_remove_speaking_handler_only_removes_speaking_handler) {
    auto mockListeningHandler = std::make_shared<testing::StrictMock<MockListeningHandlerInterface>>();
    m_registry->setListeningHandler(mockListeningHandler);
    auto mockThinkingHandler = std::make_shared<testing::StrictMock<MockThinkingHandlerInterface>>();
    m_registry->setThinkingHandler(mockThinkingHandler);
    auto mockSpeakingHandler = std::make_shared<testing::StrictMock<MockSpeakingHandlerInterface>>();
    m_registry->setSpeakingHandler(mockSpeakingHandler);

    m_registry->removeSpeakingHandler();

    ASSERT_EQ(m_registry->getListeningHandler(), mockListeningHandler);
    ASSERT_EQ(m_registry->getThinkingHandler(), mockThinkingHandler);
    ASSERT_EQ(m_registry->getSpeakingHandler(), nullptr);
}

}  // namespace test
}  // namespace transformer
}  // namespace core
}  // namespace library
}  // namespace multiAgentExperience
