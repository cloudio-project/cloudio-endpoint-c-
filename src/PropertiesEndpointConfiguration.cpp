//
// Created by lucas on 20/10/22.
//

#include "../include/PropertiesEndpointConfiguration.h"

namespace cloudio {
    PropertiesEndpointConfiguration::PropertiesEndpointConfiguration(const string propertiesFilePath) {
        this->properties = PropertiesParser::Read(propertiesFilePath);
    }

    PropertiesEndpointConfiguration::~PropertiesEndpointConfiguration() {

    }

    string PropertiesEndpointConfiguration::getProperty(string key) {
        return this->getProperty(key, "");
    }

    string PropertiesEndpointConfiguration::getProperty(string key, string defaultValue) {
        string outputProperty;
        try{
            outputProperty = properties.GetProperty(key);
        }
        catch(PropertyNotFoundException)
        {
            outputProperty = defaultValue;
        }
        return outputProperty;
    }

    bool PropertiesEndpointConfiguration::containsKey(string key) {
        try{
            properties.GetProperty(key);
            return true;
        }
        catch(PropertyNotFoundException)
        {
            return false;
        }
    }

} // cloudio