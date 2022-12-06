//
// Created by lucas on 20/10/22.
//

#include "../include/JsonNlohmannMessageFormat.h"
#include "../include/CloudioEndpoint.h"
#include <iostream>

namespace cloudio {

    JsonNlohmannMessageFormat::JsonNlohmannMessageFormat(const string &format) {
        if (format == "JSON") {
            jsonNlohmannMessageFormatSerializer = new JSONJsonNlohmannMessageFormatSerializer();
        } else if (format == "CBOR") {
            jsonNlohmannMessageFormatSerializer = new CBORJsonNlohmannMessageFormatSerializer();
        } else {    //default, JSON
            jsonNlohmannMessageFormatSerializer = new JSONJsonNlohmannMessageFormatSerializer();
        }
    }

    JsonNlohmannMessageFormat::~JsonNlohmannMessageFormat() {
        delete jsonNlohmannMessageFormatSerializer;
    }

    string JsonNlohmannMessageFormat::serializeEndpoint(CloudioEndpoint *const endpoint) {
        json endpointJson = jsonSerializeEndpoint(endpoint);

        return jsonNlohmannMessageFormatSerializer->serialize(endpointJson);
    }

    string JsonNlohmannMessageFormat::serializeNode(CloudioNode *const node) {
        json nodeJson = jsonSerializeNode(node);

        return jsonNlohmannMessageFormatSerializer->serialize(nodeJson);
    }

    string JsonNlohmannMessageFormat::serializeAttribute(CloudioAttribute *const attribute) {
        json attributeJson = jsonSerializeAttribute(attribute);

        return jsonNlohmannMessageFormatSerializer->serialize(attributeJson);
    }

    string
    JsonNlohmannMessageFormat::serializeDidSetAttribute(CloudioAttribute *const attribute,
                                                        const string &correlationID) {
        json attributeJson = jsonSerializeAttribute(attribute);
        attributeJson["correlationID"] = correlationID;
        return jsonNlohmannMessageFormatSerializer->serialize(attributeJson);
    }

    void JsonNlohmannMessageFormat::deserializeAttribute(const string &payload, CloudioAttribute *const attribute) {
        json attributeJson;
        try {
            attributeJson = jsonNlohmannMessageFormatSerializer->deserialize(payload);
        } catch (exception e) {
            cout << "Error during main deserialization process " << e.what() << endl;
            return;
        }

        long timestamp;
        try {
            timestamp = attributeJson["timestamp"];
        }
        catch (exception e) {
            cout << "Error during deserialization, no valid timestamp found " << e.what() << endl;
            return;
        }

        if (timestamp != 0) {
            try {
                switch (attribute->getType()) {
                    case Invalid:
                        break;
                    case Boolean: {
                        bool boolValue = attributeJson["value"];
                        attribute->setValueFromCloud(boolValue, timestamp);
                        break;
                    }
                    case Integer: {
                        int integerValue = attributeJson["value"];
                        attribute->setValueFromCloud(integerValue, timestamp);
                        break;
                    }

                    case Number: {
                        double doubleValue = attributeJson["value"];
                        attribute->setValueFromCloud(doubleValue, timestamp);
                        break;
                    }

                    case String: {
                        string strValue = attributeJson["value"];
                        attribute->setValueFromCloud(strValue, timestamp);
                        break;
                    }

                    default:
                        cout << "Type error while deserializing value from @set message" << endl;
                        break;
                }
            }
            catch (exception e) {
                cout << "Type error while deserializing value from @set message" << endl;
                return;
            }
        }
    }

    string
    JsonNlohmannMessageFormat::deserializeSetAttribute(const string &payload, CloudioAttribute *const attribute) {
        json attributeJson;
        try {
            attributeJson = jsonNlohmannMessageFormatSerializer->deserialize(payload);
        } catch (exception e) {
            cout << "Error during main deserialization process " << e.what() << endl;
            return "";
        }

        this->deserializeAttribute(payload, attribute);

        string correlationID = "";
        if (attributeJson["correlationID"] != nullptr && attributeJson["correlationID"].type() == value_t::string)
            correlationID = attributeJson["correlationID"];
        return correlationID != "null" ? correlationID : "";
    }

