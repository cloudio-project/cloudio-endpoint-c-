//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP__CLOUDIOATTRIBUTE_H
#define CLOUDIO_ENDPOINT_CPP__CLOUDIOATTRIBUTE_H

#include "CloudioAttributeConstraint.h"
#include "CloudioAttributeType.h"

#include <string>

using namespace std;

namespace cloudio {

    class CloudioAttribute {

    public:
        CloudioAttribute(string attributeName, CloudioAttributeType type, CloudioAttributeConstraint constraint);

        ~CloudioAttribute();

        void *getValue();

        long getTimestamp();

        CloudioAttributeConstraint getConstraint();;

        CloudioAttributeType getType();

        string getName();


    private:
        void *value;
        long timestamp = 0;
        CloudioAttributeConstraint constraint;
        CloudioAttributeType attributeType;
        string attributeName;

    };

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP__CLOUDIOATTRIBUTE_H
