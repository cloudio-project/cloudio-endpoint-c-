//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP__CLOUDIOENDPOINT_H
#define CLOUDIO_ENDPOINT_CPP__CLOUDIOENDPOINT_H

#include "CloudioNode.h"

namespace cloudio {

    class CloudioEndpoint {

    public:
        string getVersion();

        list<CloudioNode *> getNodes();

        list<string> getSupportedFormats();

    private:
        string version = "v0.2";
        list<CloudioNode *> nodes;
        list<string> supportedFormats{"json"};

    };

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP__CLOUDIOENDPOINT_H
