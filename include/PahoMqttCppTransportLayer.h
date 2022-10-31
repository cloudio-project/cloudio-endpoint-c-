//
// Created by lucas on 21/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_PAHOMQTTCPPTRANSPORTLAYER_H
#define CLOUDIO_ENDPOINT_CPP_PAHOMQTTCPPTRANSPORTLAYER_H

#include "ITransportLayer.h"

namespace cloudio {

    class PahoMqttCppTransportLayer : public ITransportLayer {
    public:
        PahoMqttCppTransportLayer();

        void initTransportLayer(string uuid, ICloudioEndpointConfiguration *endpointConfiguration);

        void connect();

        void disconnect();

        void publish(string topic, string payload, int qos, bool retained);

    };

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_PAHOMQTTCPPTRANSPORTLAYER_H
