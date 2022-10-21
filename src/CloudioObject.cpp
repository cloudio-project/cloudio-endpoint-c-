//
// Created by lucas on 21/10/22.
//

#include "../include/CloudioObject.h"

namespace cloudio {
    string CloudioObject::getConforms() {
        return this->conforms;
    }

    list<CloudioObject *> CloudioObject::getObjects() {
        return this->objects;
    }

    list<CloudioAttribute *> CloudioObject::getAttributes() {
        return this->attributes;
    }
} // cloudio