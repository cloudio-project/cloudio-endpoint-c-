//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_ICLOUDIOENDPOINTCONFIGURATION_H
#define CLOUDIO_ENDPOINT_CPP_ICLOUDIOENDPOINTCONFIGURATION_H

#include <string>

using namespace std;

namespace cloudio {
    class ICloudioEndpointConfiguration {
    public:
        virtual string getProperty(string key) = 0;

        virtual string getProperty(string key, string defaultValue) = 0;

        virtual bool containsKey(string key) = 0;
    };
} // cloudio
#endif //CLOUDIO_ENDPOINT_CPP_ICLOUDIOENDPOINTCONFIGURATION_H
