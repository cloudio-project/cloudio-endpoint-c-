//
// Created by lucas on 31/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_ICLOUDIOOBJECTCONTAINER_H
#define CLOUDIO_ENDPOINT_CPP_ICLOUDIOOBJECTCONTAINER_H

class CloudioAttribute;

namespace cloudio {

    class ICloudioObjectContainer {
    public:
        virtual void attributeHasChangedByEndpoint(CloudioAttribute *attribute) = 0;
    };

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_ICLOUDIOOBJECTCONTAINER_H
