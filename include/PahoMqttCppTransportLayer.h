//
// Created by lucas on 21/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_PAHOMQTTCPPTRANSPORTLAYER_H
#define CLOUDIO_ENDPOINT_CPP_PAHOMQTTCPPTRANSPORTLAYER_H

#include "ITransportLayer.h"
#include <mqtt/client.h>


namespace cloudio {

    class PahoMqttCppTransportLayer : public ITransportLayer {
    public:
        PahoMqttCppTransportLayer();

        ~PahoMqttCppTransportLayer();

        void initTransportLayer(string uuid, ICloudioEndpointConfiguration *endpointConfiguration);

        void connect();

        void disconnect();

        void publish(string topic, string payload, int qos, bool retained);

        bool isOnline();

    private:

        // Mqtt objects
        mqtt::async_client *mqttClient;
        mqtt::connect_options connopts;

    };

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_PAHOMQTTCPPTRANSPORTLAYER_H
