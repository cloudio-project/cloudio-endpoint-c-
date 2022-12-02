//
// Created by lucas on 20/10/22.
//

#include "../include/CloudioEndpoint.h"
#include "../include/PahoMqttCppTransportLayer.h"
#include "../include/PropertiesEndpointConfiguration.h"
#include "../include/JsonNlohmannMessageFormat.h"
#include "../include/CloudioEndpointPropertyConstants.h"
#include "../include/TopicUuidHelper.h"

namespace cloudio {

    CloudioEndpoint::CloudioEndpoint(string uuidOrAppName, ICloudioMessageFormat *cloudioMessageFormat,
                                     ITransportLayer *transportLayer,
                                     ICloudioEndpointConfiguration *endpointConfiguration) {
        try {

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

            if (endpointConfiguration == nullptr) {
                this->endpointConfiguration = new PropertiesEndpointConfiguration(
                        "/etc/cloud.io/" + uuidOrAppName + ".properties");
            } else {
                this->endpointConfiguration = endpointConfiguration;
            }

            this->uuid = this->endpointConfiguration->getProperty(UUID_PROPERTY, uuidOrAppName);

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

    list<CloudioNode *> CloudioEndpoint::getNodes() {
        return this->nodes;
    }

    CloudioNode *CloudioEndpoint::getNodeByName(string nodeName) {
        for (auto &nodeIt: this->nodes) {
            if (nodeIt->getName() == nodeName) {
                return nodeIt;
            }
        }
        return nullptr;
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
        this->transportLayer->publish("@nodeAdded/" + this->uuid + "/" + node->getName(),
                                      this->messageFormat->serializeNode(node), 1, false);
    }

    void CloudioEndpoint::set(list<string> topics, string payload) {

        if (!topics.empty() && uuid == topics.front()) {
            topics.pop_front(); // pop the uuid
            // Get the node with the name according to the topic.
            CloudioNode *node = this->getNodeByName(topics.front());
            if (node != nullptr) {
                topics.pop_front(); // pop the node name

                // Get the attribute reference.
                CloudioAttribute *attribute = node->findAttribute(topics);
                if (attribute != nullptr) {
                    cout<<"Got the attribute!!"<<endl;


                    // Deserialize the message into the attribute.
                    string correlationID = messageFormat->deserializeSetAttribute(payload, attribute);

                    if (correlationID != "null")
                    {

                    }
                    /*
                    byte[]
                    dataDidSet = messageFormat.serializeDidSetAttribute(attribute, correlationID);

                    boolean messageSend = false;
                    if (isOnline()) {
                        try {
                            mqtt.publish("@didSet/" + attribute.getUuid().toString(), dataDidSet, 1, true);
                            messageSend = true;
                        } catch (MqttException exception) {
                            log.error("Exception :" + exception.getMessage());
                            exception.printStackTrace();
                        }
                    }

                    // If the message could not be send for any reason, add the message to the pending updates persistence if
                    // available.
                    if (!messageSend && persistence) {
                        try {
                            CloudioPersistence.Message
                            message
                                    = new CloudioPersistence.Message("@didSet/" + attribute.getUuid().toString(),
                                                                     dataDidSet);

                            cloudioPersistence.storeMessage(PERSISTENCE_MQTT_UPDATE, updatePersistenceLimit, message);
                        } catch (Exception exception) {
                            log.error("Exception :" + exception.getMessage());
                            exception.printStackTrace();
                        }
                    }*/


                } else {
                    cout<<("Attribute at \"" + topics.front() + "\" not found!");
                }
            } else {
                cout<<("Node \"" + topics.front() + "\" not found!");
            }
        } else {
            cout<<("Invalid topic: " + topics.front());
        }
        cout<<"end of set"<<endl;
    }

    void CloudioEndpoint::attributeHasChangedByEndpoint(CloudioAttribute *attribute) {

        string topicUUID = getAttributeTopic(attribute);
        this->transportLayer->publish("@update/" + topicUUID, this->messageFormat->serializeAttribute(attribute), 1,
                                      true);
    }

    void CloudioEndpoint::messageArrived(string topic, string payload) {
        cout << topic << endl;
        cout << payload << endl;
        list<string> topics = split(topic, "/");

        if (topics.front() == "@set") {
            topics.pop_front(); // pop the @set
            set(topics, payload);
        }
    }

} // cloudio