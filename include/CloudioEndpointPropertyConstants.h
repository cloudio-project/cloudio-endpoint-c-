//
// Created by lucas on 31/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_CLOUDIOENDPOINTPROPERTYCONSTANTS_H
#define CLOUDIO_ENDPOINT_CPP_CLOUDIOENDPOINTPROPERTYCONSTANTS_H

#include <string>

namespace cloudio {

    /*** Constants ************************************************************************************************/
    const std::string UUID_PROPERTY = "ch.hevs.cloudio.endpoint.uuid";
    const std::string MQTT_HOST_URI_PROPERTY = "ch.hevs.cloudio.endpoint.hostUri";
    const std::string MQTT_CONNECTION_TIMEOUT_PROPERTY = "ch.hevs.cloudio.endpoint.connectTimeout";
    const std::string MQTT_CONNECTION_TIMEOUT_DEFAULT = "5";
    const std::string MQTT_CONNECT_RETRY_PROPERTY = "ch.hevs.cloudio.endpoint.connectRetryInterval";
    const std::string MQTT_CONNECT_RETRY_DEFAULT = "10";
    const std::string MQTT_KEEPALIVE_INTERVAL_PROPERTY = "ch.hevs.cloudio.endpoint.keepAliveInterval";
    const std::string MQTT_KEEPALIVE_INTERVAL_DEFAULT = "60";
    const std::string ENDPOINT_IDENTITY_FILE_PROPERTY = "ch.hevs.cloudio.endpoint.ssl.clientCert";
    const std::string CERT_AUTHORITY_FILE_PROPERTY = "ch.hevs.cloudio.endpoint.ssl.authorityCert";
    const std::string ENDPOINT_IDENTITY_KEY_PROPERTY = "ch.hevs.cloudio.endpoint.ssl.clientKey";
    const std::string SSL_VERIFY_HOSTNAME_PROPERTY = "ch.hevs.cloudio.endpoint.ssl.verifyHostname";
    const std::string SSL_VERIFY_HOSTNAME_DEFAULT = "true";
    const std::string MQTT_MAXINFLIGHT_PROPERTY = "ch.hevs.cloudio.endpoint.maxInFlight";
    const std::string MQTT_MAXINFLIGHT_DEFAULT = "1000";
    const std::string MESSAGE_FORMAT = "ch.hevs.cloudio.endpoint.messageFormat";
    const std::string MESSAGE_FORMAT_DEFAULT = "CBOR";

}

#endif //CLOUDIO_ENDPOINT_CPP_CLOUDIOENDPOINTPROPERTYCONSTANTS_H
