# Alexa AVS Device SDK Patch

This patch can be applied (using `git apply`) the the AVS Device SDK v1.23.0 to enable MAX compatability.

You can checkout the proper version of the AVS Device SDK with:

```
git clone --single-branch https://github.com/alexa/avs-device-sdk.git -b v1.23.0
```

and then apply this patch:

```
cd avs-device-sdk
git apply $PATH_TO_MAX_TOOLKIT_SOURCE/Agents/Alexa/avs-device-sdk-v1-23-0-max-compatability-patch.patch
```
