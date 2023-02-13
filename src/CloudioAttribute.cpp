//
// Created by lucas on 20/10/22.
//

#include "../include/CloudioAttribute.h"
#include "../include/ICloudioAttributeContainer.h"

#include "../include/ESP32TimestampManager.h"
#include "../include/BasicTimestampManager.h"

using namespace std;

namespace cloudio {

    CloudioAttribute::CloudioAttribute(const string &attributeName, const CloudioAttributeType type,
                                       const CloudioAttributeConstraint constraint) {
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

#ifdef ESP_PLATFORM
        timestampManager = &ESP32TimestampManager::getInstance();
#else
        timestampManager = &BasicTimestampManager::getInstance();
#endif
    }

    CloudioAttribute::CloudioAttribute(const string &attributeName, const CloudioAttributeType type,
                                       const CloudioAttributeConstraint constraint, const int initialValue) :
            CloudioAttribute(attributeName, type, constraint) {
        (*(int *) this->value) = initialValue;

    }

    CloudioAttribute::CloudioAttribute(const string &attributeName, const CloudioAttributeType type,
                                       const CloudioAttributeConstraint constraint, const double initialValue) :
            CloudioAttribute(attributeName, type, constraint) {
        (*(double *) this->value) = initialValue;
    }

    CloudioAttribute::CloudioAttribute(const string &attributeName, const CloudioAttributeType type,
                                       const CloudioAttributeConstraint constraint, const string initialValue) :
            CloudioAttribute(attributeName, type, constraint) {
        (*(string *) this->value) = initialValue;
    }

    CloudioAttribute::CloudioAttribute(const string &attributeName, const CloudioAttributeType type,
                                       const CloudioAttributeConstraint constraint, const bool initialValue) :
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

