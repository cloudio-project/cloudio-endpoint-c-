/*
 * CJsonMessageFormat.cpp
 *
 *  Created on: 7 Feb 2023
 *      Author: Lucas Bonvin
 */

#ifdef ESP_PLATFORM
#include "CJsonMessageFormat.h"
#include "../include/CloudioEndpoint.h"

using namespace std;

namespace cloudio {

	CJsonMessageFormat::CJsonMessageFormat() {

	}

	CJsonMessageFormat::~CJsonMessageFormat() {
	}

	string CJsonMessageFormat::serializeEndpoint(CloudioEndpoint *endpoint) {
		cJSON *endpointJson = this->jsonSerializeEndpoint(endpoint);

		char *toReturnChar = cJSON_Print(endpointJson);
		string toReturn = toReturnChar;
		cJSON_free(toReturnChar);
		cJSON_Delete(endpointJson);
		return toReturn;
	}

	string CJsonMessageFormat::serializeNode(CloudioNode *node) {
		cJSON *nodejson = this->jsonSerializeNode(node);

		char *toReturnChar = cJSON_Print(nodejson);
		string toReturn = toReturnChar;
		cJSON_free(toReturnChar);
		cJSON_Delete(nodejson);
		return toReturn;
	}

	string CJsonMessageFormat::serializeAttribute(CloudioAttribute *attribute) {
		cJSON *attributeJson = this->jsonSerializeAttribute(attribute);

		char *toReturnChar = cJSON_Print(attributeJson);
		string toReturn = toReturnChar;
		cJSON_free(toReturnChar);
		cJSON_Delete(attributeJson);
		return toReturn;
	}

	string CJsonMessageFormat::serializeDidSetAttribute(CloudioAttribute *attribute,
			const string &correlationID) {
		cJSON *attributeJson = this->jsonSerializeAttribute(attribute);

		cJSON_AddStringToObject(attributeJson, "correlationID",
				correlationID.c_str());

		char *toReturnChar = cJSON_Print(attributeJson);
		string toReturn = toReturnChar;
		cJSON_free(toReturnChar);
		cJSON_Delete(attributeJson);
		return toReturn;
	}

	void CJsonMessageFormat::deserializeAttribute(const string &payload,
			CloudioAttribute *attribute) {
		cJSON *attributeJson;

		attributeJson = cJSON_Parse(payload.c_str());
		if (attributeJson == NULL) {
			cout << "Error during main deserialization process " << endl;
			cJSON_Delete(attributeJson);
			return;
		}

		long timestamp = 0;
		cJSON *timestampJson = cJSON_GetObjectItem(attributeJson, "timestamp");
		if (timestampJson == NULL) {
			cout << "Error during deserialization, no valid timestamp found "
					<< endl;

			cJSON_Delete(timestampJson);
			cJSON_Delete(attributeJson);
			return;
		} else {

			timestamp =
					cJSON_GetObjectItem(attributeJson, "timestamp")->valuedouble;
		}

		if (timestamp != 0) {
			try {
				switch (attribute->getType()) {
				case Invalid:
					break;
				case Boolean: {
					bool boolValue = cJSON_IsTrue(
							cJSON_GetObjectItem(attributeJson, "value"));
					attribute->setValueFromCloud(boolValue, timestamp);
					break;
				}
				case Integer: {
					int integerValue =
							cJSON_GetObjectItem(attributeJson, "value")->valueint;
					attribute->setValueFromCloud(integerValue, timestamp);
					break;
				}

				case Number: {
					double doubleValue =
							cJSON_GetObjectItem(attributeJson, "value")->valuedouble;
					attribute->setValueFromCloud(doubleValue, timestamp);
					break;
				}

				case String: {
					string strValue =
							cJSON_GetObjectItem(attributeJson, "value")->valuestring;
					attribute->setValueFromCloud(strValue, timestamp);
					break;
				}

				default:
					cout << "Type error while deserializing value from @set message"
							<< endl;
					break;
				}
			} catch (const exception &e) {
				cout << "Type error while deserializing value from @set message"
						<< endl;

				cJSON_Delete(timestampJson);
				cJSON_Delete(attributeJson);
				return;
			}
		}
		cJSON_Delete(timestampJson);
	}

	string CJsonMessageFormat::deserializeSetAttribute(const string &payload,
			CloudioAttribute *attribute) {
		cJSON *attributeJson;
		attributeJson = cJSON_Parse(payload.c_str());
		if (attributeJson == NULL) {
			cout << "Error during main deserialization process " << endl;
			cJSON_Delete(attributeJson);
			return "";
		}

		this->deserializeAttribute(payload, attribute);

		string correlationID = "";
		if (cJSON_GetObjectItem(attributeJson, "correlationID") != NULL)
			correlationID =
					cJSON_GetObjectItem(attributeJson, "correlationID")->valuestring;

		cJSON_Delete(attributeJson);
		return correlationID;
	}

