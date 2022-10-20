//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_JSONNLOHMANNMESSAGEFORMAT_H
#define CLOUDIO_ENDPOINT_CPP_JSONNLOHMANNMESSAGEFORMAT_H

#include "ICloudioMessageFormat.h"

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

        string serializeEndpoint(CloudioEndpoint endpoint);
        string serializeNode(CloudioNode node);
        string serializeAttribute(CloudioAttribute<int> attribute);
        string serializeAttribute(CloudioAttribute<double> attribute);
        string serializeAttribute(CloudioAttribute<bool> attribute);
        string serializeAttribute(CloudioAttribute<string> attribute);

    private:
        void serializeEndpoint(CloudioEndpoint endpoint, json& endpointJson);
        void serializeNode(CloudioNode node, json& nodeJson);
        void serializeAttribute(CloudioAttribute<int> attribute, json& attributeJson);
        void serializeAttribute(CloudioAttribute<double> attribute, json& attributeJson);
        void serializeAttribute(CloudioAttribute<bool> attribute, json& attributeJson);
        void serializeAttribute(CloudioAttribute<string> attribute, json& attributeJson);

    };
}//cloudio


#endif //CLOUDIO_ENDPOINT_CPP_JSONNLOHMANNMESSAGEFORMAT_H
