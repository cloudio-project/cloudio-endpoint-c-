//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_ICLOUDIOENDPOINTCONFIGURATION_H
#define CLOUDIO_ENDPOINT_CPP_ICLOUDIOENDPOINTCONFIGURATION_H

#include <string>
#include "InvalidPropertyException.h"

using namespace std;

namespace cloudio {
    class ICloudioEndpointConfiguration {
    public:

        virtual ~ICloudioEndpointConfiguration() {}

        virtual string getProperty(const string &key) = 0;

        virtual string getProperty(const string &key, const string &defaultValue) = 0;

        virtual bool containsKey(const string &key) = 0;
    };
} // cloudio
#endif //CLOUDIO_ENDPOINT_CPP_ICLOUDIOENDPOINTCONFIGURATION_H
