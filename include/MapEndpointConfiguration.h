/*
 * MapEndpointConfiguration.h
 *
 *  Created on: 7 Feb 2023
 *      Author: Lucas Bonvin
 */

#ifndef COMPONENTS_CLOUDIO_ENDPOINT_CPP_INCLUDE_MAPENDPOINTCONFIGURATION_H_
#define COMPONENTS_CLOUDIO_ENDPOINT_CPP_INCLUDE_MAPENDPOINTCONFIGURATION_H_

#include "ICloudioEndpointConfiguration.h"
#include <map>
#include <string>

namespace cloudio {

	class MapEndpointConfiguration: public ICloudioEndpointConfiguration {
	public:
		MapEndpointConfiguration();
		MapEndpointConfiguration(const std::map<std::string, std::string> parameterPropertiesMap);
		virtual ~MapEndpointConfiguration();

		void addPropertie(const std::string &key, const std::string& value);
		void addProperties(const std::map<std::string, std::string> parameterPropertiesMap);

        // ICloudioEndpointConfiguration interface
        std::string getProperty(const std::string &key);

        std::string getProperty(const std::string &key, const std::string &defaultValue);

        bool containsKey(const std::string &key);
	private:
        std::map<std::string, std::string> propertiesMap;
	};
} // cloudio
#endif /* COMPONENTS_CLOUDIO_ENDPOINT_CPP_INCLUDE_MAPENDPOINTCONFIGURATION_H_ */
