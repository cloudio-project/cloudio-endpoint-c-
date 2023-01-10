//
// Created by lucas on 04/11/22.
//

#include "../include/TransportLayerException.h"

using namespace std;

namespace cloudio {

    TransportLayerException::TransportLayerException(const string &msg) : runtime_error(msg) {
        this->message = message;
    }
} // cloudio