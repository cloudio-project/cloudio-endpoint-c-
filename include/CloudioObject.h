//
// Created by lucas on 21/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_CLOUDIOOBJECT_H
#define CLOUDIO_ENDPOINT_CPP_CLOUDIOOBJECT_H

#include "CloudioAttribute.h"
#include "ICloudioAttributeContainer.h"
#include "ICloudioObjectContainer.h"

#include <string>
#include<list>

using namespace std;

namespace cloudio {

    class CloudioObject : public ICloudioAttributeContainer, public ICloudioObjectContainer {

    public:
        CloudioObject(string objectName);

        ~CloudioObject();

        string getConforms();

        list<CloudioObject *> getObjects();

        CloudioObject * getObjectByName(string objectName);

        list<CloudioAttribute *> getAttributes();

        CloudioAttribute * getAttributeByName(string attributeName);

        void addObject(CloudioObject *object);

        void addAttribute(CloudioAttribute *attribute);

        string getName();

        void attributeHasChangedByEndpoint(CloudioAttribute *attribute);

        ICloudioObjectContainer *getParentObjectContainer();

        ICloudioNodeContainer *getParentNodeContainer();

        CloudioAttribute* findAttribute(list<string>& location);

        void setParent(ICloudioObjectContainer *parent);

    private:
        string conforms;
        list<CloudioObject *> objects;
        list<CloudioAttribute *> attributes;
        string objectName;
        ICloudioObjectContainer *parent = nullptr;


    };

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_CLOUDIOOBJECT_H
