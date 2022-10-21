//
// Created by lucas on 20/10/22.
//

#include "../include/CloudioEndpoint.h"
#include "../include/PahoMqttCppTransportLayer.h"
#include "../include/PropertiesEndpointConfiguration.h"
#include "../include/JsonNlohmannMessageFormat.h"

namespace cloudio {

    CloudioEndpoint::CloudioEndpoint(string uuidOrAppName, ICloudioMessageFormat *cloudioMessageFormat,
                                     ITransportLayer *transportLayer) {
        if (cloudioMessageFormat == nullptr) {
            this->messageFormat = new JsonNlohmannMessageFormat();
        } else {
            this->messageFormat = cloudioMessageFormat;
        }

        if (transportLayer == nullptr) {
            transportLayer = new PahoMqttCppTransportLayer();
        } else {
            this->transportLayer = transportLayer;
        }

        PropertiesEndpointConfiguration endpointConfiguration = PropertiesEndpointConfiguration(
                "/etc/cloud.io/");

        this->uuid = endpointConfiguration.getProperty(UUID_PROPERTY, uuidOrAppName);

        // MQTT parameters
        int connectTimeout = stoi(endpointConfiguration.getProperty(MQTT_CONNECTION_TIMEOUT_PROPERTY,
                                                                   MQTT_CONNECTION_TIMEOUT_DEFAULT));
        int retryInterval = stoi(endpointConfiguration.getProperty(MQTT_CONNECT_RETRY_PROPERTY,
                                                                   MQTT_CONNECT_RETRY_DEFAULT));
        int keepAliveInterval = stoi(endpointConfiguration.getProperty(MQTT_KEEPALIVE_INTERVAL_PROPERTY,
                                                                       MQTT_KEEPALIVE_INTERVAL_DEFAULT));
    }

    CloudioEndpoint::~CloudioEndpoint() {

    }

    string CloudioEndpoint::getVersion() {
        return this->version;
    }

    list<CloudioNode *> CloudioEndpoint::getNodes() {
        return this->nodes;
    }

    list<string> CloudioEndpoint::getSupportedFormats() {
        return this->supportedFormats;
    }

    void CloudioEndpoint::addNode(CloudioNode *node) {
        this->nodes.push_front(node);
    }
} // cloudio