//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP__ICLOUDIOMESSAGEFORMAT_H
#define CLOUDIO_ENDPOINT_CPP__ICLOUDIOMESSAGEFORMAT_H

#include <string>

namespace cloudio {
    class CloudioEndpoint;

    class CloudioNode;

    class CloudioAttribute;

    class ICloudioMessageFormat {
    public:

        virtual ~ICloudioMessageFormat() {}

        virtual std::string serializeEndpoint(CloudioEndpoint *endpoint) = 0;

        virtual std::string serializeNode(CloudioNode *node) = 0;

        virtual std::string serializeAttribute(CloudioAttribute *attribute) = 0;

        virtual std::string serializeDidSetAttribute(CloudioAttribute *attribute, const std::string &correlationID) = 0;

        virtual void deserializeAttribute(const std::string &payload, CloudioAttribute *attribute) = 0;

        virtual std::string deserializeSetAttribute(const std::string &payload, CloudioAttribute *attribute) = 0;
    };
} // cloudio
#endif //CLOUDIO_ENDPOINT_CPP__ICLOUDIOMESSAGEFORMAT_H
