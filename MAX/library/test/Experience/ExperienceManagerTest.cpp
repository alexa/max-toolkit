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

#include <gtest/gtest.h>

#include "Experience/ExperienceManager.h"

#include "Mocks/MockExperienceObserver.h"

namespace multiAgentExperience {
namespace experience {
namespace test {

using namespace multiAgentExperience::experience;
using namespace multiAgentExperience::library::experience;

using namespace testing;

static const multiAgentExperience::actor::ActorId TEST_ACTOR_A("Alice");
static const multiAgentExperience::actor::ActorId TEST_ACTOR_B("Bob");
static const unsigned int TEST_SESSION{20};

class ExperienceManagerTest : public ::testing::Test {
public:
    virtual void SetUp() override {
        auto unthreadedExecutor = std::make_shared<library::utils::threading::Executor>(false);
        m_manager = std::make_shared<ExperienceManager>(unthreadedExecutor);
    }

    virtual void TearDown() override {
        m_manager.reset();
    }

protected:
    std::shared_ptr<ExperienceManager> m_manager;
};

TEST_F(ExperienceManagerTest, test_multiple_observers_simple) {
    auto observer1 = std::make_shared<testing::NiceMock<MockExperienceObserver>>();
    auto observer2 = std::make_shared<testing::NiceMock<MockExperienceObserver>>();
    EXPECT_CALL(*observer1, onExperienceChange(_)).Times(3);
    EXPECT_CALL(*observer2, onExperienceChange(_)).Times(2);

    m_manager->addObserver(observer1);
    m_manager->addObserver(observer2);
    m_manager->startExperience(TEST_ACTOR_A, TEST_SESSION, ExperienceId("1"));

    observer2.reset();
    m_manager->startExperience(TEST_ACTOR_A, TEST_SESSION, ExperienceId("2"));
}
TEST_F(ExperienceManagerTest, test_multiple_observers_complex) {
    auto observer1 = std::make_shared<testing::NiceMock<MockExperienceObserver>>();
    auto observer2 = std::make_shared<testing::NiceMock<MockExperienceObserver>>();
    auto observer3 = std::make_shared<testing::NiceMock<MockExperienceObserver>>();

    EXPECT_CALL(*observer1, onExperienceChange(_)).Times(4);
    EXPECT_CALL(*observer2, onExperienceChange(_)).Times(2);
    EXPECT_CALL(*observer3, onExperienceChange(_)).Times(3);

    m_manager->addObserver(observer1);
    m_manager->addObserver(observer2);
    m_manager->addObserver(observer3);

    m_manager->startExperience(TEST_ACTOR_A, TEST_SESSION, ExperienceId("3"));

    observer2.reset();
    m_manager->startExperience(TEST_ACTOR_A, TEST_SESSION, ExperienceId("4"));

    observer3.reset();
    m_manager->startExperience(TEST_ACTOR_A, TEST_SESSION, ExperienceId("5"));
}

TEST_F(ExperienceManagerTest, test_single_experience) {
    std::vector<Experience> experiences;
    auto observer = std::make_shared<testing::NiceMock<MockExperienceObserver>>();
    EXPECT_CALL(*observer, onExperienceChange(_)).WillRepeatedly(SaveArg<0>(&experiences));
    m_manager->addObserver(observer);
    m_manager->startExperience(TEST_ACTOR_A, TEST_SESSION, commonIds::LISTENING);
    EXPECT_EQ(experiences.size(), (size_t)1);
    EXPECT_TRUE(experiences[0].actorId == TEST_ACTOR_A);
    EXPECT_TRUE(experiences[0].sessionId == TEST_SESSION);
    EXPECT_TRUE(experiences[0].experienceId == commonIds::LISTENING);
}

TEST_F(ExperienceManagerTest, test_multiple_experience) {
    std::vector<Experience> experiences;
    auto observer = std::make_shared<testing::NiceMock<MockExperienceObserver>>();
    EXPECT_CALL(*observer, onExperienceChange(_)).Times(3).WillRepeatedly(SaveArg<0>(&experiences));
    m_manager->addObserver(observer);
    EXPECT_EQ(experiences.size(), (size_t)0);
    m_manager->startExperience(TEST_ACTOR_A, TEST_SESSION, ExperienceId("1"));
    m_manager->startExperience(TEST_ACTOR_A, TEST_SESSION + 1, ExperienceId("2"));
    EXPECT_EQ(experiences.size(), (size_t)2);
    EXPECT_TRUE(experiences[0].actorId == TEST_ACTOR_A);
    EXPECT_EQ(experiences[0].sessionId, TEST_SESSION + 1);
    EXPECT_TRUE(experiences[0].experienceId == ExperienceId("2"));
    EXPECT_TRUE(experiences[1].actorId == TEST_ACTOR_A);
    EXPECT_EQ(experiences[1].sessionId, TEST_SESSION);
    EXPECT_TRUE(experiences[1].experienceId == ExperienceId("1"));
}

TEST_F(ExperienceManagerTest, test_end_experience) {
    std::vector<Experience> experiences;
    auto observer = std::make_shared<testing::NiceMock<MockExperienceObserver>>();
    EXPECT_CALL(*observer, onExperienceChange(_)).Times(5).WillRepeatedly(SaveArg<0>(&experiences));
    m_manager->addObserver(observer);
    m_manager->startExperience(TEST_ACTOR_A, TEST_SESSION, ExperienceId("1"));
    m_manager->startExperience(TEST_ACTOR_A, TEST_SESSION + 1, ExperienceId("2"));
    m_manager->endExperience(TEST_ACTOR_A, TEST_SESSION + 1);
    EXPECT_EQ(experiences.size(), (size_t)1);
    EXPECT_TRUE(experiences[0].actorId == TEST_ACTOR_A);
    EXPECT_TRUE(experiences[0].sessionId == TEST_SESSION);
    EXPECT_TRUE(experiences[0].experienceId == ExperienceId("1"));
    m_manager->endExperience(TEST_ACTOR_A, TEST_SESSION);
    EXPECT_EQ(experiences.size(), (size_t)0);
}

TEST_F(ExperienceManagerTest, test_experience_session) {
    std::vector<Experience> experiences;
    auto observer = std::make_shared<testing::NiceMock<MockExperienceObserver>>();
    EXPECT_CALL(*observer, onExperienceChange(_)).Times(8).WillRepeatedly(SaveArg<0>(&experiences));
    m_manager->addObserver(observer);
    auto controla = m_manager->getController(TEST_ACTOR_A);
    auto controlb = m_manager->getController(TEST_ACTOR_B);
    auto controlc = m_manager->getController(TEST_ACTOR_A);
    controla->startExperience(ExperienceId("1"));
    ASSERT_EQ(experiences.size(), (size_t)1);

    auto session1 = experiences[0].sessionId;
    controlb->startExperience(ExperienceId("2"));
    controlc->startExperience(ExperienceId("3"));
    ASSERT_EQ(experiences.size(), (size_t)3);
    EXPECT_NE(experiences[0].sessionId, experiences[1].sessionId);
    EXPECT_NE(experiences[1].sessionId, experiences[2].sessionId);
    EXPECT_NE(experiences[2].sessionId, experiences[0].sessionId);

    controlb->endExperience();
    ASSERT_EQ(experiences.size(), (size_t)2);

    controlc->endExperience();
    ASSERT_EQ(experiences.size(), (size_t)1);

    controla->startExperience(ExperienceId("4"));
    ASSERT_EQ(experiences.size(), (size_t)1);

    auto session4 = experiences[0].sessionId;
    EXPECT_EQ(session1, session4);

    controla->endExperience();
    ASSERT_EQ(experiences.size(), (size_t)0);
    // verify before controls are cleaned up through destructors
    testing::Mock::VerifyAndClearExpectations(observer.get());
}

TEST_F(ExperienceManagerTest, test_experience_control) {
    std::vector<Experience> experiences;
    auto control = m_manager->getController(TEST_ACTOR_A);
    auto observer = std::make_shared<testing::NiceMock<MockExperienceObserver>>();
    EXPECT_CALL(*observer, onExperienceChange(_)).Times(2).WillRepeatedly(SaveArg<0>(&experiences));
    m_manager->addObserver(observer);
    control->startExperience(ExperienceId("1"));
    EXPECT_EQ(experiences.size(), (size_t)1);
    EXPECT_TRUE(experiences[0].actorId == TEST_ACTOR_A);
    EXPECT_TRUE(experiences[0].experienceId == ExperienceId("1"));
    // verify before controls are cleaned up through destructors
    testing::Mock::VerifyAndClearExpectations(observer.get());
}

TEST_F(ExperienceManagerTest, test_experience_control_end) {
    std::vector<Experience> experiences;
    auto control = m_manager->getController(TEST_ACTOR_A);
    auto control2 = m_manager->getController(TEST_ACTOR_A);
    auto observer = std::make_shared<testing::NiceMock<MockExperienceObserver>>();
    EXPECT_CALL(*observer, onExperienceChange(_)).Times(5).WillRepeatedly(SaveArg<0>(&experiences));
    m_manager->addObserver(observer);
    control->startExperience(ExperienceId("1"));
    control2->startExperience(ExperienceId("2"));
    EXPECT_EQ(experiences.size(), (size_t)2);
    auto session1 = experiences[0].sessionId;
    auto session2 = experiences[1].sessionId;
    EXPECT_NE(session1, session2);
    control2->endExperience();
    EXPECT_EQ(experiences.size(), (size_t)1);
    EXPECT_TRUE(experiences[0].actorId == TEST_ACTOR_A);
    EXPECT_TRUE(experiences[0].experienceId == ExperienceId("1"));
    control->endExperience();
    EXPECT_EQ(experiences.size(), (size_t)0);

    // verify before controls are cleaned up through destructors
    testing::Mock::VerifyAndClearExpectations(observer.get());
}

TEST_F(ExperienceManagerTest, test_manager_destruction) {
    auto control = m_manager->getController(TEST_ACTOR_A);
    auto observer = std::make_shared<testing::NiceMock<MockExperienceObserver>>();
    EXPECT_CALL(*observer, onExperienceChange(_)).Times(1);
    m_manager->addObserver(observer);

    m_manager.reset();
    control->startExperience(ExperienceId("1"));
}

TEST_F(ExperienceManagerTest, test_observer_destruction) {
    auto control = m_manager->getController(TEST_ACTOR_A);
    auto observer = std::make_shared<testing::NiceMock<MockExperienceObserver>>();
    m_manager->addObserver(observer);
    observer.reset();
    control->startExperience(ExperienceId("1"));
}

TEST_F(ExperienceManagerTest, test_adding_an_observer_notifies_only_the_new_observer) {
    auto observerOne = std::make_shared<testing::StrictMock<MockExperienceObserver>>();
    auto observerTwo = std::make_shared<testing::StrictMock<MockExperienceObserver>>();
    auto control = m_manager->getController(TEST_ACTOR_A);
    control->startExperience(ExperienceId("1"));
    EXPECT_CALL(*observerOne, onExperienceChange(_)).Times(1);
    m_manager->addObserver(observerOne);
    EXPECT_CALL(*observerTwo, onExperienceChange(_)).Times(1);
    m_manager->addObserver(observerTwo);

    m_manager->clearObservers();
}

}  // namespace test
}  // namespace experience
}  // namespace multiAgentExperience
