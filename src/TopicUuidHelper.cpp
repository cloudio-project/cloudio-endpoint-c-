//
// Created by lucas on 02/11/22.
//

#include "../include/TopicUuidHelper.h"
#include "../include/CloudioAttribute.h"

namespace cloudio {

    string getAttributeTopic(CloudioAttribute *attribute) {
        return getAttributeContainerTopic(attribute->getParent()) + "/" + attribute->getName();
    }

    string getAttributeContainerTopic(ICloudioAttributeContainer *attributeContainer) {
        return getObjectContainerTopic(attributeContainer->getParentObjectContainer()) + "/" +
               attributeContainer->getName();
    }

    string getObjectContainerTopic(ICloudioObjectContainer *objectContainer) {
        ICloudioObjectContainer *parentObjectContainer = objectContainer->getParentObjectContainer();
        if (parentObjectContainer != nullptr) {
            return getObjectContainerTopic(parentObjectContainer) + "/" + objectContainer->getName();
        }
        ICloudioNodeContainer *parentNodeContainer = objectContainer->getParentNodeContainer();
        if (parentNodeContainer != nullptr) {
            return getNodeContainerTopic(parentNodeContainer) + "/" + objectContainer->getName();
        }

        return "";
    }

    string getNodeContainerTopic(ICloudioNodeContainer *nodeContainer) {
        return nodeContainer->getName();
    }
} // cloudio