//
// Created by lucas on 21/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_ITRANSPORTLAYER_H
#define CLOUDIO_ENDPOINT_CPP_ITRANSPORTLAYER_H

#include "ICloudioEndpointConfiguration.h"
#include "TransportLayerException.h"

namespace cloudio {

    class ITransportLayer {
    public:
        virtual void initTransportLayer(string uuid, ICloudioEndpointConfiguration *endpointConfiguration) = 0;

        virtual void connect() = 0;

        virtual void disconnect() = 0;

        virtual void publish(string topic, string payload, int qos, bool retained) = 0;

    };

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_ITRANSPORTLAYER_H
