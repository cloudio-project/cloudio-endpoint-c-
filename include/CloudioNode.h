//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP__CLOUDIONODE_H
#define CLOUDIO_ENDPOINT_CPP__CLOUDIONODE_H

#include "CloudioObject.h"

namespace cloudio {

    class CloudioNode {

    public:
        list<CloudioObject *> getObjects();

        list<string> getInterfaces();


    private:
        list<CloudioObject *> objects;
        list<string> interfaces;
    };

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP__CLOUDIONODE_H
