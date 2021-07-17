# Computer Agent Library

This is a sample MAX-compatible Agent, powered by AWS Lex and capable of simple interactions. 
It is intended to be used by the MAX Sample Application alongside Alexa to demonstrate a multi-agent integration, 
and the interaction patterns between these two agents. The Computer Agent is provided to you for **demonstration purposes only**, and is not expected to be used in a commercial product or device.

For more details on interacting with the Computer Agent, please see the Appendix of
[MAX_Sample_Application_Getting_Started_Guide.md](../../Documentation/MAX_Sample_Application_Getting_Started_Guide.md#Appendix). 

## Prerequisites
### AWS SDK
The AWS SDK needs to be installed on the host machine to build the Computer Agent library.
You'll only need to install the AWS SDK components for Lex, Cognito, Polly and Text-to-Speech.

    cd $AWS_CHECKOUT_DIRECTORY
    git clone https://github.com/aws/aws-sdk-cpp.git
    mkdir $AWS_BUILD_DIRECTORY
    cd $AWS_BUILD_DIRECTORY
    cmake $AWS_CHECKOUT_DIRECTORY/aws-sdk-cpp -D BUILD_ONLY="lex;cognito-identity;sts;identity-management"
    make -j $(nproc)
    sudo make install

## Build Instructions
Out of source builds are recommended:

    mkdir $PATH_TO_COMPUTER_AGENT_BUILD
    cd $PATH_TO_COMPUTER_AGENT_BUILD
    cmake $PATH_TO_COMPUTER_AGENT_SOURCE \
        -DMultiAgentExperienceDir=$PATH_TO_MAX_BUILD
    make

Optionally, you may install the Computer Agent library to your system's default install location,
or to a location you specify (see `DCMAKE_INSTALL_PREFIX` below):

    make install

### CMake Options
#### required

    -DMultiAgentExperienceDir=$PATH_TO_MAX_BUILD

Required iff you did not install the MAX Library to a location where CMake can automatically find it.

    -DCMAKE_PREFIX_PATH=$CUSTOM_INSTALL_PATH

Alternatively, you may set the `CMAKE_PREFIX_PATH` to `~/max`, or wherever you have installed the MAX Library.

#### optional

    -DCMAKE_INSTALL_PREFIX=/path/to/install/prefix

By default `CMAKE_INSTALL_PREFX` is `/usr/local` on Unix-like systems.
Feel free to use the default, or point to a user directory such as ~/max.
