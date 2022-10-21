//
// Created by lucas on 20/10/22.
//

#include "../include/CloudioAttribute.h"

namespace cloudio {

    CloudioAttribute::CloudioAttribute(string attributeName, CloudioAttributeType type,
                                       CloudioAttributeConstraint constraint) {
        this->attributeName = attributeName;
        this->attributeType = type;
        this->constraint = constraint;
        switch (this->attributeType) {
            case Invalid:
                break;

            case Boolean:
                this->value = new bool;
                break;

            case Integer:
                this->value = new int;
                break;

            case Number:
                this->value = new double;
                break;


            case String:
                this->value = new string;
                break;
        }
    }

    CloudioAttribute::~CloudioAttribute() {
        switch (this->attributeType) {
            case Invalid:
                break;

            case Boolean:
                delete ((bool *) this->value);
                break;

            case Integer:
                delete ((int *) this->value);
                break;

            case Number:
                delete ((double *) this->value);
                break;


            case String:
                delete ((string *) this->value);
                break;

        }

    }

    void *CloudioAttribute::getValue() {
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

    string CloudioAttribute::getName() {
        return this->attributeName;
    }
} // cloudio