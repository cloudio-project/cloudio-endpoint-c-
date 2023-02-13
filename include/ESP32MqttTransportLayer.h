/*
 * ESP32MqttTransportLayer.h
 *
 *  Created on: 7 Feb 2023
 *      Author: Lucas Bonvin
 */

#ifdef ESP_PLATFORM
#ifndef COMPONENTS_CLOUDIO_ENDPOINT_CPP_INCLUDE_ESP32MQTTTRANSPORTLAYER_H_
#define COMPONENTS_CLOUDIO_ENDPOINT_CPP_INCLUDE_ESP32MQTTTRANSPORTLAYER_H_

#include "ITransportLayer.h"
#include "mqtt_client.h"

namespace cloudio {

	class ESP32MqttTransportLayer: public cloudio::ITransportLayer {
	public:
		virtual ~ESP32MqttTransportLayer();

		static ESP32MqttTransportLayer& getInstance();

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
				ICloudioTransportLayerMessageListener*);

	private:
		ESP32MqttTransportLayer();
		esp_mqtt_client_config_t mqtt_cfg;
		esp_mqtt_client_handle_t client;

		bool online = false;

		static void mqttCallback(void *handler_args, esp_event_base_t base, int32_t event_id, void *event_data);
	};
} // cloudio
#endif /* COMPONENTS_CLOUDIO_ENDPOINT_CPP_INCLUDE_ESP32MQTTTRANSPORTLAYER_H_ */
#endif //ESP_PLATFORM
