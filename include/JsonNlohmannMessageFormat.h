//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_JSONNLOHMANNMESSAGEFORMAT_H
#define CLOUDIO_ENDPOINT_CPP_JSONNLOHMANNMESSAGEFORMAT_H

#include "ICloudioMessageFormat.h"
#include "CloudioObject.h"

#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

namespace cloudio {
    class JsonNlohmannMessageFormat : public ICloudioMessageFormat {

    public:
        JsonNlohmannMessageFormat();

        ~JsonNlohmannMessageFormat();

        string serializeEndpoint(CloudioEndpoint *endpoint);

        string serializeNode(CloudioNode *node);

        string serializeAttribute(CloudioAttribute *attribute);

        void deserializeAttribute(string payload, CloudioAttribute *attribute);

        string deserializeSetAttribute(string payload, CloudioAttribute *attribute);

    private:
        static json jsonSerializeEndpoint(CloudioEndpoint *endpoint);

        static json jsonSerializeNode(CloudioNode *node);

        static json jsonSerializeObject(CloudioObject *object);

        static json jsonSerializeAttribute(CloudioAttribute *attribute);

    };
}//cloudio

#endif //CLOUDIO_ENDPOINT_CPP_JSONNLOHMANNMESSAGEFORMAT_H
