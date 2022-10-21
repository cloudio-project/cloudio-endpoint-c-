//
// Created by lucas on 20/10/22.
//

#include "../include/CloudioAttribute.h"

namespace cloudio {

    CloudioAttribute::CloudioAttribute() {

    }

    CloudioAttribute::~CloudioAttribute() {

    }

    void* CloudioAttribute::getValue() {
        return this->value;
    }

    long CloudioAttribute::getTimestamp() {
        return this->timestamp;
    }

    CloudioAttributeConstraint CloudioAttribute::getConstraint() {
        return this->constraint;
    }

    CloudioAttributeType CloudioAttribute::getType() {
        return this->attributeType;
    }
} // cloudio