//
// Created by lucas on 06/12/22.
//
#include "../include/CloudioAttributeType.h"

namespace cloudio {
    const char *CloudioAttributeTypeToString(CloudioAttributeType constraint) {
        switch (constraint) {
            case CloudioAttributeType::Invalid:
                return "Invalid";
            case CloudioAttributeType::Boolean:
                return "Boolean";
            case CloudioAttributeType::Integer:
                return "Integer";
            case CloudioAttributeType::Number:
                return "Number";
            case CloudioAttributeType::String:
                return "String";
            default:
                return "Invalid";
        }
    }
} // cloudio