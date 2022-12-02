//
// Created by lucas on 20/10/22.
//

#include "../include/JsonNlohmannMessageFormat.h"
#include "../include/CloudioEndpoint.h"
#include <iostream>

namespace cloudio {

    JsonNlohmannMessageFormat::JsonNlohmannMessageFormat() {

    }

    JsonNlohmannMessageFormat::~JsonNlohmannMessageFormat() {

    }

    string JsonNlohmannMessageFormat::serializeEndpoint(CloudioEndpoint *endpoint) {
        json endpointJson = jsonSerializeEndpoint(endpoint);

        return to_string(endpointJson);
    }

    string JsonNlohmannMessageFormat::serializeNode(CloudioNode *node) {
        json nodeJson = jsonSerializeNode(node);

        return to_string(nodeJson);
    }

    string JsonNlohmannMessageFormat::serializeAttribute(CloudioAttribute *attribute) {
        json attributeJson = jsonSerializeAttribute(attribute);

        return to_string(attributeJson);
    }


    string JsonNlohmannMessageFormat::serializeDidSetAttribute(CloudioAttribute *attribute, string correlationID) {
        json attributeJson = jsonSerializeAttribute(attribute);
        attributeJson["correlationID"] = correlationID;
        return to_string(attributeJson);
    }

    void JsonNlohmannMessageFormat::deserializeAttribute(string payload, CloudioAttribute *attribute) {
        json attributeJson = json::parse(payload);

        long timestamp;
        try {
            timestamp = attributeJson["timestamp"];
        }
        catch (exception e) {
            //TODO better error management
            cout << e.what() << endl;
            return;
        }


        if (timestamp != 0) {
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
                    //throw new IOException("Attribute type not supported!");
                    break;
            }
        }
    }


    string JsonNlohmannMessageFormat::deserializeSetAttribute(string payload, CloudioAttribute *attribute) {
        json attributeJson = json::parse(payload);

        this->deserializeAttribute(payload, attribute);

        return attributeJson["correlationID"] !=  "null" ? attributeJson["correlationID"] : "";
    }


    json JsonNlohmannMessageFormat::jsonSerializeEndpoint(CloudioEndpoint *endpoint) {
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

    json JsonNlohmannMessageFormat::jsonSerializeNode(CloudioNode *node) {
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

    json JsonNlohmannMessageFormat::jsonSerializeObject(CloudioObject *object) {
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

    json JsonNlohmannMessageFormat::jsonSerializeAttribute(CloudioAttribute *attribute) {
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

}