//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP__ICLOUDIOMESSAGEFORMAT_H
#define CLOUDIO_ENDPOINT_CPP__ICLOUDIOMESSAGEFORMAT_H

#include <string>

using namespace std;

namespace cloudio {
    class CloudioEndpoint;

    class CloudioNode;

    class CloudioAttribute;

    class ICloudioMessageFormat {
    public:

        virtual ~ICloudioMessageFormat() {}

        virtual string serializeEndpoint(CloudioEndpoint *endpoint) = 0;

        virtual string serializeNode(CloudioNode *node) = 0;

        virtual string serializeAttribute(CloudioAttribute *attribute) = 0;

        virtual string serializeDidSetAttribute(CloudioAttribute *attribute, const string &correlationID) = 0;

        virtual void deserializeAttribute(const string &payload, CloudioAttribute *attribute) = 0;

        virtual string deserializeSetAttribute(const string &payload, CloudioAttribute *attribute) = 0;
    };
} // cloudio
#endif //CLOUDIO_ENDPOINT_CPP__ICLOUDIOMESSAGEFORMAT_H
