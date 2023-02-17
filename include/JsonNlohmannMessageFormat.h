//
// Created by lucas on 20/10/22.
//
#ifdef __unix__
#ifndef CLOUDIO_ENDPOINT_CPP_JSONNLOHMANNMESSAGEFORMAT_H
#define CLOUDIO_ENDPOINT_CPP_JSONNLOHMANNMESSAGEFORMAT_H

#include "ICloudioMessageFormat.h"
#include "CloudioObject.h"

#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

namespace cloudio {
    class JsonNlohmannMessageFormat : public ICloudioMessageFormat {

    private:
        class IJsonNlohmannMessageFormatSerializer {
        public:

            virtual ~IJsonNlohmannMessageFormatSerializer() {}

            virtual std::string serialize(nlohmann::json data) = 0;

            virtual nlohmann::json deserialize(const std::string &payload) = 0;
        };

        class JSONJsonNlohmannMessageFormatSerializer : public IJsonNlohmannMessageFormatSerializer {
        public:
            // IJsonNlohmannMessageFormatSerializer interface
            std::string serialize(nlohmann::json data) {
                return to_string(data);
            };

            nlohmann::json deserialize(const std::string &payload) {
                return nlohmann::json::parse(payload);
            }
        };

        class CBORJsonNlohmannMessageFormatSerializer : public IJsonNlohmannMessageFormatSerializer {
        public:
            // IJsonNlohmannMessageFormatSerializer interface
            std::string serialize(nlohmann::json data) {
                std::vector<uint8_t> cbor_data = nlohmann::json::to_cbor(data);
                unsigned char *cbordata = cbor_data.data();
                return std::string((char *) cbordata);
            };

            nlohmann::json deserialize(const std::string &payload) {
                return nlohmann::json::from_cbor(payload);
            };
        };

    public:
        JsonNlohmannMessageFormat(const std::string &format);

        ~JsonNlohmannMessageFormat();

        // ICloudioMessageFormat interface
        std::string serializeEndpoint(CloudioEndpoint *endpoint);

        std::string serializeNode(CloudioNode *node);

        std::string serializeAttribute(CloudioAttribute *attribute);

        std::string serializeDidSetAttribute(CloudioAttribute *attribute, const std::string &correlationID);

        void deserializeAttribute(const std::string &payload, CloudioAttribute *attribute);

        std::string deserializeSetAttribute(const std::string &payload, CloudioAttribute *attribute);

    private:
        static nlohmann::json jsonSerializeEndpoint(CloudioEndpoint *endpoint);

        static nlohmann::json jsonSerializeNode(CloudioNode *node);

        static nlohmann::json jsonSerializeObject(CloudioObject *object);

        static nlohmann::json jsonSerializeAttribute(CloudioAttribute *attribute);

        IJsonNlohmannMessageFormatSerializer *jsonNlohmannMessageFormatSerializer;

    };
}//cloudio

#endif //CLOUDIO_ENDPOINT_CPP_JSONNLOHMANNMESSAGEFORMAT_H
#endif
