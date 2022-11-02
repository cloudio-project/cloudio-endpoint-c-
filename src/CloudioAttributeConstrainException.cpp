//
// Created by lucas on 02/11/22.
//

#include "../include/CloudioAttributeConstrainException.h"

namespace cloudio {

    CloudioAttributeConstrainException::CloudioAttributeConstrainException(char *msg) : message(msg) {

    }

    char *CloudioAttributeConstrainException::what() {
        return message;
    }
} // cloudio