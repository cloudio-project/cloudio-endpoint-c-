//
// Created by lucas on 21/10/22.
//

#include "../include/CloudioObject.h"

using namespace std;

namespace cloudio {

    CloudioObject::CloudioObject(const string &objectName) {
        this->objectName = objectName;
    }

    CloudioObject::~CloudioObject() {

    }

    const string &CloudioObject::getConforms() const {
        return this->conforms;
    }

    const vector<CloudioObject *> &CloudioObject::getObjects() {
        return this->objects;
    }

    CloudioObject *CloudioObject::getObjectByName(const string &objectName) {
        for (auto &objectIt: this->objects) {
            if (objectIt->getName() == objectName) {
                return objectIt;
            }
        }
        return nullptr;
    }

    const vector<CloudioAttribute *> &CloudioObject::getAttributes() {
        return this->attributes;
    }

    CloudioAttribute *CloudioObject::getAttributeByName(const string &attributeName) {
        for (auto &attributeIt: this->attributes) {
            if (attributeIt->getName() == attributeName) {
                return attributeIt;
            }
        }
        return nullptr;
    }

    void CloudioObject::addObject(CloudioObject *const object) {
        object->setParent(this);
        this->objects.push_back(object);
    }

    void CloudioObject::addAttribute(CloudioAttribute *const attribute) {
        attribute->setParent(this);
        this->attributes.push_back(attribute);
    }

    const std::string &CloudioObject::getName() const {
        return this->objectName;
    }

    void CloudioObject::attributeHasChangedByEndpoint(CloudioAttribute &attribute) {
        if (this->parent != nullptr) {
            this->parent->attributeHasChangedByEndpoint(attribute);
        }
    }

    void CloudioObject::setParent(ICloudioObjectContainer *parent) {
        this->parent = parent;
    }

    ICloudioObjectContainer *CloudioObject::getParentObjectContainer() {
        return parent;
    }

    ICloudioNodeContainer *CloudioObject::getParentNodeContainer() {
        return nullptr;
    }


    CloudioAttribute *CloudioObject::findAttribute(queue <string> &location) {
        if (!location.empty()) {
            if (location.size() > 1) {
                CloudioObject *object = getObjectByName(location.front());
                location.pop(); // pop object name
                if (object != nullptr) {
                    return object->findAttribute(location);
                }
            } else {
                if (!location.empty()) {
                    CloudioAttribute *attribute = getAttributeByName(location.front());
                    location.pop(); // pop attribute name
                    if (attribute != nullptr && location.empty()) {
                        return attribute;
                    }
                }
            }
        }
        return nullptr;
    }
} // cloudio