//
// Created by lucas on 31/10/22.
//

#include "../include/InvalidPropertyException.h"

namespace cloudio {
    InvalidPropertyException::InvalidPropertyException(char *msg) : message(msg) {

    }

    char *InvalidPropertyException::what() {
        return message;
    }

}
