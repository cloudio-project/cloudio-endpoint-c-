/*
 * ESP32MqttTransportLayer.cpp
 *
 *  Created on: 7 Feb 2023
 *      Author: Lucas Bonvin
 */

#ifdef ESP_PLATFORM
#include "../include/ESP32MqttTransportLayer.h"

#include "../include/CloudioAttributeConstrainException.h"
#include "../include/CloudioAttributeTypeException.h"
#include "../include/PropertiesHelper.h"

using namespace std;

extern const uint8_t client_cert_pem_start[] asm("_binary_clientCertificate_PEM_start");
extern const uint8_t client_cert_pem_end[] asm("_binary_clientCertificate_PEM_end");
extern const uint8_t client_key_pem_start[] asm("_binary_clientPrivateKey_PEM_start");
extern const uint8_t client_key_pem_end[] asm("_binary_clientPrivateKey_PEM_end");
extern const uint8_t server_cert_pem_start[] asm("_binary_caCertificate_PEM_start");
extern const uint8_t server_cert_pem_end[] asm("_binary_caCertificate_PEM_end");

namespace cloudio {
	ESP32MqttTransportLayer::ESP32MqttTransportLayer() {
	}

	ESP32MqttTransportLayer::~ESP32MqttTransportLayer() {
	}

	ESP32MqttTransportLayer& ESP32MqttTransportLayer::getInstance() {
		static ESP32MqttTransportLayer transportLayer;
		return transportLayer;
	}

	void ESP32MqttTransportLayer::initTransportLayer(const string &uuid,
			ICloudioEndpointConfiguration *const endpointConfiguration) {
		transportLayerProperties localProperties;
		try{
			localProperties = getTransportLayerProperties(endpointConfiguration);
		}
		catch(InvalidPropertyException &e){
			throw e;
		}


		this->mqtt_cfg.broker.address.uri = localProperties.hostURI.c_str();
		this->mqtt_cfg.broker.verification.certificate =
				(const char*) server_cert_pem_start;
		this->mqtt_cfg.broker.verification.skip_cert_common_name_check = !localProperties.verifyHostname; // equivalent to disable the hostname verification in paho
		this->mqtt_cfg.credentials.authentication.certificate =
				(const char*) client_cert_pem_start;
		this->mqtt_cfg.credentials.authentication.key =
				(const char*) client_key_pem_start;

		this->client = esp_mqtt_client_init(&mqtt_cfg);
		/* The last argument may be used to pass data to the event handler, in this example mqtt_event_handler */
		esp_mqtt_client_register_event(this->client,
				(esp_mqtt_event_id_t) ESP_EVENT_ANY_ID, this->mqttCallback, NULL);
	}

	void ESP32MqttTransportLayer::connect() {
		esp_mqtt_client_start(this->client);
	}

	void ESP32MqttTransportLayer::disconnect() {
	}

	void ESP32MqttTransportLayer::publish(const string &topic,
			const string &payload, const int qos, const bool retained) const {
		esp_mqtt_client_publish(this->client, topic.c_str(),
				payload.c_str(), payload.size(), qos, retained);

	}

	void ESP32MqttTransportLayer::subscribe(const string &topic,
			const int qos) const {
		esp_mqtt_client_subscribe(this->client, topic.c_str(), qos);

	}

	bool ESP32MqttTransportLayer::isOnline() const {
		return this->online;
	}

	void ESP32MqttTransportLayer::setTransportLayerMessageListener(
			ICloudioTransportLayerMessageListener *cloudioTransportLayerMessageListener) {
		this->cloudioTransportLayerMessageListener =
				cloudioTransportLayerMessageListener;
	}

	void ESP32MqttTransportLayer::mqttCallback(void *handler_args,
			esp_event_base_t base, int32_t event_id, void *event_data) {

		esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t) event_data;
		esp_mqtt_client_handle_t client = event->client;

		switch ((esp_mqtt_event_id_t) event_id) {
		case MQTT_EVENT_CONNECTED:
			ESP32MqttTransportLayer::getInstance().online = true;
			break;
		case MQTT_EVENT_DISCONNECTED:
			ESP32MqttTransportLayer::getInstance().online = false;
			break;
		case MQTT_EVENT_SUBSCRIBED:	//nothing to do here, kept for debug
			break;
		case MQTT_EVENT_UNSUBSCRIBED:	//nothing to do here, kept for debug
			break;
		case MQTT_EVENT_PUBLISHED:	//nothing to do here, kept for debug
			break;
		case MQTT_EVENT_DATA: // received data from subscription
		{
			string topicStr;
			string dataStr;

			topicStr.assign(event->topic, event->topic + event->topic_len);
			dataStr.assign(event->data, event->data + event->data_len);

			ESP32MqttTransportLayer::getInstance().cloudioTransportLayerMessageListener->messageArrived(
					topicStr, dataStr);
			break;
		}
		case MQTT_EVENT_ERROR:
			break;
		default:
			break;
		}
	}
}/* namespace cloudio */
#endif //ESP_PLATFORM
