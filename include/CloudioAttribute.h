//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP__CLOUDIOATTRIBUTE_H
#define CLOUDIO_ENDPOINT_CPP__CLOUDIOATTRIBUTE_H

#include "CloudioAttributeConstraint.h"

namespace cloudio {

    template <class AttributeType>
    class CloudioAttribute {

    public:
        CloudioAttribute();
        ~CloudioAttribute();

        AttributeType getValue();
        long getTimestamp();;

    private:
        AttributeType value;
        long timestamp;
        CloudioAttributeConstraint constraint;

    };

    template<class AttributeType>
    CloudioAttribute<AttributeType>::CloudioAttribute() {

    }

    template<class AttributeType>
    CloudioAttribute<AttributeType>::~CloudioAttribute() {

    }

    template<class AttributeType>
    AttributeType CloudioAttribute<AttributeType>::getValue() {
        return this->value;
    }

    template<class AttributeType>
    long CloudioAttribute<AttributeType>::getTimestamp() {
        return timestamp;
    }

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP__CLOUDIOATTRIBUTE_H
