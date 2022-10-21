//
// Created by lucas on 20/10/22.
//

#include "../include/CloudioEndpoint.h"

namespace cloudio {
    string CloudioEndpoint::getVersion() {
        return this->version;
    }

    list<CloudioNode *> CloudioEndpoint::getNodes() {
        return this->nodes;
    }

    list<string> CloudioEndpoint::getSupportedFormats() {
        return this->supportedFormats;
    }
} // cloudio