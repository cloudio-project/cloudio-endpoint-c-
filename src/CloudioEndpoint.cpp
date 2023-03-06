//
// Created by lucas on 20/10/22.
//

#include "../include/CloudioEndpoint.h"
#include "../include/PahoMqttCppTransportLayer.h"
#include "../include/ESP32MqttTransportLayer.h"
#include "../include/PropertiesEndpointConfiguration.h"
#include "../include/MapEndpointConfiguration.h"
#include "../include/JsonNlohmannMessageFormat.h"
#include "../include/CJsonMessageFormat.h"
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
#ifdef __unix__
                this->transportLayer = new PahoMqttCppTransportLayer();
#elif ESP_PLATFORM
                this->transportLayer = &ESP32MqttTransportLayer::getInstance();
#else // default value
                this->transportLayer = new PahoMqttCppTransportLayer();
#endif//__unix
            } else {
                this->transportLayer = transportLayer;
            }

            if (endpointConfiguration == nullptr) {
#ifdef __unix__
                this->endpointConfiguration = new PropertiesEndpointConfiguration(
                        "/etc/cloud.io/" + uuidOrAppName + ".properties");
#else
                this->endpointConfiguration = new MapEndpointConfiguration();
#endif//__unix

            } else {
                this->endpointConfiguration = endpointConfiguration;
            }

            this->uuid = this->endpointConfiguration->getProperty(UUID_PROPERTY, uuidOrAppName);

            if (cloudioMessageFormat == nullptr) {
                string messageFormatId = this->endpointConfiguration->getProperty(MESSAGE_FORMAT,
                                                                                  MESSAGE_FORMAT_DEFAULT);
#ifdef __unix__
                this->messageFormat = new JsonNlohmannMessageFormat(messageFormatId);
#elif ESP_PLATFORM
                this->messageFormat = new CJsonMessageFormat();
#else // default value
                this->messageFormat = new JsonNlohmannMessageFormat(messageFormatId);
#endif//__unix
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
        transaction = new Transaction();
    }

    CloudioEndpoint::~CloudioEndpoint() {

    }

    string CloudioEndpoint::getVersion() {
        return this->version;
    }

    const std::vector<CloudioNode *> &CloudioEndpoint::getNodes() {
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

    const std::string &CloudioEndpoint::getName() const {
        return this->uuid;
    }

    void CloudioEndpoint::addNode(CloudioNode *const node) {
        node->setParent(this);
        this->nodes.push_back(node);
        this->transportLayer->publish("@nodeAdded/" + this->uuid + "/" + node->getName(),
                                      this->messageFormat->serializeNode(node), 1, false);
    }

    bool CloudioEndpoint::isOnline() {
        return this->transportLayer->isOnline();
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

    void CloudioEndpoint::attributeHasChangedByEndpoint(CloudioAttribute &attribute) {

        if (this->inTransaction) {
            this->transaction->addAttribute(&attribute);
        } else {
            string topicUUID = getAttributeTopic(&attribute);
            this->transportLayer->publish("@update/" + topicUUID, this->messageFormat->serializeAttribute(&attribute),
                                          1,
                                          true);
        }
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


    void CloudioEndpoint::beginTransaction() {
        this->inTransaction = true;
    }

    void CloudioEndpoint::commitTransaction() {
        string data = messageFormat->serializeTransaction(this->transaction);
        bool messageSend = false;

        if (this->isOnline()) {
            this->transportLayer->publish("@transaction/" + this->uuid, data, 1, true);
            messageSend = true;
            transaction->clearAttributes();
        }

        if (!messageSend) {
            //pass, condition will be used when persistence will be implemented
        }

        this->inTransaction = false;
    }

    void CloudioEndpoint::rollbackTransaction() {
        this->transaction->clearAttributes();
    }
} // cloudio
