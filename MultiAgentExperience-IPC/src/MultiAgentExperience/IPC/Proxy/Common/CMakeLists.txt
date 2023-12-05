target_sources(
        MultiAgentExperience-IPC
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/OnCompletionCallbackProxy.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/OnCompletionCallbackMessageHandler.cpp
)