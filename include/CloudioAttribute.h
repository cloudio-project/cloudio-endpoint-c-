//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTE_H
#define CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTE_H

#include "CloudioAttributeConstraint.h"
#include "CloudioAttributeType.h"
#include "ICloudioAttributeListener.h"

#include "../include/CloudioAttributeConstrainException.h"
#include "../include/CloudioAttributeTypeException.h"

#include <string>
#include <list>

using namespace std;

namespace cloudio {

    class ICloudioAttributeContainer;

    class CloudioAttribute {

    public:
        CloudioAttribute(const string &attributeName, CloudioAttributeType type, CloudioAttributeConstraint constraint);

        CloudioAttribute(const string &attributeName, CloudioAttributeType type, CloudioAttributeConstraint constraint,
                         int initialValue);

        CloudioAttribute(const string &attributeName, CloudioAttributeType type, CloudioAttributeConstraint constraint,
                         double initialValue);

        CloudioAttribute(const string &attributeName, CloudioAttributeType type, CloudioAttributeConstraint constraint,
                         string initialValue);

        CloudioAttribute(const string &attributeName, CloudioAttributeType type, CloudioAttributeConstraint constraint,
                         bool initialValue);

        ~CloudioAttribute();

        void *getValue();

        long getTimestamp();

        CloudioAttributeConstraint getConstraint();;

        CloudioAttributeType getType();

        string getName();

        void setValue(int intValue);

        void setValue(double doubleValue);

        void setValue(const string &stringValue);

        void setValue(bool boolValue);

        void setValue(int intValue, long newTimestamp);

        void setValue(double doubleValue, long newTimestamp);

        void setValue(const string &stringValue, long newTimestamp);

        void setValue(bool boolValue, long newTimestamp);

        bool setValueFromCloud(int intValue, long newTimestamp);

        bool setValueFromCloud(double doubleValue, long newTimestamp);

        bool setValueFromCloud(const string &stringValue, long newTimestamp);

        bool setValueFromCloud(bool boolValue, long newTimestamp);

        void setParent(ICloudioAttributeContainer *parent);

        ICloudioAttributeContainer *getParent();

        void addListener(ICloudioAttributeListener *listener);

        void removeListener(ICloudioAttributeListener *listener);


    private:
        void *value;
        long timestamp = 0;
        CloudioAttributeConstraint constraint;
        CloudioAttributeType attributeType;
        string attributeName;
        ICloudioAttributeContainer *parent = nullptr;
        list<ICloudioAttributeListener *> listeners;

        void innerPreSetValue();

        void innerPostSetValue(long newTimestamp);

        bool innerPostSetValueFromCloud(long newTimestamp);

        void setIntegerValue(int intValue);

        void setNumberValue(double doubleValue);

        void setStringValue(const string &stringValue);

        void setBooleanValue(bool value);

        void notifyListeners();
    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTE_H
