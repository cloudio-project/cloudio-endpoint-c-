//
// Created by lucas on 20/10/22.
//

#include "../include/CloudioEndpoint.h"
#include "../include/PahoMqttCppTransportLayer.h"
#include "../include/PropertiesEndpointConfiguration.h"
#include "../include/JsonNlohmannMessageFormat.h"
#include "../include/InvalidPropertyException.h"
#include "../include/CloudioEndpointPropertyConstants.h"
#include "../include/TopicUuidHelper.h"

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

    string CloudioEndpoint::getName() {
        return this->uuid;
    }

    void CloudioEndpoint::addNode(CloudioNode *node) {
        node->setParent(this);
        this->nodes.push_front(node);
    }

    void CloudioEndpoint::attributeHasChangedByEndpoint(CloudioAttribute *attribute) {

        string topicUUID = getAttributeTopic(attribute);
        this->transportLayer->publish("@update/" + topicUUID, this->messageFormat->serializeAttribute(attribute), 1,
                                      true);
    }

} // cloudio