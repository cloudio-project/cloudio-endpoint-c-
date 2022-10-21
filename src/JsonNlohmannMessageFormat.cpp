//
// Created by lucas on 20/10/22.
//

#include "../include/JsonNlohmannMessageFormat.h"

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


    json JsonNlohmannMessageFormat::jsonSerializeEndpoint(CloudioEndpoint *endpoint) {
        json endpointJson;

        endpointJson["version"] = endpoint->getVersion();
        endpointJson["messageFormatVersion"] = 2;

        json supportedFormats = json::array();

        for (std::list<string>::iterator formatIt = endpoint->getSupportedFormats().begin();
             formatIt != endpoint->getSupportedFormats().end(); ++formatIt) {
            supportedFormats.push_back(*formatIt);
        }

        endpointJson["supportedFormats"] = supportedFormats;

        json nodes = json::array();

        for (std::list<CloudioNode *>::iterator nodeIt = endpoint->getNodes().begin();
             nodeIt != endpoint->getNodes().end(); ++nodeIt) {
            nodes.push_back(jsonSerializeNode(*nodeIt));
        }

        endpointJson["nodes"] = nodes;

        return endpointJson;
    }

    json JsonNlohmannMessageFormat::jsonSerializeNode(CloudioNode *node) {
        json nobeJson;

        json implements = json::array();

        for (std::list<string>::iterator interfaceIt = node->getInterfaces().begin();
             interfaceIt != node->getInterfaces().end(); ++interfaceIt) {
            implements.push_back(*interfaceIt);
        }

        nobeJson["implements"] = implements;

        json innerObjects = json::array();

        for (std::list<CloudioObject *>::iterator objectIt = node->getObjects().begin();
             objectIt != node->getObjects().end(); ++objectIt) {
            innerObjects.push_back(jsonSerializeObject(*objectIt));
        }

        nobeJson["objects"] = innerObjects;

        return nobeJson;
    }

    json JsonNlohmannMessageFormat::jsonSerializeObject(CloudioObject *object) {
        json objectJson;

        if (object->getConforms().empty())
            objectJson["conforms"] = object->getConforms();
        json innerObjects = json::array();

        for (std::list<CloudioObject *>::iterator objectIt = object->getObjects().begin();
             objectIt != object->getObjects().end(); ++objectIt) {
            innerObjects.push_back(jsonSerializeObject(*objectIt));
        }

        objectJson["objects"] = innerObjects;

        json attributes = json::array();

        for (std::list<CloudioAttribute *>::iterator attributeIt = object->getAttributes().begin();
             attributeIt != object->getAttributes().end(); ++attributeIt) {
            innerObjects.push_back(jsonSerializeAttribute(*attributeIt));
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
                attributeJson["value"] = *attributeValue ? "true" : "false";
                break;
            }
            case Integer: {
                attributeJson["type"] = "Integer";
                int *attributeValue = (int *) attribute->getValue();
                attributeJson["value"] = to_string(*attributeValue);
                break;
            }
            case Number: {
                attributeJson["type"] = "Number";
                double *attributeValue = (double *) attribute->getValue();
                attributeJson["value"] = to_string(*attributeValue);
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
        };
        attributeJson["constraint"] = attribute->getConstraint();

        if (attribute->getConstraint() != CloudioAttributeConstraint::Static) {
            if (attribute->getTimestamp() != 0) {
                attributeJson["timestamp"] = attribute->getTimestamp();
            }
        }

        return attributeJson;
    }

}