/*
 * ZephyrMqttTransportLayer.cpp
 *
 *  Created on: 20 April 2023
 *      Author: Lucas Bonvin
 */

#include "../include/ZephyrMqttTransportLayer.h"

#include "../include/CloudioAttributeConstrainException.h"
#include "../include/CloudioAttributeTypeException.h"

#include <hw_id.h>
#include <zephyr/random/rand32.h>
#include <zephyr/logging/log.h>

using namespace std;

namespace cloudio
{
    ZephyrMqttTransportLayer::ZephyrMqttTransportLayer()
    {
    }

    ZephyrMqttTransportLayer::~ZephyrMqttTransportLayer()
    {
    }

    ZephyrMqttTransportLayer &ZephyrMqttTransportLayer::getInstance()
    {
        static ZephyrMqttTransportLayer transportLayer;
        return transportLayer;
    }

    void ZephyrMqttTransportLayer::initTransportLayer(const string &uuid,
                                                      ICloudioEndpointConfiguration *const endpointConfiguration)
    {
        
        transportLayerProperties localProperties;
        try{
            localProperties = getTransportLayerProperties(endpointConfiguration);
        }
        catch(InvalidPropertyException &e){
            throw e;
        }
/*
        int err;

        mqtt_client_init(&this->client);

        err = this->brokerInit(localProperties);
        if (err)
        {
            LOG_ERR("Failed to initialize broker connection");
            //TODO return err;
        }

        /* MQTT client configuration */
        /*
        this->client.broker = &broker;
        this->client.evt_cb = this->mqttCallback;
        this->client.client_id.utf8 = (uint8_t *)client_id_get();
        this->client.client_id.size = strlen((char *)this->client.client_id.utf8);
        this->client.password = NULL;
        this->client.user_name = NULL;
        this->client.protocol_version = MQTT_VERSION_3_1_1;

        /* MQTT buffers configuration */
        /*
        this->client.rx_buf = rx_buffer;
        this->client.rx_buf_size = sizeof(rx_buffer);
        this->client.tx_buf = tx_buffer;
        this->client.tx_buf_size = sizeof(tx_buffer);

        /* MQTT transport configuration */
        /*
        struct mqtt_sec_config *tls_cfg = &(this->client.transport).tls.config;
        static sec_tag_t sec_tag_list[] = {CONFIG_MQTT_TLS_SEC_TAG};

        LOG_INF("TLS enabled with some test here");
        this->client.transport.type = MQTT_TRANSPORT_SECURE;

        tls_cfg->peer_verify = (localProperties.verifyHostname == true) ? TLS_PEER_VERIFY_REQUIRED : TLS_PEER_VERIFY_NONE ;
        tls_cfg->cipher_count = 0;
        tls_cfg->cipher_list = NULL;
        tls_cfg->sec_tag_count = ARRAY_SIZE(sec_tag_list);
        tls_cfg->sec_tag_list = sec_tag_list;
        tls_cfg->hostname = localProperties.hostname.c_str();

        tls_cfg->session_cache = IS_ENABLED(CONFIG_MQTT_TLS_SESSION_CACHING) ? TLS_SESSION_CACHE_ENABLED : TLS_SESSION_CACHE_DISABLED;

        //TODO return err;
        */
    }

    int ZephyrMqttTransportLayer::brokerInit(transportLayerProperties localProperties)
    {
/*
        int err;
        struct addrinfo *result;
        struct addrinfo *addr;
        struct addrinfo hints = {
            .ai_family = AF_INET,
            .ai_socktype = SOCK_STREAM};
        //TODO replace 
        err = getaddrinfo(localProperties.hostname.c_str(), NULL, &hints, &result);
        if (err)
        {
            LOG_ERR("getaddrinfo failed: %d", err);
            return -ECHILD;
        }

        addr = result;

        /* Look for address of the broker. *//*
        while (addr != NULL)
        {
            /* IPv4 Address. *//*
            if (addr->ai_addrlen == sizeof(struct sockaddr_in))
            {
                struct sockaddr_in *broker4 =
                    ((struct sockaddr_in *)&broker);
                char ipv4_addr[NET_IPV4_ADDR_LEN];

                broker4->sin_addr.s_addr =
                    ((struct sockaddr_in *)addr->ai_addr)
                        ->sin_addr.s_addr;
                broker4->sin_family = AF_INET;
                broker4->sin_port = htons(localProperties.port);

                inet_ntop(AF_INET, &broker4->sin_addr.s_addr,
                          ipv4_addr, sizeof(ipv4_addr));
                LOG_INF("IPv4 Address found %s", ipv4_addr);

                break;
            }
            else
            {
                LOG_ERR("ai_addrlen = %u should be %u or %u",
                        (unsigned int)addr->ai_addrlen,
                        (unsigned int)sizeof(struct sockaddr_in),
                        (unsigned int)sizeof(struct sockaddr_in6));
            }

            addr = addr->ai_next;
        }

        /* Free the address. *//*
        freeaddrinfo(result);

        return err;*/
    }

    const char *ZephyrMqttTransportLayer::client_id_get()
    {
        /*
        static char client_id[255]; // todo 255 was MAX(sizeof(CONFIG_MQTT_CLIENT_ID), CLIENT_ID_LEN)

        if (strlen(CONFIG_MQTT_CLIENT_ID) > 0)
        {
            snprintf(client_id, sizeof(client_id), "%s",
                     CONFIG_MQTT_CLIENT_ID);
            LOG_DBG("client_id = %s", (char *)client_id);

            return client_id;
        }

        char hw_id_buf[HW_ID_LEN] = {0};

        int err = hw_id_get(hw_id_buf, ARRAY_SIZE(hw_id_buf));

        if (!err)
        {
            snprintf(client_id, sizeof(client_id), "nrf-%s",
                     hw_id_buf);
            LOG_DBG("client_id = %s", (char *)client_id);

            return client_id;
        }

        LOG_ERR("failed to retrieve HW ID, err: %d", err);

        uint32_t id = sys_rand32_get();
        snprintf(client_id, sizeof(client_id), "%s-%010u", CONFIG_BOARD, id);

        LOG_DBG("client_id = %s", (char *)client_id);

        return client_id;
        */
    }

    void ZephyrMqttTransportLayer::connect()
    {
    }

    void ZephyrMqttTransportLayer::disconnect()
    {
    }

    void ZephyrMqttTransportLayer::publish(const string &topic,
                                           const string &payload, const int qos, const bool retained) const
    {
    }

    void ZephyrMqttTransportLayer::subscribe(const string &topic,
                                             const int qos) const
    {
    }

    bool ZephyrMqttTransportLayer::isOnline() const
    {
        return this->online;
    }

    void ZephyrMqttTransportLayer::setTransportLayerMessageListener(
        ICloudioTransportLayerMessageListener *)
    {
    }

    void ZephyrMqttTransportLayer::mqttCallback(struct mqtt_client *const c, const struct mqtt_evt *evt)
    {
    }
} /* namespace cloudio */
