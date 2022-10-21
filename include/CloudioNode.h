//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP__CLOUDIONODE_H
#define CLOUDIO_ENDPOINT_CPP__CLOUDIONODE_H

#include "CloudioObject.h"

namespace cloudio {

    class CloudioNode {

    public:

        CloudioNode(string nodeName);

        ~CloudioNode();

        list<CloudioObject *> getObjects();

        list<string> getInterfaces();

        void addObject(CloudioObject *object);

        string getName();


    private:
        list<CloudioObject *> objects;
        list<string> interfaces;
        string nodeName;
    };

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP__CLOUDIONODE_H
