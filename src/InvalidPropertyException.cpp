//
// Created by lucas on 31/10/22.
//

#include "../include/InvalidPropertyException.h"

namespace cloudio {
    InvalidPropertyException::InvalidPropertyException(string msg) : message(msg) {

    }

    const char *InvalidPropertyException::what() {
        return message.c_str();
    }

}