	cJSON* CJsonMessageFormat::jsonSerializeEndpoint(CloudioEndpoint *endpoint) {
		cJSON *endpointJson = cJSON_CreateObject();

		cJSON_AddStringToObject(endpointJson, "version",
				endpoint->getVersion().c_str());
		cJSON_AddNumberToObject(endpointJson, "messageFormatVersion", 2);

		cJSON *supportedFormats = cJSON_CreateArray();

		for (auto &formatIt : endpoint->getSupportedFormats()) {
			cJSON *supportedFormat;
			supportedFormat = cJSON_CreateString(formatIt.c_str());
			cJSON_AddItemToArray(supportedFormats, supportedFormat);
		}

		cJSON_AddItemToObject(endpointJson, "supportedFormats", supportedFormats);

		cJSON *nodes = cJSON_CreateObject();

		for (auto &nodeIt : endpoint->getNodes()) {
			cJSON_AddItemToObject(nodes, nodeIt->getName().c_str(),
					jsonSerializeNode(nodeIt));
		}

		cJSON_AddItemToObject(endpointJson, "nodes", nodes);

		return endpointJson;
	}

	cJSON* CJsonMessageFormat::jsonSerializeNode(CloudioNode *node) {
		cJSON *nodeJson = cJSON_CreateObject();

		cJSON *implements = cJSON_CreateArray();

		if (!node->getInterfaces().empty()) {
			for (auto &interfaceIt : node->getInterfaces()) {
				cJSON *interface;
				interface = cJSON_CreateString(interfaceIt.c_str());
				cJSON_AddItemToArray(implements, interface);
			}
		}

		cJSON_AddItemToObject(nodeJson, "implements", implements);

		cJSON *innerObjects = cJSON_CreateObject();

		for (auto &objectIt : node->getObjects()) {
			cJSON_AddItemToObject(innerObjects, objectIt->getName().c_str(),
					jsonSerializeObject(objectIt));
		}

		cJSON_AddItemToObject(nodeJson, "objects", innerObjects);

		return nodeJson;
	}

	cJSON* CJsonMessageFormat::jsonSerializeObject(CloudioObject *object) {
		cJSON *objectJson = cJSON_CreateObject();

		if (object->getConforms().empty())
			cJSON_AddStringToObject(objectJson, "conforms",
					object->getConforms().c_str());

		cJSON *innerObjects = cJSON_CreateObject();

		for (auto &objectIt : object->getObjects()) {
			cJSON_AddItemToObject(innerObjects, objectIt->getName().c_str(),
					jsonSerializeObject(objectIt));
		}

		cJSON_AddItemToObject(objectJson, "objects", innerObjects);

		cJSON *attributes = cJSON_CreateObject();
		;

		for (auto &attributeIt : object->getAttributes()) {
			cJSON_AddItemToObject(attributes, attributeIt->getName().c_str(),
					jsonSerializeAttribute(attributeIt));
		}
		cJSON_AddItemToObject(objectJson, "attributes", attributes);

		return objectJson;
	}

	cJSON* CJsonMessageFormat::jsonSerializeAttribute(CloudioAttribute *attribute) {
		cJSON *attributeJson = cJSON_CreateObject();
		switch (attribute->getType()) {
		case Invalid:
			//should throw exception?
			break;

		case Boolean: {
			cJSON_AddStringToObject(attributeJson, "type", "Boolean");
			bool *attributeValue = (bool*) attribute->getValue();
			cJSON_AddBoolToObject(attributeJson, "value", *attributeValue);
			break;
		}
		case Integer: {
			cJSON_AddStringToObject(attributeJson, "type", "Integer");
			int *attributeValue = (int*) attribute->getValue();
			cJSON_AddNumberToObject(attributeJson, "value", *attributeValue);
			break;
		}
		case Number: {
			cJSON_AddStringToObject(attributeJson, "type", "Number");
			double *attributeValue = (double*) attribute->getValue();
			cJSON_AddNumberToObject(attributeJson, "value", *attributeValue);
			break;
		}

		case String: {
			cJSON_AddStringToObject(attributeJson, "type", "String");
			string *attributeValue = (string*) attribute->getValue();
			cJSON_AddStringToObject(attributeJson, "value",
					attributeValue->c_str());
			break;
		}

		default:
			break;
		}
		switch (attribute->getConstraint()) {
		case Static:
			cJSON_AddStringToObject(attributeJson, "constraint", "Static");
			break;
		case Parameter:
			cJSON_AddStringToObject(attributeJson, "constraint", "Parameter");
			break;
		case Status:
			cJSON_AddStringToObject(attributeJson, "constraint", "Status");
			break;
		case SetPoint:
			cJSON_AddStringToObject(attributeJson, "constraint", "SetPoint");
			break;
		case Measure:
			cJSON_AddStringToObject(attributeJson, "constraint", "Measure");
			break;
		}

		if (attribute->getConstraint() != CloudioAttributeConstraint::Static) {
			if (attribute->getTimestamp() != 0) {
				cJSON_AddNumberToObject(attributeJson, "timestamp",
						attribute->getTimestamp());
			}
		}

		return attributeJson;
	}
} // cloudio
#endif //ESP_PLATFORM
