//
// Created by lucas on 21/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_CLOUDIOOBJECT_H
#define CLOUDIO_ENDPOINT_CPP_CLOUDIOOBJECT_H

#include "CloudioAttribute.h"
#include "ICloudioAttributeContainer.h"
#include "ICloudioObjectContainer.h"

#include <string>
#include<queue>

namespace cloudio {

    class CloudioObject : public ICloudioAttributeContainer, public ICloudioObjectContainer {

    public:
        CloudioObject(const std::string &objectName);

        ~CloudioObject();

        std::string getConforms();

        std::vector<CloudioObject *> getObjects();

        CloudioObject *getObjectByName(const std::string &objectName);

        std::vector<CloudioAttribute *> getAttributes();

        CloudioAttribute *getAttributeByName(const std::string &attributeName);

        void addObject(CloudioObject *object);

        void addAttribute(CloudioAttribute *attribute);

        // INamedItem interface
        std::string getName();

        // ICloudioAttributeContainer & ICloudioObjectContainer interface
        void attributeHasChangedByEndpoint(CloudioAttribute *attribute);

        ICloudioObjectContainer *getParentObjectContainer();

        // ICloudioObjectContainer interface
        ICloudioNodeContainer *getParentNodeContainer();

        CloudioAttribute *findAttribute(std::queue<std::string> &location);

        void setParent(ICloudioObjectContainer *parent);


    private:
        std::string conforms;
        std::vector<CloudioObject *> objects;
        std::vector<CloudioAttribute *> attributes;
        std::string objectName;
        ICloudioObjectContainer *parent = nullptr;

    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_CLOUDIOOBJECT_H
