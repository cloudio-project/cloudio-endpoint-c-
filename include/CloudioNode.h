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

        CloudioObject *getObjectByName(string objectName);

        list<string> getInterfaces();

        void addObject(CloudioObject *object);

        void setParent(ICloudioNodeContainer *parent);

        // INamedItem interface
        string getName();

        // ICloudioObjectContainer interface
        void attributeHasChangedByEndpoint(CloudioAttribute *attribute);

        ICloudioObjectContainer *getParentObjectContainer();

        ICloudioNodeContainer *getParentNodeContainer();

        CloudioAttribute *findAttribute(list<string> &location);


    private:
        list<CloudioObject *> objects;
        list<string> interfaces;
        string nodeName;
        ICloudioNodeContainer *parent = nullptr;
    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP__CLOUDIONODE_H
