//
// Created by lucas on 20/10/22.
//

#include "../include/JsonNlohmannMessageFormat.h"
namespace cloudio {

    JsonNlohmannMessageFormat::JsonNlohmannMessageFormat() {

    }

    JsonNlohmannMessageFormat::~JsonNlohmannMessageFormat() {

    }

    char *JsonNlohmannMessageFormat::serializeEndpoint(CloudioEndpoint endpoint) {
        return nullptr;
    }

    char *JsonNlohmannMessageFormat::serializeNode(CloudioNode node) {
        return nullptr;
    }

    char *JsonNlohmannMessageFormat::serializeAttribute(CloudioAttribute<int> attribute) {
        return nullptr;
    }

    char *JsonNlohmannMessageFormat::serializeAttribute(CloudioAttribute<double> attribute) {
        return nullptr;
    }

    char *JsonNlohmannMessageFormat::serializeAttribute(CloudioAttribute<bool> attribute) {
        return nullptr;
    }

    char *JsonNlohmannMessageFormat::serializeAttribute(CloudioAttribute<string> attribute) {
        return nullptr;
    }
}