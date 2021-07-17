# Common build settings across all MAX Toolkit modules.

# Append custom CMake modules.
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# Convenience function to get similar behaviour as CMAKE_DEPENDENT_OPTION
# for non boolean variables.
# Will mark "target" as advanced (hidden by default in most tools) unless
# "dependency" is defined and not equal to "".
function(mark_as_dependent target dependency)
    if (${dependency})
        mark_as_advanced(CLEAR ${target})
    elseif (NOT ${dependency})
        mark_as_advanced(FORCE ${target})
    endif()
endfunction(mark_as_dependent)

macro(include_once module)
    if(NOT DEFINED "BuildDefaults_Include_${module}_Set")
        set("BuildDefaults_Include_${module}_Set" ON)
        include("${module}")
    endif()
endmacro()

# Disallow out-of-source-builds.
include_once(DisallowOutOfSourceBuilds)

# Setup default build options, like compiler flags and build type.
include_once(BuildOptions)

# Setup package requirement variables.
include_once(PackageConfigs)

# Setup media player variables.
include_once(MediaPlayer)

# Setup PortAudio variables.
include_once(PortAudio)

# Setup platform dependant variables.
include_once(Platforms)

# Setup GLib
include_once(GLib)