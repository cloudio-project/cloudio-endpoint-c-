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

    list<CloudioAttribute *> CloudioObject::getAttributes() {
        return this->attributes;
    }

    void CloudioObject::addObject(CloudioObject *object) {
        this->objects.push_front(object);
    }

    void CloudioObject::addAttribute(CloudioAttribute *attribute) {
        this->attributes.push_front(attribute);
    }

    string CloudioObject::getName() {
        return this->objectName;
    }
} // cloudio