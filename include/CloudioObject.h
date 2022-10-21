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
        string getConforms();

        list<CloudioObject *> getObjects();

        list<CloudioAttribute *> getAttributes();


    private:
        string conforms;
        list<CloudioObject *> objects;
        list<CloudioAttribute *> attributes;


    };

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_CLOUDIOOBJECT_H
