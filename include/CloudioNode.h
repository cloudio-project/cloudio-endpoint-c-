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

        CloudioNode(std::string nodeName);

        ~CloudioNode();

        std::list<CloudioObject *> getObjects();

        CloudioObject *getObjectByName(std::string objectName);

        std::list<std::string> getInterfaces();

        void addObject(CloudioObject *object);

        void setParent(ICloudioNodeContainer *parent);

        // INamedItem interface
        std::string getName();

        // ICloudioObjectContainer interface
        void attributeHasChangedByEndpoint(CloudioAttribute *attribute);

        ICloudioObjectContainer *getParentObjectContainer();

        ICloudioNodeContainer *getParentNodeContainer();

        CloudioAttribute *findAttribute(std::list<std::string> &location);


    private:
        std::list<CloudioObject *> objects;
        std::list<std::string> interfaces;
        std::string nodeName;
        ICloudioNodeContainer *parent = nullptr;
    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP__CLOUDIONODE_H
