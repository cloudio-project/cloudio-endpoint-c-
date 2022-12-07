//
// Created by lucas on 31/10/22.
//

#include "../include/InvalidPropertyException.h"

using namespace std;

namespace cloudio {
    InvalidPropertyException::InvalidPropertyException(const string &msg) : message(msg) {

    }

    const char *InvalidPropertyException::what() {
        return message.c_str();
    }
} // cloudio
