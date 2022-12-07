//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP__CLOUDIONODE_H
#define CLOUDIO_ENDPOINT_CPP__CLOUDIONODE_H

#include "CloudioObject.h"
#include "ICloudioNodeContainer.h"
#include "ICloudioObjectContainer.h"
#include <queue>

namespace cloudio {

    class CloudioNode : public ICloudioObjectContainer {

    public:

        CloudioNode(std::string nodeName);

        ~CloudioNode();

        std::vector<CloudioObject *> getObjects();

        CloudioObject *getObjectByName(std::string objectName);

        std::vector<std::string> getInterfaces();

        void addObject(CloudioObject *object);

        void setParent(ICloudioNodeContainer *parent);

        // INamedItem interface
        std::string getName();

        // ICloudioObjectContainer interface
        void attributeHasChangedByEndpoint(CloudioAttribute *attribute);

        ICloudioObjectContainer *getParentObjectContainer();

        ICloudioNodeContainer *getParentNodeContainer();

        CloudioAttribute *findAttribute(std::queue<std::string> &location);


    private:
        std::vector<CloudioObject *> objects;
        std::vector<std::string> interfaces;
        std::string nodeName;
        ICloudioNodeContainer *parent = nullptr;
    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP__CLOUDIONODE_H
