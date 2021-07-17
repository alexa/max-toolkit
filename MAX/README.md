# MAX Library

Here you will find both the API surface, and implementation, of the MAX Library. The API surface should be your starting
point as a consumer of the MAX Library. You should also explore the provided documentation towards integrating either a
[device](../Documentation/Integrating_A_Device_With_MAX_Library.md) or an [agent](../Documentation/Integrating_An_Agent_With_MAX_Library.md) with the MAX Library.

The MAX Library is the core of the MAX Toolkit, and should not require change when developing either a new agent or device.

## Build Instructions
Out of source builds are recommended:

    mkdir $PATH_TO_MAX_BUILD
    cd $PATH_TO_MAX_BUILD
    cmake $PATH_TO_MAX_SOURCE

    make


Optionally, you may install the MAX Library to your system's default install location,
or to a location you specify (see `DCMAKE_INSTALL_PREFIX` below):

    make install


### CMake Options
#### Optional

    -DCMAKE_INSTALL_PREFIX=/path/to/install/prefix

The default install prefix is `/usr/local` on Unix-like systems. Feel free to leave as default, or point to a user directory such as `~/max`.
