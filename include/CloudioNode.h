//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP__CLOUDIONODE_H
#define CLOUDIO_ENDPOINT_CPP__CLOUDIONODE_H

#include "CloudioObject.h"
#include "ICloudioNodeContainer.h"
#include "ICloudioObjectContainer.h"

namespace cloudio {

    class CloudioNode : public ICloudioObjectContainer {

    public:

        CloudioNode(string nodeName);

        ~CloudioNode();

        list<CloudioObject *> getObjects();

        list<string> getInterfaces();

        void addObject(CloudioObject *object);

        string getName();

        void setParent(ICloudioNodeContainer *parent);

        void attributeHasChangedByEndpoint(CloudioAttribute *attribute);

        ICloudioObjectContainer *getParentObjectContainer();

        ICloudioNodeContainer *getParentNodeContainer();


    private:
        list<CloudioObject *> objects;
        list<string> interfaces;
        string nodeName;
        ICloudioNodeContainer *parent = nullptr;
    };

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP__CLOUDIONODE_H