    int64_t CloudioAttribute::getTimestamp() {
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

    void CloudioAttribute::setValue(const int intValue) {
        this->setValue(intValue, timestampManager->getTimestamp());
    }

    void CloudioAttribute::setValue(const double doubleValue) {
        this->setValue(doubleValue, timestampManager->getTimestamp());
    }

    void CloudioAttribute::setValue(const string &stringValue) {
        this->setValue(stringValue, timestampManager->getTimestamp());
    }

    void CloudioAttribute::setValue(const bool boolValue) {
        this->setValue(boolValue, timestampManager->getTimestamp());
    }

    void CloudioAttribute::setValue(const int intValue, const int64_t newTimestamp) {
        this->innerPreSetValue();

        this->setIntegerValue(intValue);

        this->innerPostSetValue(newTimestamp);
    }

    void CloudioAttribute::setValue(const double doubleValue, const int64_t newTimestamp) {
        this->innerPreSetValue();

        this->setNumberValue(doubleValue);

        this->innerPostSetValue(newTimestamp);
    }

    void CloudioAttribute::setValue(const string &stringValue, const int64_t newTimestamp) {
        this->innerPreSetValue();

        this->setStringValue(stringValue);

        this->innerPostSetValue(newTimestamp);
    }

    void CloudioAttribute::setValue(const bool boolValue, const int64_t newTimestamp) {
        this->innerPreSetValue();

        this->setBooleanValue(boolValue);

        this->innerPostSetValue(newTimestamp);
    }

    CloudioAttribute& CloudioAttribute::operator=(int intValue) {
        setValue(intValue);
        return *this;
    }

    CloudioAttribute& CloudioAttribute::operator=(double doubleValue) {
        setValue(doubleValue);
        return *this;
    }

    CloudioAttribute& CloudioAttribute::operator=(const std::string &stringValue) {
        setValue(stringValue);
        return *this;
    }

    CloudioAttribute& CloudioAttribute::operator=(bool boolValue) {
        setValue(boolValue);
        return *this;
    }

    bool CloudioAttribute::setValueFromCloud(const int intValue, const int64_t newTimestamp) {
        bool isSetPossible = innerPostSetValueFromCloud(newTimestamp);

        if (isSetPossible) {
            setIntegerValue(intValue);
            this->notifyListeners();
        }
        return isSetPossible;
    }

    bool CloudioAttribute::setValueFromCloud(double doubleValue, int64_t newTimestamp) {
        bool isSetPossible = innerPostSetValueFromCloud(newTimestamp);

        if (isSetPossible) {
            setNumberValue(doubleValue);
            this->notifyListeners();
        }
        return isSetPossible;
    }

    bool CloudioAttribute::setValueFromCloud(const string &stringValue, int64_t newTimestamp) {
        bool isSetPossible = innerPostSetValueFromCloud(newTimestamp);

        if (isSetPossible) {
            setStringValue(stringValue);
            this->notifyListeners();
        }
        return isSetPossible;
    }

    bool CloudioAttribute::setValueFromCloud(const bool boolValue, const int64_t newTimestamp) {
        bool isSetPossible = innerPostSetValueFromCloud(newTimestamp);

        if (isSetPossible) {
            setBooleanValue(boolValue);
            this->notifyListeners();
        }
        return isSetPossible;
    }

    bool CloudioAttribute::innerPostSetValueFromCloud(const int64_t newTimestamp) {
        if (this->constraint != Parameter && this->constraint != SetPoint) {
            throw CloudioAttributeConstrainException(
                    "Can not change an attribute whose constraint is neither Parameter nor SetPoint ");
        }
        if (this->timestamp >= newTimestamp)
            return false;

        this->timestamp = newTimestamp;
        return true;
    }

    void CloudioAttribute::setIntegerValue(const int intValue) {
        if (this->attributeType == Integer) {
            (*(int *) this->value) = intValue;
        } else {
            throw CloudioAttributeTypeException("Cannot use setIntegerValue on an attribute of type " + string(
                    to_string(this->attributeType)));
        }
    }

    void CloudioAttribute::setNumberValue(const double doubleValue) {
        if (this->attributeType == Number) {
            (*(double *) this->value) = doubleValue;
        } else {
            throw CloudioAttributeTypeException("Cannot use setNumberValue on an attribute of type " + string(
                    to_string(this->attributeType)));
        }
    }

    void CloudioAttribute::setStringValue(const string &stringValue) {
        if (this->attributeType == String) {
            (*(string *) this->value) = stringValue;
        } else {
            throw CloudioAttributeTypeException("Cannot use setStringValue on an attribute of type " + string(
                    to_string(this->attributeType)));
        }
    }

    void CloudioAttribute::setBooleanValue(const bool boolValue) {
        if (this->attributeType == Boolean) {
            (*(bool *) this->value) = boolValue;
        } else {
            throw CloudioAttributeTypeException("Cannot use setBooleanValue on an attribute of type " + string(
                    to_string(this->attributeType)));
        }
    }

    void CloudioAttribute::innerPreSetValue() {
        if (this->constraint != Status && this->constraint != Measure) {
            throw CloudioAttributeConstrainException("Can only change Status and Measure constraint attribute, not " +
                                                     to_string(this->constraint));
        }
    }

    void CloudioAttribute::innerPostSetValue(const int64_t newTimestamp) {
        this->timestamp = newTimestamp;
        if (this->parent != nullptr) {
            this->parent->attributeHasChangedByEndpoint(*this);
        }
    }

    void CloudioAttribute::setParent(ICloudioAttributeContainer *const newParent) {
        this->parent = newParent;
    }

    ICloudioAttributeContainer *CloudioAttribute::getParent() {
        return this->parent;
    }

    void CloudioAttribute::addListener(ICloudioAttributeListener *const listener) {
        this->listeners.push_back(listener);
    }

    void CloudioAttribute::removeListener(ICloudioAttributeListener *const listener) {
        this->listeners.remove(listener);
    }

    void CloudioAttribute::notifyListeners() {
        if (!this->listeners.empty()) {
            for (auto &listener: this->listeners) {
                listener->attributeHasChanged(*this);
            }
        }
    }
} // cloudio
