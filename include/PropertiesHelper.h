/*
 * PropertiesHelper.h
 *
 *  Created on: 13 Feb 2023
 *      Author: Lucas Bonvin
 */

#ifndef COMPONENTS_CLOUDIO_ENDPOINT_CPP_INCLUDE_PROPERTIESHELPER_H_
#define COMPONENTS_CLOUDIO_ENDPOINT_CPP_INCLUDE_PROPERTIESHELPER_H_

#include <string>
#include "ICloudioEndpointConfiguration.h"

namespace cloudio {

	struct transportLayerProperties{
		int connectTimeout;
		int retryInterval;
		int keepAliveInterval;
		int maxInflight;
		std::string endpointIdentityFilePath;
		std::string authorityFilePath;
		std::string identityKeyPath;
		std::string hostURI;
		bool verifyHostname;
	};

	transportLayerProperties getTransportLayerProperties(ICloudioEndpointConfiguration *endpointConfiguration);

} /* namespace cloudio */

#endif /* COMPONENTS_CLOUDIO_ENDPOINT_CPP_INCLUDE_PROPERTIESHELPER_H_ */
