target_sources(
        MultiAgentExperience-IPC
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/ControlRegistryProxy.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ControlRegistryMessageHandler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ControlMessageHandler.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ControlProxy.cpp
)