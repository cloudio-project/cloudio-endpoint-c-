//
// Created by lucas on 21/10/22.
//

#include "../include/PahoMqttCppTransportLayer.h"
#include "../include/CloudioEndpointPropertyConstants.h"

namespace cloudio {
    PahoMqttCppTransportLayer::PahoMqttCppTransportLayer() {

    }

    PahoMqttCppTransportLayer::~PahoMqttCppTransportLayer() {
        delete this->mqttClient;
    }

    void
    PahoMqttCppTransportLayer::initTransportLayer(string uuid, ICloudioEndpointConfiguration *endpointConfiguration) {

        // MQTT parameters
        int connectTimeout;
        int retryInterval;
        int keepAliveInterval;
        int maxInflight;

        try {
            connectTimeout = stoi(endpointConfiguration->getProperty(MQTT_CONNECTION_TIMEOUT_PROPERTY,
                                                                     MQTT_CONNECTION_TIMEOUT_DEFAULT));
        }
        catch (exception e) {
            throw InvalidPropertyException("Invalid connect timeout (" + MQTT_CONNECTION_TIMEOUT_PROPERTY +
                                           "), must be a valid integer number, " + e.what());
        }

        try {
            retryInterval = stoi(endpointConfiguration->getProperty(MQTT_CONNECT_RETRY_PROPERTY,
                                                                    MQTT_CONNECT_RETRY_DEFAULT));
        }
        catch (exception e) {
            throw InvalidPropertyException("Invalid retry interval (" + MQTT_CONNECT_RETRY_PROPERTY +
                                           "), must be a valid integer number, " + e.what());
        }

        try {
            keepAliveInterval = stoi(endpointConfiguration->getProperty(MQTT_KEEPALIVE_INTERVAL_PROPERTY,
                                                                        MQTT_KEEPALIVE_INTERVAL_DEFAULT));
        }
        catch (exception e) {
            throw InvalidPropertyException("Invalid keep alive interval (" + MQTT_KEEPALIVE_INTERVAL_PROPERTY +
                                           "), must be a valid integer number, " + e.what());
        }

        try {
            maxInflight = stoi(endpointConfiguration->getProperty(MQTT_MAXINFLIGHT_PROPERTY,
                                                                  MQTT_MAXINFLIGHT_DEFAULT));
        }
        catch (exception e) {
            throw InvalidPropertyException("Invalid max in flight messages (" + MQTT_MAXINFLIGHT_PROPERTY +
                                           "), must be a valid integer number, " + e.what());
        }


        // Certificates parameters
        string endpointIdentityFilePath;
        string authorityFilePath;
        string identityKeyPath;
        string hostURI;

        if (endpointConfiguration->containsKey(ENDPOINT_IDENTITY_FILE_PROPERTY)) {
            endpointIdentityFilePath = endpointConfiguration->getProperty(ENDPOINT_IDENTITY_FILE_PROPERTY);
        } else {
            throw InvalidPropertyException("No endpoint certificate path given");
        }

        if (endpointConfiguration->containsKey(CERT_AUTHORITY_FILE_PROPERTY)) {
            authorityFilePath = endpointConfiguration->getProperty(CERT_AUTHORITY_FILE_PROPERTY);
        } else {
            throw InvalidPropertyException("No authority path given");
        }

        if (endpointConfiguration->containsKey(ENDPOINT_IDENTITY_KEY_PROPERTY)) {
            identityKeyPath = endpointConfiguration->getProperty(ENDPOINT_IDENTITY_KEY_PROPERTY);
        } else {
            throw InvalidPropertyException("No endpoint private key path given");
        }

        if (endpointConfiguration->containsKey(MQTT_HOST_URI_PROPERTY)) {
            hostURI = endpointConfiguration->getProperty(MQTT_HOST_URI_PROPERTY);
        } else {
            throw InvalidPropertyException("No hoste URI given");
        }

        if (endpointConfiguration->containsKey(MQTT_HOST_URI_PROPERTY)) {
            hostURI = endpointConfiguration->getProperty(MQTT_HOST_URI_PROPERTY);
        } else {
            throw InvalidPropertyException("No hoste URI given");
        }


        string verifyHostnameStr = endpointConfiguration->getProperty(SSL_VERIFY_HOSTNAME_PROPERTY,
                                                                      SSL_VERIFY_HOSTNAME_DEFAULT);
        bool verifyHostname = verifyHostnameStr.compare("true") == 0;


        // Construct a client using the Ip and Id
        mqttClient = new mqtt::async_client(hostURI, uuid);

        mqttClient->set_callback(*this);

        mqtt::ssl_options sslopts = mqtt::ssl_options_builder()
                .trust_store(authorityFilePath)
                .key_store(endpointIdentityFilePath)
                .private_key(identityKeyPath)
                .ssl_version(3)
                .verify(verifyHostname)
                .finalize();

        mqtt::message willmsg = mqtt::message("@offline/" + uuid, "", mqtt::GRANTED_QOS_1, true);

        this->connopts = mqtt::connect_options_builder()
                .connect_timeout(chrono::seconds(connectTimeout))
                .keep_alive_interval(chrono::seconds(keepAliveInterval))
                .max_inflight(maxInflight)
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

    void PahoMqttCppTransportLayer::publish(string topic, string payload, int qos, bool retained) {
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

    void PahoMqttCppTransportLayer::subscribe(string topic, int qos) {
        this->mqttClient->subscribe(topic, qos);
    }

    bool PahoMqttCppTransportLayer::isOnline() {
        return mqttClient->is_connected();
    }

    void PahoMqttCppTransportLayer::setTransportLayerMessageListener(
            ICloudioTransportLayerMessageListener *cloudioTransportLayerMessageListener) {
        this->cloudioTransportLayerMessageListener = cloudioTransportLayerMessageListener;
    }

    void PahoMqttCppTransportLayer::connected(const string &cause) {
        //cout<<"connected"<<endl;
    }

    void PahoMqttCppTransportLayer::connection_lost(const string &cause) {
        //cout<<"connection_lost"<<endl;
    }

    void PahoMqttCppTransportLayer::message_arrived(mqtt::const_message_ptr msg) {
        //cout<<"message_arrived"<<endl;
        this->cloudioTransportLayerMessageListener->messageArrived(msg->get_topic(), msg->get_payload_str());
    }

    void PahoMqttCppTransportLayer::delivery_complete(mqtt::delivery_token_ptr tok) {
        //cout<<"delivery_complete"<<endl;
    }
} // cloudio