//
// Created by lucas on 20/10/22.
//

#include "../include/CloudioEndpoint.h"
#include "../include/PahoMqttCppTransportLayer.h"
#include "../include/PropertiesEndpointConfiguration.h"
#include "../include/JsonNlohmannMessageFormat.h"
#include "../include/InvalidPropertyException.h"
#include "../include/CloudioEndpointPropertyConstants.h"

namespace cloudio {

    CloudioEndpoint::CloudioEndpoint(string uuidOrAppName, ICloudioMessageFormat *cloudioMessageFormat,
                                     ITransportLayer *transportLayer) {
        if (cloudioMessageFormat == nullptr) {
            this->messageFormat = new JsonNlohmannMessageFormat();
        } else {
            this->messageFormat = cloudioMessageFormat;
        }

        if (transportLayer == nullptr) {
            this->transportLayer = new PahoMqttCppTransportLayer();
        } else {
            this->transportLayer = transportLayer;
        }


        ICloudioEndpointConfiguration *endpointConfiguration = new PropertiesEndpointConfiguration(
                "/etc/cloud.io/" + uuidOrAppName + ".properties");

        this->uuid = endpointConfiguration->getProperty(UUID_PROPERTY, uuidOrAppName);

        this->transportLayer->initTransportLayer(uuid, endpointConfiguration);
        this->transportLayer->connect();

        string testPayload =
                "{\"constraint\": \"Measure\",\"type\": \"Number\",\"timestamp\": " + to_string(time(nullptr)) +
                ",\"value\": 40.0}";

        this->transportLayer->publish("@update/" + uuid + "/myNode/myObject/myMeasure", testPayload, 1, false);

        this->transportLayer->disconnect();


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