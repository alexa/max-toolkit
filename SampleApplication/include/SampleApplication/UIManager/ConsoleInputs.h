/*
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */


#ifndef SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UIMANAGER_CONSOLEINPUTS_H_
#define SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UIMANAGER_CONSOLEINPUTS_H_

namespace multiAgentExperience {
namespace sampleApplication {
namespace uiManager {
namespace consoleInputs {
/// Used to express the first valid character to invoke tap-to-talk.
static const char TAP_STARTING_CHAR = '1';

/// Used to express the last valid character to invoke tap-to-talk.
static const char TAP_ENDING_CHAR = '9';

/// The character to exit the application.
static const char QUIT = 'q';

/// The character to invoke the help screen.
static const char HELP = 'h';

/// The character to toggle microphone mute.
static const char MIC_TOGGLE = 'm';

/// The character to issue a stop UDC.
static const char UDC_STOP = 's';
}  // namespace consoleInputs
}  // namespace uiManager
}  // namespace sampleApplication
}  // namespace multiAgentExperience

#endif  // SAMPLEAPPLICATION_INCLUDE_SAMPLEAPPLICATION_UIMANAGER_CONSOLEINPUTS_H_
