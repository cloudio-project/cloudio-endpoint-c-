/*
 * ZephyrMqttTransportLayer.h
 *
 *  Created on: 20 April 2023
 *      Author: Lucas Bonvin
 */

#ifndef COMPONENTS_CLOUDIO_ENDPOINT_CPP_INCLUDE_ZEPHYRMQTTTRANSPORTLAYER_H_
#define COMPONENTS_CLOUDIO_ENDPOINT_CPP_INCLUDE_ZEPHYRMQTTTRANSPORTLAYER_H_

#include "ITransportLayer.h"
#include <zephyr/net/mqtt.h>
#include <zephyr/net/socket.h>

#include "../include/PropertiesHelper.h"

namespace cloudio
{

    class ZephyrMqttTransportLayer : public cloudio::ITransportLayer
    {
    public:
        virtual ~ZephyrMqttTransportLayer();

        static ZephyrMqttTransportLayer &getInstance();

        // ITransportLayer interface
        void initTransportLayer(const std::string &uuid,
                                ICloudioEndpointConfiguration *endpointConfiguration);

        void connect();

        void disconnect();

        void publish(const std::string &topic, const std::string &payload, int qos,
                     bool retained) const;

        void subscribe(const std::string &topic, int qos) const;

        bool isOnline() const;

        void setTransportLayerMessageListener(
            ICloudioTransportLayerMessageListener *);

    private:
        ZephyrMqttTransportLayer();

        int brokerInit(transportLayerProperties localProperties);
        const char* client_id_get();

        bool online = false;

        struct mqtt_client client;
        struct sockaddr_storage broker;

        uint8_t rx_buffer[128];
        uint8_t tx_buffer[128];
        char payload_buf[128];

        static void mqttCallback(struct mqtt_client *const c,
                                 const struct mqtt_evt *evt);
    };
} // cloudio
#endif /* COMPONENTS_CLOUDIO_ENDPOINT_CPP_INCLUDE_ZEPHYRMQTTTRANSPORTLAYER_H_ */
