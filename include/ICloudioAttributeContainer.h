//
// Created by lucas on 31/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_ICLOUDIOATTRIBUTECONTAINER_H
#define CLOUDIO_ENDPOINT_CPP_ICLOUDIOATTRIBUTECONTAINER_H

#include "INamedItem.h"

namespace cloudio {

    class CloudioAttribute;

    class ICloudioObjectContainer;

    class ICloudioAttributeContainer : public INamedItem {
    public:

        virtual ~ICloudioAttributeContainer() {}

        virtual void attributeHasChangedByEndpoint(CloudioAttribute &attribute) = 0;

        virtual ICloudioObjectContainer *getParentObjectContainer() = 0;

    };

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_ICLOUDIOATTRIBUTECONTAINER_H
