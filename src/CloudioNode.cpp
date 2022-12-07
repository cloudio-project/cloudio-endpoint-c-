//
// Created by lucas on 20/10/22.
//

#include "../include/CloudioNode.h"

using namespace std;

namespace cloudio {

    CloudioNode::CloudioNode(string nodeName) {
        this->nodeName = nodeName;
    }

    CloudioNode::~CloudioNode() {

    }

    vector<CloudioObject *> CloudioNode::getObjects() {
        return this->objects;
    }

    CloudioObject *CloudioNode::getObjectByName(string objectName) {
        for (auto &objectIt: this->objects) {
            if (objectIt->getName() == objectName) {
                return objectIt;
            }
        }
        return nullptr;
    }

    vector <string> CloudioNode::getInterfaces() {
        return this->interfaces;
    }

    void CloudioNode::addObject(CloudioObject *const object) {
        object->setParent(this);
        this->objects.push_back(object);
    }

    string CloudioNode::getName() {
        return this->nodeName;
    }

    void CloudioNode::attributeHasChangedByEndpoint(CloudioAttribute *const attribute) {
        if (this->parent != nullptr) {
            this->parent->attributeHasChangedByEndpoint(attribute);
        }
    }

    void CloudioNode::setParent(ICloudioNodeContainer *const parent) {
        this->parent = parent;
    }

    ICloudioObjectContainer *CloudioNode::getParentObjectContainer() {
        return nullptr;
    }

    ICloudioNodeContainer *CloudioNode::getParentNodeContainer() {
        return parent;
    }


    CloudioAttribute *CloudioNode::findAttribute(queue <string> &location) {
        if (!location.empty()) {
            CloudioObject *object = this->getObjectByName(location.front());
            location.pop(); //pop object name
            if (object != nullptr) {
                return object->findAttribute(location);
            }
        }
        return nullptr;
    }
} // cloudio