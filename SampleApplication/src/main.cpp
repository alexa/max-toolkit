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

#include "SampleApplication/Application.h"

#include <cstdlib>
#include <iostream>
#include <string>

/**
 * The starting point for the MAX Sample Application. @c main expects a config JSON file to be provided.
 *
 * @param argc The number of elements in the @c argv array.
 * @param argv An array of @argc elements, containing the program name and all command-line arguments.
 * @return @c EXIT_FAILURE if the application failed to initialize correctly, else @c EXIT_SUCCESS.
 */
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Incorrect parameters - exiting. Usage: " << std::string(argv[0]) << " <path_to_MAXConfig.json>"
                  << std::endl;
        return EXIT_FAILURE;
    }

    std::string maxConfigPath = std::string(argv[1]);

    auto application = multiAgentExperience::sampleApplication::Application::create(maxConfigPath);
    if (!application) {
        std::cout << "Unable to instantiate the MAX Sample Application from main(). Exiting." << std::endl;
        return EXIT_FAILURE;
    }

    application->run();

    return EXIT_SUCCESS;
}
