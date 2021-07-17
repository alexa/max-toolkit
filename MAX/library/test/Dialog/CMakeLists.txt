add_googletest(DialogTest
    "${PRIVATE_INCLUDES}"
    "MultiAgentExperience"
    ${CMAKE_CURRENT_SOURCE_DIR}/DialogArbitratorTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DialogLifecycleTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DialogManagerIntegrationTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/DialogRequestLifecycleTest.cpp
)
