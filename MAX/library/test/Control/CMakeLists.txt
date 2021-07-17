add_googletest(ControlTest
    "${PRIVATE_INCLUDES}"
    "MultiAgentExperience"
    ${CMAKE_CURRENT_SOURCE_DIR}/ControlAccessKeysTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ControlInvokerTest.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/ControlStoreTest.cpp
)
