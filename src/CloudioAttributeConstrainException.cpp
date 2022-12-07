//
// Created by lucas on 02/11/22.
//

#include "../include/CloudioAttributeConstrainException.h"

using namespace std;

namespace cloudio {

    CloudioAttributeConstrainException::CloudioAttributeConstrainException(const string &msg) : message(msg) {

    }

    const char *CloudioAttributeConstrainException::what() {
        return message.c_str();
    }
} // cloudio