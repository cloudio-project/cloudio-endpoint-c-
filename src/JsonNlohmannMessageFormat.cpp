//
// Created by lucas on 20/10/22.
//

#include "../include/JsonNlohmannMessageFormat.h"
namespace cloudio {

    JsonNlohmannMessageFormat::JsonNlohmannMessageFormat() {

    }

    JsonNlohmannMessageFormat::~JsonNlohmannMessageFormat() {

    }

    string JsonNlohmannMessageFormat::serializeEndpoint(CloudioEndpoint endpoint) {
        json endpointJson;

        serializeEndpoint(endpoint, endpointJson);

        return to_string(endpointJson);
    }

    string JsonNlohmannMessageFormat::serializeNode(CloudioNode node) {
        json nodeJson;

        serializeNode(node, nodeJson);

        return to_string(nodeJson);
    }

    string JsonNlohmannMessageFormat::serializeAttribute(CloudioAttribute<int> attribute) {
        json attributeJson;

        serializeAttribute(attribute, attributeJson);

        return to_string(attributeJson);
    }

    string JsonNlohmannMessageFormat::serializeAttribute(CloudioAttribute<double> attribute) {
        json attributeJson;

        serializeAttribute(attribute, attributeJson);

        return to_string(attributeJson);
    }

    string JsonNlohmannMessageFormat::serializeAttribute(CloudioAttribute<bool> attribute) {
        json attributeJson;

        serializeAttribute(attribute, attributeJson);

        return to_string(attributeJson);
    }

    string JsonNlohmannMessageFormat::serializeAttribute(CloudioAttribute<string> attribute) {
        json attributeJson;

        serializeAttribute(attribute, attributeJson);

        return to_string(attributeJson);
    }

    void JsonNlohmannMessageFormat::serializeEndpoint(CloudioEndpoint endpoint, json &endpointJson) {

    }

    void JsonNlohmannMessageFormat::serializeNode(CloudioNode node, json &nodeJson) {

    }

    void JsonNlohmannMessageFormat::serializeAttribute(CloudioAttribute<int> attribute, json &attributeJson) {

        attributeJson["type"] = "Integer";
        attributeJson["constraint"] = attribute.getConstraint();
        attributeJson["timestamp"] = attribute.getType();
        attributeJson["value"] = attribute.getType();
    }

    void JsonNlohmannMessageFormat::serializeAttribute(CloudioAttribute<double> attribute, json &attributeJson) {

        attributeJson["type"] = "Double";
        attributeJson["constraint"] = attribute.getConstraint();
        attributeJson["timestamp"] = attribute.getType();
        attributeJson["value"] = attribute.getType();
    }

    void JsonNlohmannMessageFormat::serializeAttribute(CloudioAttribute<bool> attribute, json &attributeJson) {

        attributeJson["type"] = "Boolean";
        attributeJson["constraint"] = attribute.getConstraint();
        attributeJson["timestamp"] = attribute.getType();
        attributeJson["value"] = attribute.getType();
    }

    void JsonNlohmannMessageFormat::serializeAttribute(CloudioAttribute<string> attribute, json &attributeJson) {
        attributeJson["type"] = "String";
        attributeJson["constraint"] = attribute.getConstraint();
        attributeJson["timestamp"] = attribute.getType();
        attributeJson["value"] = attribute.getType();
    }
}