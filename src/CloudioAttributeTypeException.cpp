//
// Created by lucas on 06/12/22.
//

#include "../include/CloudioAttributeTypeException.h"

using namespace std;

namespace cloudio {

    CloudioAttributeTypeException::CloudioAttributeTypeException(const string &msg) : message(msg) {

    }

    const char *CloudioAttributeTypeException::what() {
        return message.c_str();
    }
} // cloudio