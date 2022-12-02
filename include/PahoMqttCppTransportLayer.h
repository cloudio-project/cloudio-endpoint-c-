//
// Created by lucas on 21/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_PAHOMQTTCPPTRANSPORTLAYER_H
#define CLOUDIO_ENDPOINT_CPP_PAHOMQTTCPPTRANSPORTLAYER_H

#include "ITransportLayer.h"
#include <mqtt/client.h>


namespace cloudio {

    class PahoMqttCppTransportLayer : public ITransportLayer, public mqtt::callback {
    public:
        PahoMqttCppTransportLayer();

        ~PahoMqttCppTransportLayer();

        void initTransportLayer(string uuid, ICloudioEndpointConfiguration *endpointConfiguration);

        void connect();

        void disconnect();

        void publish(string topic, string payload, int qos, bool retained);

        void subscribe(string topic, int qos);

        bool isOnline();

        void setTransportLayerMessageListener(ICloudioTransportLayerMessageListener *);

        void connected(const string &cause);

        void connection_lost(const string &cause);

        void message_arrived(mqtt::const_message_ptr msg);

        void delivery_complete(mqtt::delivery_token_ptr tok);

    private:

        // Mqtt objects
        mqtt::async_client *mqttClient;
        mqtt::connect_options connopts;

    };

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_PAHOMQTTCPPTRANSPORTLAYER_H
