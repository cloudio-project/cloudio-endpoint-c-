//
// Created by lucas on 20/10/22.
//

#include "../include/CloudioAttribute.h"
#include "../include/ICloudioAttributeContainer.h"

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

    void CloudioAttribute::setValue(int value) {
        this->setValue(value, time(nullptr));
    }

    void CloudioAttribute::setValue(double value) {
        this->setValue(value, time(nullptr));
    }

    void CloudioAttribute::setValue(string value) {
        this->setValue(value, time(nullptr));
    }

    void CloudioAttribute::setValue(bool value) {
        this->setValue(value, time(nullptr));
    }
    void CloudioAttribute::setValue(int value, long timestamp) {
        switch (this->attributeType) {
            case Invalid:
            case Boolean:
            case Number:
            case String:
                //raise exception
                break;

            case Integer:
                (*(int*)this->value) = value;
                break;
        }
    }

    void CloudioAttribute::setValue(double value, long timestamp) {

        switch (this->attributeType) {
            case Invalid:
            case Boolean:
            case Integer:
            case String:
                //raise exception
                break;

            case Number:
                (*(double*)this->value) = value;
                break;
        }
    }

    void CloudioAttribute::setValue(string value, long timestamp) {

        switch (this->attributeType) {
            case Invalid:
            case Boolean:
            case Number:
            case Integer:
                //raise exception
                break;

            case String:
                (*(string*)this->value) = value;
                break;
        }
    }

    void CloudioAttribute::setValue(bool value, long timestamp) {

        switch (this->attributeType) {
            case Invalid:
            case Integer:
            case Number:
            case String:
                //raise exception
                break;

            case Boolean:
                (*(bool*)this->value) = value;
                break;
        }
    }

    void CloudioAttribute::innerPostSetValue(long timestamp) {
        this->timestamp = timestamp;
        if(this->parent != nullptr)
        {
            this->parent->attributeHasChangedByEndpoint(this);
        }
    }

    void CloudioAttribute::setParent(ICloudioAttributeContainer *parent) {
        this->parent = parent;
    }
} // cloudio