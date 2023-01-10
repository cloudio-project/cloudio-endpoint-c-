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

        const std::vector<CloudioObject *> &getObjects();

        CloudioObject *getObjectByName(const std::string &objectName);

        const std::vector<std::string> &getInterfaces();

        void addObject(CloudioObject *object);

        void setParent(ICloudioNodeContainer *parent);

        // INamedItem interface
        const std::string &getName() const;

        // ICloudioObjectContainer interface
        void attributeHasChangedByEndpoint(CloudioAttribute &attribute);

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
