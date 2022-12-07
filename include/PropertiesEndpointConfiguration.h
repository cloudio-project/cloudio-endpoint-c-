//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_PROPERTIESENDPOINTCONFIGURATION_H
#define CLOUDIO_ENDPOINT_CPP_PROPERTIESENDPOINTCONFIGURATION_H

#include "ICloudioEndpointConfiguration.h"
#include <iostream>
#include "PropertiesParser.h"

namespace cloudio {

    class PropertiesEndpointConfiguration : public ICloudioEndpointConfiguration {
    public:
        PropertiesEndpointConfiguration(const std::string &propertiesFilePath);

        ~PropertiesEndpointConfiguration();

        // ICloudioEndpointConfiguration interface
        std::string getProperty(const std::string &key);

        std::string getProperty(const std::string &key, const std::string &defaultValue);

        bool containsKey(const std::string &key);

    private:
        cppproperties::Properties properties;
    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_PROPERTIESENDPOINTCONFIGURATION_H