    json JsonNlohmannMessageFormat::jsonSerializeEndpoint(CloudioEndpoint *const endpoint) {
        json endpointJson;

        endpointJson["version"] = endpoint->getVersion();
        endpointJson["messageFormatVersion"] = 2;

        json supportedFormats = json::array();

        for (auto &formatIt: endpoint->getSupportedFormats()) {
            supportedFormats.push_back(formatIt);
        }


        endpointJson["supportedFormats"] = supportedFormats;

        json nodes;

        for (auto &nodeIt: endpoint->getNodes()) {
            nodes[nodeIt->getName()] = jsonSerializeNode(nodeIt);
        }

        endpointJson["nodes"] = nodes;

        return endpointJson;
    }

    json JsonNlohmannMessageFormat::jsonSerializeNode(CloudioNode *const node) {
        json nobeJson;

        json implements = json::array();
        if (!node->getInterfaces().empty()) {
            for (auto &interfaceIt: node->getInterfaces()) {
                implements.push_back(interfaceIt);
            }
        }

        nobeJson["implements"] = implements;

        json innerObjects;

        for (auto &objectIt: node->getObjects()) {
            innerObjects[objectIt->getName()] = jsonSerializeObject(objectIt);
        }

        nobeJson["objects"] = innerObjects;

        return nobeJson;
    }

    json JsonNlohmannMessageFormat::jsonSerializeObject(CloudioObject *const object) {
        json objectJson;

        if (object->getConforms().empty())
            objectJson["conforms"] = object->getConforms();
        json innerObjects;

        for (auto &objectIt: object->getObjects()) {
            innerObjects[objectIt->getName()] = jsonSerializeObject(objectIt);
        }

        objectJson["objects"] = innerObjects;

        json attributes;

        for (auto &attributeIt: object->getAttributes()) {
            innerObjects[attributeIt->getName()] = jsonSerializeAttribute(attributeIt);
        }

        objectJson["attributes"] = innerObjects;

        return objectJson;
    }

    json JsonNlohmannMessageFormat::jsonSerializeAttribute(CloudioAttribute *const attribute) {
        json attributeJson;
        switch (attribute->getType()) {
            case Invalid:
                //should throw exception?
                break;

            case Boolean: {
                attributeJson["type"] = "Boolean";
                bool *attributeValue = (bool *) attribute->getValue();
                attributeJson["value"] = *attributeValue;
                break;
            }
            case Integer: {
                attributeJson["type"] = "Integer";
                int *attributeValue = (int *) attribute->getValue();
                attributeJson["value"] = *attributeValue;
                break;
            }
            case Number: {
                attributeJson["type"] = "Number";
                double *attributeValue = (double *) attribute->getValue();
                attributeJson["value"] = *attributeValue;
                break;
            }

            case String: {
                attributeJson["type"] = "String";
                string *attributeValue = (string *) attribute->getValue();
                attributeJson["value"] = *attributeValue;
                break;
            }

            default:
                break;
        }
        switch (attribute->getConstraint()) {
            case Static:
                attributeJson["constraint"] = "Static";
                break;
            case Parameter:
                attributeJson["constraint"] = "Parameter";
                break;
            case Status:
                attributeJson["constraint"] = "Status";
                break;
            case SetPoint:
                attributeJson["constraint"] = "SetPoint";
                break;
            case Measure:
                attributeJson["constraint"] = "Measure";
                break;
        }

        if (attribute->getConstraint() != CloudioAttributeConstraint::Static) {
            if (attribute->getTimestamp() != 0) {
                attributeJson["timestamp"] = attribute->getTimestamp();
            }
        }

        return attributeJson;
    }
} // cloudio