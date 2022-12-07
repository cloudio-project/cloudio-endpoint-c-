//
// Created by lucas on 20/10/22.
//

#include "../include/CloudioEndpoint.h"
#include "../include/PahoMqttCppTransportLayer.h"
#include "../include/PropertiesEndpointConfiguration.h"
#include "../include/JsonNlohmannMessageFormat.h"
#include "../include/CloudioEndpointPropertyConstants.h"
#include "../include/TopicUuidHelper.h"
#include "../include/CloudioMessageFormatFactory.h"

using namespace std;

namespace cloudio {

    CloudioEndpoint::CloudioEndpoint(const string &uuidOrAppName,
                                     ICloudioMessageFormat *const cloudioMessageFormat,
                                     ITransportLayer *const transportLayer,
                                     ICloudioEndpointConfiguration *const endpointConfiguration) {
        try {

            if (transportLayer == nullptr) {
                this->transportLayer = new PahoMqttCppTransportLayer();
            } else {
                this->transportLayer = transportLayer;
            }

            if (endpointConfiguration == nullptr) {
                this->endpointConfiguration = new PropertiesEndpointConfiguration(
                        "/etc/cloud.io/" + uuidOrAppName + ".properties");
            } else {
                this->endpointConfiguration = endpointConfiguration;
            }

            this->uuid = this->endpointConfiguration->getProperty(UUID_PROPERTY, uuidOrAppName);

            if (cloudioMessageFormat == nullptr) {
                string messageFormatId = this->endpointConfiguration->getProperty(MESSAGE_FORMAT,
                                                                                  MESSAGE_FORMAT_DEFAULT);
                this->messageFormat = new JsonNlohmannMessageFormat(messageFormatId);
            } else {
                this->messageFormat = cloudioMessageFormat;
            }

            this->transportLayer->initTransportLayer(uuid, this->endpointConfiguration);
            this->transportLayer->connect();

            this->transportLayer->publish("@online/" + this->uuid, this->messageFormat->serializeEndpoint(this), 1,
                                          true);
            this->transportLayer->setTransportLayerMessageListener(this);

            this->transportLayer->subscribe("@set/" + this->uuid + "/#", 1);

        } catch (TransportLayerException &e) {
            throw;
        }
    }

    CloudioEndpoint::~CloudioEndpoint() {

    }

    string CloudioEndpoint::getVersion() {
        return this->version;
    }

    vector<CloudioNode *> CloudioEndpoint::getNodes() {
        return this->nodes;
    }

    CloudioNode *CloudioEndpoint::getNodeByName(const string &nodeName) {
        for (auto &nodeIt: this->nodes) {
            if (nodeIt->getName() == nodeName) {
                return nodeIt;
            }
        }
        return nullptr;
    }

    vector <string> CloudioEndpoint::getSupportedFormats() {
        return this->supportedFormats;
    }

    string CloudioEndpoint::getName() {
        return this->uuid;
    }

    void CloudioEndpoint::addNode(CloudioNode *const node) {
        node->setParent(this);
        this->nodes.push_back(node);
        this->transportLayer->publish("@nodeAdded/" + this->uuid + "/" + node->getName(),
                                      this->messageFormat->serializeNode(node), 1, false);
    }

    void
    CloudioEndpoint::set(const string &topic, queue <string> location, ICloudioMessageFormat *const setMessageFormat,
                         const string &payload) {
        if (!location.empty() && uuid == location.front()) {
            location.pop(); // pop the uuid
            // Get the node with the name according to the topic.
            CloudioNode *node = this->getNodeByName(location.front());
            if (node != nullptr) {
                location.pop(); // pop the node name

                // Get the attribute reference.
                CloudioAttribute *attribute = node->findAttribute(location);
                if (attribute != nullptr) {

                    // Deserialize the message into the attribute using determined messageFormat
                    string correlationID = setMessageFormat->deserializeSetAttribute(payload, attribute);

                    // User endpoint messageFormat to serialize diSet attribute
                    string dataDidSet = this->messageFormat->serializeDidSetAttribute(attribute, correlationID);
                    string topicUUID = getAttributeTopic(attribute);
                    this->transportLayer->publish("@didSet/" + topicUUID, dataDidSet, 1, true);

                } else {
                    cout << ("Attribute from topic \"" + topic + "\" not found!") << endl;
                }
            } else {
                cout << ("Node from topic \"" + topic + "\" not found!") << endl;
            }
        } else {
            cout << ("Invalid topic: " + topic) << endl;
        }
    }

    void CloudioEndpoint::attributeHasChangedByEndpoint(CloudioAttribute *const attribute) {

        string topicUUID = getAttributeTopic(attribute);
        this->transportLayer->publish("@update/" + topicUUID, this->messageFormat->serializeAttribute(attribute), 1,
                                      true);
    }

    void CloudioEndpoint::messageArrived(const string &topic, const string &payload) {

        // First determine the message format (first byte identifies the message format).
        ICloudioMessageFormat *arrivedMessageFormat = CloudioMessageFormatFactory::messageFormat(payload[0]);
        if (arrivedMessageFormat == nullptr) {
            cout << "Message-format " << (char) payload[0] << " not supported!" << endl;
            return;
        }

        queue<string> location = split(topic, "/");

        if (location.front() == "@set") {
            location.pop(); // pop the @set
            set(topic, location, arrivedMessageFormat, payload);
        }
    }
} // cloudio