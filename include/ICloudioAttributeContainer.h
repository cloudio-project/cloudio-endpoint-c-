//
// Created by lucas on 31/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_ICLOUDIOATTRIBUTECONTAINER_H
#define CLOUDIO_ENDPOINT_CPP_ICLOUDIOATTRIBUTECONTAINER_H


namespace cloudio {

    class CloudioAttribute;
    class ICloudioAttributeContainer {
    public:
        virtual void attributeHasChangedByEndpoint(CloudioAttribute *attribute) = 0;
    };

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_ICLOUDIOATTRIBUTECONTAINER_H
