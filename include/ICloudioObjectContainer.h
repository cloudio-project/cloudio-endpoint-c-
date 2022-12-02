//
// Created by lucas on 31/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_ICLOUDIOOBJECTCONTAINER_H
#define CLOUDIO_ENDPOINT_CPP_ICLOUDIOOBJECTCONTAINER_H


#include "INamedItem.h"
#include <list>

namespace cloudio {

    class CloudioAttribute;

    class ICloudioNodeContainer;

    class ICloudioObjectContainer : public INamedItem {
    public:
        virtual void attributeHasChangedByEndpoint(CloudioAttribute *attribute) = 0;

        virtual ICloudioObjectContainer *getParentObjectContainer() = 0;

        virtual ICloudioNodeContainer *getParentNodeContainer() = 0;

        virtual CloudioAttribute* findAttribute(list<string>& topics) = 0;
    };

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_ICLOUDIOOBJECTCONTAINER_H
