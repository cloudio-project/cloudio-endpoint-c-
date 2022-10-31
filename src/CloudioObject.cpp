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
        if(this->parent != nullptr)
        {
            this->parent->attributeHasChangedByEndpoint(attribute);
        }
    }

    void CloudioObject::setParent(ICloudioObjectContainer *parent) {
        this->parent = parent;
    }
} // cloudio