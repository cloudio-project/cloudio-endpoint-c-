//
// Created by lucas on 05/12/22.
//

#include "../include/CloudioMessageFormatFactory.h"
#include "../include/JsonNlohmannMessageFormat.h"

namespace cloudio {

    static ICloudioMessageFormat *json;
    static ICloudioMessageFormat *cbor;

    ICloudioMessageFormat *CloudioMessageFormatFactory::messageFormat(char messageFormatId) {
        if (messageFormatId == '{') {
            if (json == nullptr) json = new JsonNlohmannMessageFormat("JSON");
            return json;
        } else if ((messageFormatId & 0b11100000) == 0b10100000) {
            if (cbor == nullptr) cbor = new JsonNlohmannMessageFormat("CBOR");
            return cbor;
        } else {
            return nullptr;
        }
    }

    ICloudioMessageFormat *CloudioMessageFormatFactory::messageFormat(string messageFormatName) {
        if (messageFormatName == "JSON") {
            if (json == nullptr) json = new JsonNlohmannMessageFormat("JSON");
            return json;
        } else if (messageFormatName == "CBOR") {
            if (cbor == nullptr) cbor = new JsonNlohmannMessageFormat("CBOR");
            return cbor;
        } else {
            return nullptr;
        }
    }
} // cloudio