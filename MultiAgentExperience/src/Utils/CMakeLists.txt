target_sources(
        MultiAgentExperience
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Executor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/TaskThread.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/ThreadPool.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/Timer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/WorkerThread.cpp)
