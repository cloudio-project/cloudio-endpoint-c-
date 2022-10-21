//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP__CLOUDIOENDPOINT_H
#define CLOUDIO_ENDPOINT_CPP__CLOUDIOENDPOINT_H

#include "CloudioNode.h"

namespace cloudio {

    class CloudioEndpoint {

    public:
        CloudioEndpoint();

        ~CloudioEndpoint();

        string getVersion();

        list<CloudioNode *> getNodes();

        list<string> getSupportedFormats();

        void addNode(CloudioNode *node);

    private:
        string version = "v0.2";
        list<CloudioNode *> nodes;
        list<string> supportedFormats{"JSON"};

    };

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP__CLOUDIOENDPOINT_H
