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

LOG_MODULE_DECLARE(mqtt_simple, CONFIG_MQTT_SIMPLE_LOG_LEVEL);

namespace cloudio
{
    ZephyrMqttTransportLayer::ZephyrMqttTransportLayer()
    {
        LOG_INF("Test log");
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
        try
        {
            localProperties = getTransportLayerProperties(endpointConfiguration);
        }
        catch (InvalidPropertyException &e)
        {
            throw e;
        }

        int err;

        mqtt_client_init(&this->client);

        err = this->brokerInit(localProperties);
        if (err)
        {
            LOG_ERR("Failed to initialize broker connection");
            // TODO return err;
        }

        /* MQTT client configuration */

        this->client.broker = &broker;
        this->client.evt_cb = this->mqttCallback;
        this->client.client_id.utf8 = (uint8_t *)client_id_get();
        this->client.client_id.size = strlen((char *)this->client.client_id.utf8);
        this->client.password = NULL;
        this->client.user_name = NULL;
        this->client.protocol_version = MQTT_VERSION_3_1_1;

        /* MQTT buffers configuration */

        this->client.rx_buf = rx_buffer;
        this->client.rx_buf_size = sizeof(rx_buffer);
        this->client.tx_buf = tx_buffer;
        this->client.tx_buf_size = sizeof(tx_buffer);

        /* MQTT transport configuration */

        struct mqtt_sec_config *tls_cfg = &(this->client.transport).tls.config;
        static sec_tag_t sec_tag_list[] = {CONFIG_MQTT_TLS_SEC_TAG};

        LOG_INF("TLS enabled with some test here");
        this->client.transport.type = MQTT_TRANSPORT_SECURE;

        tls_cfg->peer_verify = (localProperties.verifyHostname == true) ? TLS_PEER_VERIFY_REQUIRED : TLS_PEER_VERIFY_NONE;
        tls_cfg->cipher_count = 0;
        tls_cfg->cipher_list = NULL;
        tls_cfg->sec_tag_count = ARRAY_SIZE(sec_tag_list);
        tls_cfg->sec_tag_list = sec_tag_list;
        tls_cfg->hostname = localProperties.hostname.c_str();

        tls_cfg->session_cache = IS_ENABLED(CONFIG_MQTT_TLS_SESSION_CACHING) ? TLS_SESSION_CACHE_ENABLED : TLS_SESSION_CACHE_DISABLED;

        // TODO return err;
    }

    int ZephyrMqttTransportLayer::brokerInit(transportLayerProperties localProperties)
    {

        int err;
        struct addrinfo *result;
        struct addrinfo *addr;
        struct addrinfo hints = {
            .ai_family = AF_INET,
            .ai_socktype = SOCK_STREAM};
        err = getaddrinfo(localProperties.hostname.c_str(), NULL, &hints, &result);
        if (err)
        {
            // LOG_ERR("getaddrinfo failed: %d", err);
            return -ECHILD;
        }

        addr = result;

        /* Look for address of the broker. */
        while (addr != NULL)
        {
            /* IPv4 Address. */
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

        /* Free the address. */
        freeaddrinfo(result);

        return err;
    }

    const char *ZephyrMqttTransportLayer::client_id_get()
    {

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
    }

    int ZephyrMqttTransportLayer::fds_init(struct mqtt_client *c)
    {
        if (c->transport.type == MQTT_TRANSPORT_NON_SECURE)
        {
            fds.fd = c->transport.tcp.sock;
        }
        else
        {
#if defined(CONFIG_MQTT_LIB_TLS)
            fds.fd = c->transport.tls.sock;
#else
            return -ENOTSUP;
#endif
        }

        fds.events = POLLIN;

        return 0;
    }

    void ZephyrMqttTransportLayer::connect()
    {
        int err = 0;
        while (true)
        {
            if (connect_attempt++ > 0)
            {
                LOG_INF("Reconnecting in %d seconds...",
                        CONFIG_MQTT_RECONNECT_DELAY_S);
                k_sleep(K_SECONDS(CONFIG_MQTT_RECONNECT_DELAY_S));
            }
            err = mqtt_connect(&client);
            if (err != 0)
            {
                LOG_ERR("mqtt_connect %d", err);
            }
            else
            {
                break;
            }
        }

        err = fds_init(&client);
        if (err != 0)
        {
            LOG_ERR("fds_init: %d", err);
            this->online = true;
            return;
        }
        this->online = true;
    }

    void ZephyrMqttTransportLayer::disconnect()
    {
    }

    void ZephyrMqttTransportLayer::publish(const string &topic,
                                           const string &payload, const int qos, const bool retained) const
    {
        struct mqtt_publish_param param;

        param.message.topic.qos = qos;
        param.message.topic.topic.utf8 = (uint8_t *)topic.c_str();
        param.message.topic.topic.size = topic.length();
        param.message.payload.data = (uint8_t *)payload.c_str();
        param.message.payload.len = payload.length();
        param.message_id = sys_rand32_get();
        param.dup_flag = 0;
        param.retain_flag = 0;

        std::string test = "Publishing: ";

        LOG_INF("to topic: %s len: %u",
                CONFIG_MQTT_PUB_TOPIC,
                (unsigned int)strlen(CONFIG_MQTT_PUB_TOPIC));
        struct mqtt_client clientCpy = this->client; // TODO did something to avoid const pointer...
        int publishStatus = mqtt_publish(&clientCpy, &param);
    }

    void ZephyrMqttTransportLayer::subscribe(const string &topic,
                                             const int qos) const
    {
        struct mqtt_topic subscribe_topic = {
            .topic = {
                .utf8 = (uint8_t *)topic.c_str(),
                .size = strlen(topic.c_str())},
            .qos = qos};

        const struct mqtt_subscription_list subscription_list = {
            .list = &subscribe_topic,
            .list_count = 1,
            .message_id = 1234};

        LOG_INF("Subscribing to: %s len %u", CONFIG_MQTT_SUB_TOPIC,
                (unsigned int)strlen(CONFIG_MQTT_SUB_TOPIC));

        struct mqtt_client clientCpy = this->client; // TODO did something to avoid const pointer...
        mqtt_subscribe(&clientCpy, &subscription_list);
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
        int err;

        switch (evt->type)
        {
        case MQTT_EVT_CONNACK:
            break;

        case MQTT_EVT_DISCONNECT:
            break;

        case MQTT_EVT_PUBLISH:
            break;

        case MQTT_EVT_PUBACK:
            break;

        case MQTT_EVT_SUBACK:
            break;

        case MQTT_EVT_PINGRESP:
            break;

        default:
            break;
        }
    }
    void ZephyrMqttTransportLayer::mqttPoll(){
        int err = poll(&fds, 1, mqtt_keepalive_time_left(&client));
		if (err < 0) {
			LOG_ERR("poll: %d", errno);
			return;
		}

		err = mqtt_live(&client);
		if ((err != 0) && (err != -EAGAIN)) {
			LOG_ERR("ERROR: mqtt_live: %d", err);
			return;
		}

		if ((fds.revents & POLLIN) == POLLIN) {
			err = mqtt_input(&client);
			if (err != 0) {
				LOG_ERR("mqtt_input: %d", err);
				return;
			}
		}

		if ((fds.revents & POLLERR) == POLLERR) {
			LOG_ERR("POLLERR");
			return;
		}

		if ((fds.revents & POLLNVAL) == POLLNVAL) {
			LOG_ERR("POLLNVAL");
			return;
		}
    }
} /* namespace cloudio */
