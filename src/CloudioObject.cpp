//
// Created by lucas on 21/10/22.
//

#include "../include/CloudioObject.h"

namespace cloudio {

    CloudioObject::CloudioObject(string objectName) {
        this->objectName = objectName;
    }

    CloudioObject::~CloudioObject() {

    }

    string CloudioObject::getConforms() {
        return this->conforms;
    }

    list<CloudioObject *> CloudioObject::getObjects() {
        return this->objects;
    }

    CloudioObject *CloudioObject::getObjectByName(string objectName) {
        for (auto &objectIt: this->objects) {
            if (objectIt->getName() == objectName) {
                return objectIt;
            }
        }
        return nullptr;
    }

    list<CloudioAttribute *> CloudioObject::getAttributes() {
        return this->attributes;
    }

    CloudioAttribute *CloudioObject::getAttributeByName(string attributeName) {
        for (auto &attributeIt: this->attributes) {
            if (attributeIt->getName() == attributeName) {
                return attributeIt;
            }
        }
        return nullptr;
    }

    void CloudioObject::addObject(CloudioObject *object) {
        object->setParent(this);
        this->objects.push_front(object);
    }

    void CloudioObject::addAttribute(CloudioAttribute *attribute) {
        attribute->setParent(this);
        this->attributes.push_front(attribute);
    }

    string CloudioObject::getName() {
        return this->objectName;
    }

    void CloudioObject::attributeHasChangedByEndpoint(CloudioAttribute *attribute) {
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


    CloudioAttribute *CloudioObject::findAttribute(list<string> &location) {
        if (!location.empty()) {
            if (location.size() > 1) {
                CloudioObject *object = getObjectByName(location.front());
                location.pop_front(); // pop object name
                if (object != nullptr) {
                    return object->findAttribute(location);
                }
            } else {
                if (!location.empty()) {
                    CloudioAttribute *attribute = getAttributeByName(location.front());
                    location.pop_front(); // pop attribute name
                    if (attribute != nullptr && location.empty()) {
                        return attribute;
                    }
                }
            }
        }
        return nullptr;
    }
} // cloudio