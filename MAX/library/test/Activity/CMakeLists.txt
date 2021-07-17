add_googletest(ActivityTest
    "${PRIVATE_INCLUDES}"
    "MultiAgentExperience"
    ${CMAKE_CURRENT_SOURCE_DIR}/ActivityLifecycleTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ActivityManagerIntegrationTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ActivityRequestLifecycleTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ChannelToActivityObserverTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FocusManagerActivityChannelsTest.cpp
)

