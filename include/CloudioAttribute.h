//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTE_H
#define CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTE_H

#include "CloudioAttributeConstraint.h"
#include "CloudioAttributeType.h"
#include "ICloudioAttributeListener.h"
#include "ITimestampManager.h"

#include "../include/CloudioAttributeConstrainException.h"
#include "../include/CloudioAttributeTypeException.h"

#include <stdint.h>
#include <string>
#include <list>

namespace cloudio {

    class ICloudioAttributeContainer;

    class CloudioAttribute {

    public:
        CloudioAttribute(const std::string &attributeName, CloudioAttributeType type,
                         CloudioAttributeConstraint constraint);

        CloudioAttribute(const std::string &attributeName, CloudioAttributeType type,
                         CloudioAttributeConstraint constraint,
                         int initialValue);

        CloudioAttribute(const std::string &attributeName, CloudioAttributeType type,
                         CloudioAttributeConstraint constraint,
                         double initialValue);

        CloudioAttribute(const std::string &attributeName, CloudioAttributeType type,
                         CloudioAttributeConstraint constraint,
                         std::string initialValue);

        CloudioAttribute(const std::string &attributeName, CloudioAttributeType type,
                         CloudioAttributeConstraint constraint,
                         bool initialValue);

        ~CloudioAttribute();

        void *getValue();

        int64_t getTimestamp();

        CloudioAttributeConstraint getConstraint();;

        CloudioAttributeType getType();

        std::string getName();

        void setValue(int intValue);

        void setValue(double doubleValue);

        void setValue(const std::string &stringValue);

        void setValue(bool boolValue);

        void setValue(int intValue, int64_t newTimestamp);

        void setValue(double doubleValue, int64_t newTimestamp);

        void setValue(const std::string &stringValue, int64_t newTimestamp);

        void setValue(bool boolValue, int64_t newTimestamp);

        CloudioAttribute &operator=(int intValue);

        CloudioAttribute &operator=(double doubleValue);

        CloudioAttribute &operator=(const std::string &stringValue);

        CloudioAttribute &operator=(bool boolValue);

        bool setValueFromCloud(int intValue, int64_t newTimestamp);

        bool setValueFromCloud(double doubleValue, int64_t newTimestamp);

        bool setValueFromCloud(const std::string &stringValue, int64_t newTimestamp);

        bool setValueFromCloud(bool boolValue, int64_t newTimestamp);

        void setParent(ICloudioAttributeContainer *parent);

        ICloudioAttributeContainer *getParent();

        void addListener(ICloudioAttributeListener *listener);

        void removeListener(ICloudioAttributeListener *listener);


    private:
        void *value;
        int64_t timestamp = 0;
        CloudioAttributeConstraint constraint;
        CloudioAttributeType attributeType;
        std::string attributeName;
        ICloudioAttributeContainer *parent = nullptr;
        std::list<ICloudioAttributeListener *> listeners;

        ITimestampManager *timestampManager;

        void innerPreSetValue();

        void innerPostSetValue(int64_t newTimestamp);

        bool innerPostSetValueFromCloud(int64_t newTimestamp);

        void setIntegerValue(int intValue);

        void setNumberValue(double doubleValue);

        void setStringValue(const std::string &stringValue);

        void setBooleanValue(bool value);

        void notifyListeners();
    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTE_H
