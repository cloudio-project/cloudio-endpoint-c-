//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP__ICLOUDIOMESSAGEFORMAT_H
#define CLOUDIO_ENDPOINT_CPP__ICLOUDIOMESSAGEFORMAT_H

#include <string>
#include "CloudioEndpoint.h"
#include "CloudioNode.h"
#include "CloudioAttribute.h"

using namespace std;

namespace cloudio {
    class ICloudioMessageFormat{
    public:
        virtual char* serializeEndpoint(CloudioEndpoint endpoint) = 0;
        virtual char* serializeNode(CloudioNode node) = 0;

        virtual char* serializeAttribute(CloudioAttribute<int> attribute) = 0;
        virtual char* serializeAttribute(CloudioAttribute<double> attribute) = 0;
        virtual char* serializeAttribute(CloudioAttribute<bool> attribute) = 0;
        virtual char* serializeAttribute(CloudioAttribute<string> attribute) = 0;
    };
} // cloudio
#endif //CLOUDIO_ENDPOINT_CPP__ICLOUDIOMESSAGEFORMAT_H
