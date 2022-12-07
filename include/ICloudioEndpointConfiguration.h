//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_ICLOUDIOENDPOINTCONFIGURATION_H
#define CLOUDIO_ENDPOINT_CPP_ICLOUDIOENDPOINTCONFIGURATION_H

#include <string>
#include "InvalidPropertyException.h"

namespace cloudio {
    class ICloudioEndpointConfiguration {
    public:

        virtual ~ICloudioEndpointConfiguration() {}

        virtual std::string getProperty(const std::string &key) = 0;

        virtual std::string getProperty(const std::string &key, const std::string &defaultValue) = 0;

        virtual bool containsKey(const std::string &key) = 0;
    };
} // cloudio
#endif //CLOUDIO_ENDPOINT_CPP_ICLOUDIOENDPOINTCONFIGURATION_H
