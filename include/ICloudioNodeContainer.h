//
// Created by lucas on 31/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_ICLOUDIONODECONTAINER_H
#define CLOUDIO_ENDPOINT_CPP_ICLOUDIONODECONTAINER_H

#include "INamedItem.h"

namespace cloudio {

    class CloudioAttribute;

    class ICloudioNodeContainer : public INamedItem {
    public:
        virtual ~ICloudioNodeContainer() {}

        virtual void attributeHasChangedByEndpoint(CloudioAttribute *attribute) = 0;
    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_ICLOUDIONODECONTAINER_H
