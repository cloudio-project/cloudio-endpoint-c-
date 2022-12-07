//
// Created by lucas on 21/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_ITRANSPORTLAYER_H
#define CLOUDIO_ENDPOINT_CPP_ITRANSPORTLAYER_H

#include "ICloudioEndpointConfiguration.h"
#include "TransportLayerException.h"
#include "ICloudioTransportLayerMessageListener.h"

namespace cloudio {

    class ITransportLayer {
    public:
        virtual void initTransportLayer(const std::string &uuid, ICloudioEndpointConfiguration *endpointConfiguration) = 0;

        virtual void connect() = 0;

        virtual void disconnect() = 0;

        virtual void publish(const std::string &topic, const std::string &payload, int qos, bool retained) = 0;

        virtual void subscribe(const std::string &topic, int qos) = 0;

        virtual bool isOnline() = 0;

        virtual void setTransportLayerMessageListener(ICloudioTransportLayerMessageListener *) = 0;

    protected:
        ICloudioTransportLayerMessageListener *cloudioTransportLayerMessageListener;

    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_ITRANSPORTLAYER_H
