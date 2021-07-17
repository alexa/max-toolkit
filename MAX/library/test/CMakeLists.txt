set(PRIVATE_INCLUDES
    "${MultiAgentExperience_SOURCE_DIR}/library/include/"
    "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_subdirectory(Activity)
add_subdirectory(Agent)
add_subdirectory(Control)
add_subdirectory(Core)
add_subdirectory(Dialog)
add_subdirectory(Experience)
add_subdirectory(Integration)
