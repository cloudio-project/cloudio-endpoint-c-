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

    list<string> split(string s, string delimiter) {
        size_t pos_start = 0, pos_end, delim_len = delimiter.length();
        string token;
        list<string> res;

        while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
            token = s.substr(pos_start, pos_end - pos_start);
            pos_start = pos_end + delim_len;
            res.push_back(token);
        }

        res.push_back(s.substr(pos_start));
        return res;
    }
} // cloudio