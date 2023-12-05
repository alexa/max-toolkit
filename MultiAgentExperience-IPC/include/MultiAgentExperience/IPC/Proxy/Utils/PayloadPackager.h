/*
 * Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * You may not use this file except in compliance with the terms and conditions
 * set forth in the accompanying LICENSE file.
 */

#ifndef MULTIAGENTEXPERIENCE_IPC_PROXY_UTILS_PACKAGER_H
#define MULTIAGENTEXPERIENCE_IPC_PROXY_UTILS_PACKAGER_H

#include <vector>

#include <MultiAgentExperience/IPC/Messaging/Reference.h>
#include <MultiAgentExperience/IPC/Messaging/ReferenceListPayload.h>
#include <MultiAgentExperience/IPC/Messaging/ReferencePayload.h>

namespace multiAgentExperience {
namespace ipc {
namespace proxy {
namespace utils {

/**
 * This class is responsible for packaging objects of non-primitive types (i.e. that require @c References) into
 * payloads that are accepted by the @c TransportSenderInterface::send methods.
 */
class PayloadPackager {
public:

    /**
     * Creates a ReferencePayload object of type T, from the shared_ptr to the object of type T.
     *
     * @tparam arg The shared_ptr to an object whose @c ReferencePayload is to be created
     * @return The ReferencePayload object created for @c arg
     */
    template <typename T>
    static multiAgentExperience::ipc::messaging::ReferencePayload packageReferencePayload(const std::shared_ptr<T>& arg) {

        auto reference = multiAgentExperience::ipc::messaging::reference::createReference<T>(arg);

        auto payload = multiAgentExperience::ipc::messaging::ReferencePayload(reference);

        return payload;
    }

    /**
     * Creates a ReferenceListPayload object from the list of objects in the template parameter pack - @c args.
     *
     * @tparam args The template parameter pack which contains 0 or more arguments. Each argument is a shared_ptr to
     * an object which will be included in the @c ReferenceListPayload.
     * @return The ReferenceListPayload object created for the objects in @c args
     */
    template <typename... T>
    static multiAgentExperience::ipc::messaging::ReferenceListPayload packageReferenceListPayload(const std::shared_ptr<T>&... args) {

        std::vector<multiAgentExperience::ipc::messaging::Reference> references = {
            /// Unpack each element in the parameter pack, create a @c Reference for it, and store it in the vector.
            std::forward<multiAgentExperience::ipc::messaging::Reference>(
                multiAgentExperience::ipc::messaging::reference::createReference<T>(args)
            )...
        };

        auto payload = multiAgentExperience::ipc::messaging::ReferenceListPayload(references);

        return payload;
    }

    /**
     * Creates a ReferenceListPayload object from the vector of objects in the template parameter pack - @c args.
     *
     * @tparam args The vector which contains elements. Each element
     * will be included in the @c ReferenceListPayload.
     * @return The ReferenceListPayload object created for the objects in @c args
     */
    template <typename T>
    static multiAgentExperience::ipc::messaging::ReferenceListPayload packageReferenceListPayload(const std::vector<std::shared_ptr<T>>& args) {

        std::vector<multiAgentExperience::ipc::messaging::Reference> references;
        for(auto arg : args) {
            auto curReference = multiAgentExperience::ipc::messaging::reference::createReference<T>(arg);
            references.push_back(curReference);
        }

        auto payload = multiAgentExperience::ipc::messaging::ReferenceListPayload(references);

        return payload;
    }

};

} // namespace utils
} // namespace proxy
} // namespace ipc
} // namespace multiAgentExperience

#endif //MULTIAGENTEXPERIENCE_IPC_PROXY_UTILS_PACKAGER_H
