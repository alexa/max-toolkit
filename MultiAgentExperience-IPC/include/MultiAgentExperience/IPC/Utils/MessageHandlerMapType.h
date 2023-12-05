/*
* Copyright 2023 Amazon.com, Inc. or its affiliates. All Rights Reserved.
*
* You may not use this file except in compliance with the terms and conditions
* set forth in the accompanying LICENSE file.
*/

#ifndef MULTIAGENTEXPERIENCE_IPC_UTILS_CUSTOMMESSAGEHANDLERMAP_H
#define MULTIAGENTEXPERIENCE_IPC_UTILS_CUSTOMMESSAGEHANDLERMAP_H

#include <iostream>
#include <map>
#include <memory>

#include <MultiAgentExperience/IPC/Messaging/Reference.h>

/**
 * @tparam MessageHandlerType
 * @tparam OwningObjectType
 *
 * This ValueStruct object is the value corresponding to the "Reference" key in the respective
 * MessageHandlerMap. For instance in "MessageHandlerStore.h" for "m_activityManagerMessageHandlers"
 * map the key is a multiAgentExperience::ipc::messaging::Reference object and the value corresponding to this
 * key will be a ValueStruct object that encapsulates the following two things :
 *
 * 1) "shared_ptr" to the actual "MessageHandler" object that is created
 * 2) "weak_ptr" to the object for which the "MessageHandler" is created (this object we identify as
 * the owning object because if this goes out of scope i.e. if the actual object goes out of
 * scope then all the objects created for it should go out of scope as well and hence it's helpful
 * in determining which entries to clean-up from the respective map)
 */
template<typename MessageHandlerType, typename OwningObjectType>
struct ValueStruct {
    std::shared_ptr<MessageHandlerType> m_messageHandlerObject;
    std::weak_ptr<OwningObjectType> m_owningObject;
};

/**
 *
 * @tparam MessageHandlerType
 * @tparam OwningObjectType
 *
 * This data type is what we will use in order to create respective MessageHandler maps in
 * MessageHandlerStore.h for instance "m_activityManagerMessageHandlers". This type inherits from
 * std::map and overrides the "insert()" function of std::map in order to remove dead/stale entries
 * in the map. The way dead/stale entries are identified can be seen from "removeStaleEntries"
 * function which essentially checks the validity of the owning object and if it doesn't exist/
 * is invalid the corresponding entry is deleted from the map
 */
template<typename MessageHandlerType, typename OwningObjectType>
class MessageHandlerMapType : public std::map<multiAgentExperience::ipc::messaging::Reference,
    ValueStruct<MessageHandlerType, OwningObjectType>> {
 public:
    /// Override std::map's "insert()" function to remove expired entries from the MessageHandler
    /// map
    void insert(const multiAgentExperience::ipc::messaging::Reference& key, const
    ValueStruct<MessageHandlerType, OwningObjectType>& value) {
        /// Remove entries with 0 strong reference count for the owning object if there are any
        /// as a "0" strong reference count indicates an expired/out-of-scope object
        removeDeadEntries();

        /// Insert the new key-value pair in the MessageHandler map
        std::map<multiAgentExperience::ipc::messaging::Reference, ValueStruct<MessageHandlerType,
        OwningObjectType>>::insert(std::make_pair(key, value));
    }

 private:
    void removeDeadEntries() {
        auto messageHandlerMapIterator = this->begin();

        while (messageHandlerMapIterator != this->end()) {
            auto owningObjectSharedPtr = messageHandlerMapIterator->second.m_owningObject.lock();
            if (owningObjectSharedPtr) {
                ++messageHandlerMapIterator;
            } else {
                /// this is a safe operation because "erase()" after erasing the current entry
                /// returns an iterator to the next entry in the map
                messageHandlerMapIterator = this->erase(messageHandlerMapIterator);
            }
        }
    }
};

#endif // MULTIAGENTEXPERIENCE_IPC_UTILS_CUSTOMMESSAGEHANDLERMAP_H