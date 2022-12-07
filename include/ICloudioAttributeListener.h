//
// Created by lucas on 02/12/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_ICLOUDIOATTRIBUTELISTENER_H
#define CLOUDIO_ENDPOINT_CPP_ICLOUDIOATTRIBUTELISTENER_H

namespace cloudio {

    class CloudioAttribute;

    class ICloudioAttributeListener {
    public:

        virtual ~ICloudioAttributeListener() {}

        virtual void attributeHasChanged(CloudioAttribute &attribute) = 0;
    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_ICLOUDIOATTRIBUTELISTENER_H
