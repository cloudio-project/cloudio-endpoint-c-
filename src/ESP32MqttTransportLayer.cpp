/*
 * ESP32MqttTransportLayer.cpp
 *
 *  Created on: 7 Feb 2023
 *      Author: Lucas Bonvin
 */

#include "../include/ESP32MqttTransportLayer.h"

#include "../include/CloudioAttributeConstrainException.h"
#include "../include/CloudioAttributeTypeException.h"

using namespace std;

extern const uint8_t client_cert_pem_start[] asm("_binary_client_crt_start");
extern const uint8_t client_cert_pem_end[] asm("_binary_client_crt_end");
extern const uint8_t client_key_pem_start[] asm("_binary_client_key_start");
extern const uint8_t client_key_pem_end[] asm("_binary_client_key_end");
extern const uint8_t server_cert_pem_start[] asm("_binary_mosquitto_org_crt_start");
extern const uint8_t server_cert_pem_end[] asm("_binary_mosquitto_org_crt_end");

namespace cloudio {
ESP32MqttTransportLayer::ESP32MqttTransportLayer() {
}

ESP32MqttTransportLayer::~ESP32MqttTransportLayer() {
	// TODO Auto-generated destructor stub
}

ESP32MqttTransportLayer& ESP32MqttTransportLayer::getInstance() {
	static ESP32MqttTransportLayer transportLayer;
	return transportLayer;
}

void ESP32MqttTransportLayer::initTransportLayer(const string &uuid,
		ICloudioEndpointConfiguration *const endpointConfiguration) {

	this->mqtt_cfg.broker.address.uri = "mqtts://207.180.220.211:8883";
	this->mqtt_cfg.broker.verification.certificate =
			(const char*) server_cert_pem_start;
	this->mqtt_cfg.broker.verification.skip_cert_common_name_check = true; // equivalent to disable the hostname verification in paho
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
	int msg_id = esp_mqtt_client_publish(this->client, topic.c_str(),
			payload.c_str(), payload.size(), qos, retained);

}

void ESP32MqttTransportLayer::subscribe(const string &topic,
		const int qos) const {
	int msg_id = esp_mqtt_client_subscribe(this->client, topic.c_str(), qos);

}

bool ESP32MqttTransportLayer::isOnline() const {
	return this->online;
}

void ESP32MqttTransportLayer::setTransportLayerMessageListener(
		ICloudioTransportLayerMessageListener*) {
}

void ESP32MqttTransportLayer::mqttCallback(void *handler_args,
		esp_event_base_t base, int32_t event_id, void *event_data) {

	esp_mqtt_event_handle_t event = (esp_mqtt_event_handle_t) event_data;
	esp_mqtt_client_handle_t client = event->client;

	switch ((esp_mqtt_event_id_t) event_id) {
	case MQTT_EVENT_CONNECTED:
		ESP32MqttTransportLayer::getInstance().online = true;
		printf("Connected to mqtt broker\n");
		break;
	case MQTT_EVENT_DISCONNECTED:
		ESP32MqttTransportLayer::getInstance().online = false;
		printf("Disonnected to mqtt broker");
		break;
	case MQTT_EVENT_SUBSCRIBED:	//nothing to do here, kept for debug
		printf("We subscribed to something\n");
		break;
	case MQTT_EVENT_UNSUBSCRIBED:	//nothing to do here, kept for debug
		break;
	case MQTT_EVENT_PUBLISHED:	//nothing to do here, kept for debug
		printf("Something has been published\n");
		break;
	case MQTT_EVENT_DATA: // received data from subscription
		printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
		printf("DATA=%.*s\r\n", event->data_len, event->data);
		try {
			if(ESP32MqttTransportLayer::getInstance().cloudioTransportLayerMessageListener == nullptr){
				printf("cloudioTransportLayerMessageListener IS nullptr");
			}
			else{
				printf("cloudioTransportLayerMessageListener is not nullptr");
			}
			ESP32MqttTransportLayer::getInstance().cloudioTransportLayerMessageListener->messageArrived(
					event->topic, event->data);
		} catch (CloudioAttributeConstrainException &e) {
			cout << "CloudioAttributeConstrainException " << e.what() << endl;
		} catch (CloudioAttributeTypeException &e) {
			cout << "CloudioAttributeTypeException " << e.what() << endl;
		} catch (InvalidPropertyException &e) {
			cout << "InvalidPropertyException " << e.what() << endl;
		} catch (TransportLayerException &e) {
			cout << "TransportLayerException " << e.what() << endl;
		} catch (exception &e) {
			cout << "other uncaught exception " << e.what() << endl;
		}
		break;
	case MQTT_EVENT_ERROR:
		break;
	default:
		break;
	}
}
}
