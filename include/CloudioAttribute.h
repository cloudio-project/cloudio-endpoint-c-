//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP__CLOUDIOATTRIBUTE_H
#define CLOUDIO_ENDPOINT_CPP__CLOUDIOATTRIBUTE_H

#include "CloudioAttributeConstraint.h"
#include "CloudioAttributeType.h"
#include "CloudioAttributeConstrainException.h"
#include "ICloudioAttributeListener.h"

#include <string>
#include <list>

using namespace std;

namespace cloudio {

    class ICloudioAttributeContainer;

    class CloudioAttribute {

    public:
        CloudioAttribute(string attributeName, CloudioAttributeType type, CloudioAttributeConstraint constraint);

        CloudioAttribute(string attributeName, CloudioAttributeType type, CloudioAttributeConstraint constraint,
                         int initialValue);

        CloudioAttribute(string attributeName, CloudioAttributeType type, CloudioAttributeConstraint constraint,
                         double initialValue);

        CloudioAttribute(string attributeName, CloudioAttributeType type, CloudioAttributeConstraint constraint,
                         string initialValue);

        CloudioAttribute(string attributeName, CloudioAttributeType type, CloudioAttributeConstraint constraint,
                         bool initialValue);

        ~CloudioAttribute();

        void *getValue();

        long getTimestamp();

        CloudioAttributeConstraint getConstraint();;

        CloudioAttributeType getType();

        string getName();

        void setValue(int value);

        void setValue(double value);

        void setValue(string value);

        void setValue(bool value);

        void setValue(int value, long timestamp);

        void setValue(double value, long timestamp);

        void setValue(string value, long timestamp);

        void setValue(bool value, long timestamp);

        bool setValueFromCloud(int value, long timestamp);

        bool setValueFromCloud(double value, long timestamp);

        bool setValueFromCloud(string value, long timestamp);

        bool setValueFromCloud(bool value, long timestamp);

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

            void innerPostSetValue(long timestamp);

            void setIntegerValue(int value);

            void setNumberValue(double value);

            void setStringValue(string value);

            void setBooleanValue(bool value);

        };

    } // cloudio

#endif //CLOUDIO_ENDPOINT_CPP__CLOUDIOATTRIBUTE_H
