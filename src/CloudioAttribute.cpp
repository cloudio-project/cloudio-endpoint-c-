//
// Created by lucas on 20/10/22.
//

#include "../include/CloudioAttribute.h"
#include "../include/ICloudioAttributeContainer.h"
#include "../include/CloudioAttributeConstrainException.h"

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

    CloudioAttribute::CloudioAttribute(string attributeName, CloudioAttributeType type,
                                       CloudioAttributeConstraint constraint, int initialValue) :
            CloudioAttribute(attributeName, type, constraint) {
        (*(int *) this->value) = initialValue;

    }

    CloudioAttribute::CloudioAttribute(string attributeName, CloudioAttributeType type,
                                       CloudioAttributeConstraint constraint, double initialValue) :
            CloudioAttribute(attributeName, type, constraint) {
        (*(double *) this->value) = initialValue;
    }

    CloudioAttribute::CloudioAttribute(string attributeName, CloudioAttributeType type,
                                       CloudioAttributeConstraint constraint, string initialValue) :
            CloudioAttribute(attributeName, type, constraint) {
        (*(string *) this->value) = initialValue;
    }

    CloudioAttribute::CloudioAttribute(string attributeName, CloudioAttributeType type,
                                       CloudioAttributeConstraint constraint, bool initialValue) :
            CloudioAttribute(attributeName, type, constraint) {
        (*(bool *) this->value) = initialValue;
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
        this->innerPreSetValue();

        if (this->attributeType == Integer) {
            (*(int *) this->value) = value;
        } else {
            // raise exception
        }
        this->innerPostSetValue(timestamp);
    }

    void CloudioAttribute::setValue(double value, long timestamp) {
        this->innerPreSetValue();

        if (this->attributeType == Number) {
            (*(double *) this->value) = value;
        } else {
            // raise exception
        }
        this->innerPostSetValue(timestamp);
    }

    void CloudioAttribute::setValue(string value, long timestamp) {
        this->innerPreSetValue();

        if (this->attributeType == String) {
            (*(string *) this->value) = value;
        } else {
            // raise exception
        }
        this->innerPostSetValue(timestamp);
    }

    void CloudioAttribute::setValue(bool value, long timestamp) {
        this->innerPreSetValue();

        if (this->attributeType == Boolean) {
            (*(bool *) this->value) = value;
        } else {
            // raise exception
        }
        this->innerPostSetValue(timestamp);
    }

    void CloudioAttribute::innerPreSetValue() {
        if (this->constraint != Status && this->constraint != Measure) {
            string message = "Can only change Status and Measure constraint attribute";
            throw CloudioAttributeConstrainException("Can only change Status and Measure constraint attribute");
        }
    }

    void CloudioAttribute::innerPostSetValue(long timestamp) {
        this->timestamp = timestamp;
        if (this->parent != nullptr) {
            this->parent->attributeHasChangedByEndpoint(this);
        }
    }

    void CloudioAttribute::setParent(ICloudioAttributeContainer *parent) {
        this->parent = parent;
    }

    ICloudioAttributeContainer *CloudioAttribute::getParent() {
        return this->parent;
    }
} // cloudio