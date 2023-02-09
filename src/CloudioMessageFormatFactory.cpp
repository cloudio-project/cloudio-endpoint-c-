//
// Created by lucas on 05/12/22.
//

#include "../include/CloudioMessageFormatFactory.h"
#include "../include/JsonNlohmannMessageFormat.h"
#include "../include/CJsonMessageFormat.h"

using namespace std;

namespace cloudio {

    static ICloudioMessageFormat *json;
    static ICloudioMessageFormat *cbor;

    ICloudioMessageFormat *CloudioMessageFormatFactory::messageFormat(const char messageFormatId) {
        if (messageFormatId == '{') {
#ifdef __unix__
            if (json == nullptr) json = new JsonNlohmannMessageFormat("JSON");
#elif ESP_PLATFORM
            if (json == nullptr) json = new CJsonMessageFormat();
#else// by default, consider we have an OS
            if (json == nullptr) json = new JsonNlohmannMessageFormat("JSON");
#endif//__unix ESP_PLATFORM
            return json;
        } else if ((messageFormatId & 0b11100000) == 0b10100000) {
#ifdef __unix__
            if (cbor == nullptr) cbor = new JsonNlohmannMessageFormat("CBOR");
#elif ESP_PLATFORM
            cbor = nullptr; // for now CBOR is not yet supported on ESP platform
#else// by default, consider we have an OS
            if (cbor == nullptr) json = new JsonNlohmannMessageFormat("CBOR");
#endif//__unix ESP_PLATFORM
            return cbor;
        } else {
            return nullptr;
        }
    }

    ICloudioMessageFormat *CloudioMessageFormatFactory::messageFormat(const string &messageFormatName) {
        if (messageFormatName == "JSON") {
#ifdef __unix__
            if (json == nullptr) json = new JsonNlohmannMessageFormat("JSON");
#elif ESP_PLATFORM
            if (json == nullptr) json = new CJsonMessageFormat();
#else// by default, consider we have an OS
            if (json == nullptr) json = new JsonNlohmannMessageFormat("JSON");
#endif//__unix__  ESP_PLATFORM
            return json;
        } else if (messageFormatName == "CBOR") {
#ifdef __unix__
            if (cbor == nullptr) cbor = new JsonNlohmannMessageFormat("CBOR");
#elif ESP_PLATFORM
            cbor = nullptr; // for now CBOR is not yet supported on ESP platform
#else// by default, consider we have an OS
            if (cbor == nullptr) cbor = new JsonNlohmannMessageFormat("CBOR");
#endif//__unix ESP_PLATFORM
            return cbor;
        } else {
            return nullptr;
        }
    }
} // cloudio
