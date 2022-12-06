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

using value_t = nlohmann::detail::value_t;

namespace cloudio {
    class JsonNlohmannMessageFormat : public ICloudioMessageFormat {

    private:
        class IJsonNlohmannMessageFormatSerializer {
        public:

            virtual ~IJsonNlohmannMessageFormatSerializer() {}

            virtual string serialize(json data) = 0;

            virtual json deserialize(const string &payload) = 0;
        };

        class JSONJsonNlohmannMessageFormatSerializer : public IJsonNlohmannMessageFormatSerializer {
        public:
            // IJsonNlohmannMessageFormatSerializer interface
            string serialize(json data) {
                return to_string(data);
            };

            json deserialize(const string &payload) {
                return json::parse(payload);
            }
        };

        class CBORJsonNlohmannMessageFormatSerializer : public IJsonNlohmannMessageFormatSerializer {
        public:
            // IJsonNlohmannMessageFormatSerializer interface
            string serialize(json data) {
                vector<uint8_t> cbor_data = json::to_cbor(data);
                unsigned char *cbordata = cbor_data.data();
                return string((char *) cbordata);
            };

            json deserialize(const string &payload) {
                return json::from_cbor(payload);
            };
        };

    public:
        JsonNlohmannMessageFormat(const string &format);

        ~JsonNlohmannMessageFormat();

        // ICloudioMessageFormat interface
        string serializeEndpoint(CloudioEndpoint *endpoint);

        string serializeNode(CloudioNode *node);

        string serializeAttribute(CloudioAttribute *attribute);

        string serializeDidSetAttribute(CloudioAttribute *attribute, const string &correlationID);

        void deserializeAttribute(const string &payload, CloudioAttribute *attribute);

        string deserializeSetAttribute(const string &payload, CloudioAttribute *attribute);

    private:
        static json jsonSerializeEndpoint(CloudioEndpoint *endpoint);

        static json jsonSerializeNode(CloudioNode *node);

        static json jsonSerializeObject(CloudioObject *object);

        static json jsonSerializeAttribute(CloudioAttribute *attribute);

        IJsonNlohmannMessageFormatSerializer *jsonNlohmannMessageFormatSerializer;

    };
}//cloudio

#endif //CLOUDIO_ENDPOINT_CPP_JSONNLOHMANNMESSAGEFORMAT_H
