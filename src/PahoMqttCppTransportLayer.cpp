//
// Created by lucas on 21/10/22.
//
#ifdef __unix__
#include "../include/PahoMqttCppTransportLayer.h"
#include "../include/CloudioEndpointPropertyConstants.h"
#include "../include/PropertiesHelper.h"
using namespace std;

namespace cloudio {
    PahoMqttCppTransportLayer::PahoMqttCppTransportLayer() {

    }

    PahoMqttCppTransportLayer::~PahoMqttCppTransportLayer() {
        delete this->mqttClient;
    }

    void
    PahoMqttCppTransportLayer::initTransportLayer(const string &uuid,
                                                  ICloudioEndpointConfiguration *const endpointConfiguration) {
        transportLayerProperties localProperties;
        try{
            localProperties = getTransportLayerProperties(endpointConfiguration);
        }
        catch(InvalidPropertyException &e){
            throw e;
        }

        // Construct a client using the Ip and Id
        mqttClient = new mqtt::async_client(localProperties.hostURI, uuid);

        mqttClient->set_callback(*this);

        mqtt::ssl_options sslopts = mqtt::ssl_options_builder()
                .trust_store(localProperties.authorityFilePath)
                .key_store(localProperties.endpointIdentityFilePath)
                .private_key(localProperties.identityKeyPath)
                .ssl_version(3)
                .verify(localProperties.verifyHostname)
                .finalize();

        mqtt::message willmsg = mqtt::message("@offline/" + uuid, "", mqtt::GRANTED_QOS_1, true);

        this->connopts = mqtt::connect_options_builder()
                .connect_timeout(chrono::seconds(localProperties.connectTimeout))
                .keep_alive_interval(chrono::seconds(localProperties.keepAliveInterval))
                .max_inflight(localProperties.maxInflight)
                .will(move(willmsg))
                .ssl(move(sslopts))
                .finalize();
    }

    void PahoMqttCppTransportLayer::connect() {
        // Use the connect method of the client to establish a connection to the broker.
        try {
            mqtt::token_ptr conntok = mqttClient->connect(connopts);
            conntok->wait();
        }
        catch (mqtt::security_exception &e) {
            throw TransportLayerException(
                    "Error while connecting to mqtt broker, mqtt::security_exception : " + string(e.what()));
        }
        catch (mqtt::exception &e) {
            throw TransportLayerException(
                    "Error while connecting to mqtt broker, mqtt::exception : " + string(e.what()));
        }
    }

    void PahoMqttCppTransportLayer::disconnect() {
        mqttClient->disconnect()->wait();
    }

    void
    PahoMqttCppTransportLayer::publish(const string &topic, const string &payload, const int qos,
                                       const bool retained) const {
        bool messageSend = false;
        mqtt::message_ptr timeLeftMessagePointer = mqtt::make_message(
                topic,
                payload,
                qos,
                retained);
        if (this->isOnline()) {
            try {
                mqtt::delivery_token_ptr publishok = mqttClient->publish(timeLeftMessagePointer);
                messageSend = true;
            }
            catch (mqtt::exception &e) {
                throw TransportLayerException(
                        "Error while sending " + topic + " message to mqtt broker, mqtt::exception : " +
                        string(e.what()));
            }
        }
        if (!messageSend) {
            throw TransportLayerException("Error " + topic + " message not sent");
        }
    }

    void PahoMqttCppTransportLayer::subscribe(const string &topic, const int qos) const {
        this->mqttClient->subscribe(topic, qos);
    }

    bool PahoMqttCppTransportLayer::isOnline() const {
        return mqttClient->is_connected();
    }

    void PahoMqttCppTransportLayer::setTransportLayerMessageListener(
            ICloudioTransportLayerMessageListener *cloudioTransportLayerMessageListener) {
        this->cloudioTransportLayerMessageListener = cloudioTransportLayerMessageListener;
    }

    void PahoMqttCppTransportLayer::connected(const string &cause) {
    }

    void PahoMqttCppTransportLayer::connection_lost(const string &cause) {
    }

    void PahoMqttCppTransportLayer::message_arrived(mqtt::const_message_ptr msg) {
        this->cloudioTransportLayerMessageListener->messageArrived(msg->get_topic(), msg->get_payload_str());
    }

    void PahoMqttCppTransportLayer::delivery_complete(mqtt::delivery_token_ptr tok) {
    }
} // cloudio
#endif//__unix__
