/*
 * MapEndpointConfiguration.cpp
 *
 *  Created on: 7 Feb 2023
 *      Author: Lucas Bonvin
 */

#include "../include/MapEndpointConfiguration.h"

using namespace std;

namespace cloudio {
    MapEndpointConfiguration::MapEndpointConfiguration() {
    }

    MapEndpointConfiguration::MapEndpointConfiguration(
            map <string, string> parameterPropertiesMap) {
        this->propertiesMap.insert(parameterPropertiesMap.begin(),
                                   parameterPropertiesMap.end());
    }

    MapEndpointConfiguration::~MapEndpointConfiguration() {
    }

    void MapEndpointConfiguration::addPropertie(const string &key,
                                                const string &value) {
        this->propertiesMap[key] = value;
    }

    void MapEndpointConfiguration::addProperties(
            map <string, string> parameterPropertiesMap) {
        this->propertiesMap.insert(parameterPropertiesMap.begin(),
                                   parameterPropertiesMap.end());
    }

    // ICloudioEndpointConfiguration interface
    string MapEndpointConfiguration::MapEndpointConfiguration::getProperty(
            const string &key) {
        return this->getProperty(key, "");
    }

    string MapEndpointConfiguration::getProperty(const string &key,
                                                 const string &defaultValue) {
        if (this->containsKey(key)) {
            return this->propertiesMap[key];
        } else {
            return defaultValue;
        }
    }

    bool MapEndpointConfiguration::containsKey(const string &key) {
        if (this->propertiesMap.find(key) != this->propertiesMap.end()) {
            return true;
        } else {
            return false;
        }
    }

} // cloudio
