//
// Created by lucas on 21/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_CLOUDIOOBJECT_H
#define CLOUDIO_ENDPOINT_CPP_CLOUDIOOBJECT_H

#include "CloudioAttribute.h"

#include <string>
#include<list>

using namespace std;

namespace cloudio {

    class CloudioObject {

    public:
        CloudioObject(string objectName);

        ~CloudioObject();

        string getConforms();

        list<CloudioObject *> getObjects();

        list<CloudioAttribute *> getAttributes();

        void addObject(CloudioObject *object);

        void addAttribute(CloudioAttribute *attribute);

        string getName();

    private:
        string conforms;
        list<CloudioObject *> objects;
        list<CloudioAttribute *> attributes;
        string objectName;


    };

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_CLOUDIOOBJECT_H
