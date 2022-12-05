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

    private:
        class IJsonNlohmannMessageFormatSerializer {
        public:
            virtual string serialize(json data) = 0;

            virtual json deserialize(string payload) = 0;
        };

        class JSONJsonNlohmannMessageFormatSerializer : public IJsonNlohmannMessageFormatSerializer {
        public:
            string serialize(json data) {
                return to_string(data);
            };

            json deserialize(string payload) {
                return json::parse(payload);
            }
        };

        class CBORJsonNlohmannMessageFormatSerializer : public IJsonNlohmannMessageFormatSerializer {
        public:
            string serialize(json data) {
                vector<uint8_t> cbor_data = json::to_cbor(data);
                unsigned char *cbordata = cbor_data.data();
                return string((char *) cbordata);
            };

            json deserialize(string payload) {
                return json::from_cbor(payload);
            };
        };

    public:
        JsonNlohmannMessageFormat(string format);

        ~JsonNlohmannMessageFormat();

        string serializeEndpoint(CloudioEndpoint *endpoint);

        string serializeNode(CloudioNode *node);

        string serializeAttribute(CloudioAttribute *attribute);

        string serializeDidSetAttribute(CloudioAttribute *attribute, string correlationID);

        void deserializeAttribute(string payload, CloudioAttribute *attribute);

        string deserializeSetAttribute(string payload, CloudioAttribute *attribute);


    private:
        static json jsonSerializeEndpoint(CloudioEndpoint *endpoint);

        static json jsonSerializeNode(CloudioNode *node);

        static json jsonSerializeObject(CloudioObject *object);

        static json jsonSerializeAttribute(CloudioAttribute *attribute);

        IJsonNlohmannMessageFormatSerializer *jsonNolhmannMessageFormatSerializer;


    };
}//cloudio

#endif //CLOUDIO_ENDPOINT_CPP_JSONNLOHMANNMESSAGEFORMAT_H
