/*
 * PropertiesHelper.cpp
 *
 *  Created on: 13 Feb 2023
 *      Author: Lucas Bonvin
 */

#include "PropertiesHelper.h"
#include "CloudioEndpointPropertyConstants.h"

using namespace std;

namespace cloudio {

	transportLayerProperties getTransportLayerProperties(
			ICloudioEndpointConfiguration *endpointConfiguration) {
		// MQTT parameters
		transportLayerProperties toReturn = { };

		try {
			toReturn.connectTimeout = stoi(
					endpointConfiguration->getProperty(
							MQTT_CONNECTION_TIMEOUT_PROPERTY,
							MQTT_CONNECTION_TIMEOUT_DEFAULT));
		} catch (exception &e) {
			throw InvalidPropertyException(
					"Invalid connect timeout (" + MQTT_CONNECTION_TIMEOUT_PROPERTY
							+ "), must be a valid integer number, " + e.what());
		}

		try {
			toReturn.retryInterval = stoi(
					endpointConfiguration->getProperty(MQTT_CONNECT_RETRY_PROPERTY,
							MQTT_CONNECT_RETRY_DEFAULT));
		} catch (exception &e) {
			throw InvalidPropertyException(
					"Invalid retry interval (" + MQTT_CONNECT_RETRY_PROPERTY
							+ "), must be a valid integer number, " + e.what());
		}

		try {
			toReturn.keepAliveInterval = stoi(
					endpointConfiguration->getProperty(
							MQTT_KEEPALIVE_INTERVAL_PROPERTY,
							MQTT_KEEPALIVE_INTERVAL_DEFAULT));
		} catch (exception &e) {
			throw InvalidPropertyException(
					"Invalid keep alive interval ("
							+ MQTT_KEEPALIVE_INTERVAL_PROPERTY
							+ "), must be a valid integer number, " + e.what());
		}

		try {
			toReturn.maxInflight = stoi(
					endpointConfiguration->getProperty(MQTT_MAXINFLIGHT_PROPERTY,
							MQTT_MAXINFLIGHT_DEFAULT));
		} catch (exception &e) {
			throw InvalidPropertyException(
					"Invalid max in flight messages (" + MQTT_MAXINFLIGHT_PROPERTY
							+ "), must be a valid integer number, " + e.what());
		}

		// Certificates parameters, files not necessary for ESP32
#ifndef ESP_PLATFORM
		if (endpointConfiguration->containsKey(ENDPOINT_IDENTITY_FILE_PROPERTY)) {
			toReturn.endpointIdentityFilePath = endpointConfiguration->getProperty(
					ENDPOINT_IDENTITY_FILE_PROPERTY);
		} else {
			throw InvalidPropertyException("No endpoint certificate path given");
		}

		if (endpointConfiguration->containsKey(CERT_AUTHORITY_FILE_PROPERTY)) {
			toReturn.authorityFilePath = endpointConfiguration->getProperty(
					CERT_AUTHORITY_FILE_PROPERTY);
		} else {
			throw InvalidPropertyException("No authority path given");
		}

		if (endpointConfiguration->containsKey(ENDPOINT_IDENTITY_KEY_PROPERTY)) {
			toReturn.identityKeyPath = endpointConfiguration->getProperty(
					ENDPOINT_IDENTITY_KEY_PROPERTY);
		} else {
			throw InvalidPropertyException("No endpoint private key path given");
		}
#endif


		if (endpointConfiguration->containsKey(MQTT_HOST_URI_PROPERTY)) {
			toReturn.hostURI = endpointConfiguration->getProperty(
					MQTT_HOST_URI_PROPERTY);
		} else {
			throw InvalidPropertyException("No hoste URI given");
		}

		string verifyHostnameStr = endpointConfiguration->getProperty(
				SSL_VERIFY_HOSTNAME_PROPERTY, SSL_VERIFY_HOSTNAME_DEFAULT);
		toReturn.verifyHostname = verifyHostnameStr.compare("true") == 0;

		return toReturn;
	}

} /* namespace cloudio */
