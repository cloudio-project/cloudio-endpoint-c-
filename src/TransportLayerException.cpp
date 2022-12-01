//
// Created by lucas on 04/11/22.
//

#include "../include/TransportLayerException.h"

namespace cloudio {

    TransportLayerException::TransportLayerException(string msg) : message(msg) {
        this->message = message;
    }

    const char *TransportLayerException::what() {
        return message.c_str();
    }
} // cloudio