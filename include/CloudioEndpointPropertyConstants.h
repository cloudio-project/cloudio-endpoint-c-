//
// Created by lucas on 31/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_CLOUDIOENDPOINTPROPERTYCONSTANTS_H
#define CLOUDIO_ENDPOINT_CPP_CLOUDIOENDPOINTPROPERTYCONSTANTS_H

#include <string>

using namespace std;

namespace cloudio {

    /*** Constants ************************************************************************************************/
    const string UUID_PROPERTY = "ch.hevs.cloudio.endpoint.uuid";
    const string MQTT_HOST_URI_PROPERTY = "ch.hevs.cloudio.endpoint.hostUri";
    const string MQTT_CONNECTION_TIMEOUT_PROPERTY = "ch.hevs.cloudio.endpoint.connectTimeout";
    const string MQTT_CONNECTION_TIMEOUT_DEFAULT = "5";
    const string MQTT_CONNECT_RETRY_PROPERTY = "ch.hevs.cloudio.endpoint.connectRetryInterval";
    const string MQTT_CONNECT_RETRY_DEFAULT = "10";
    const string MQTT_KEEPALIVE_INTERVAL_PROPERTY = "ch.hevs.cloudio.endpoint.keepAliveInterval";
    const string MQTT_KEEPALIVE_INTERVAL_DEFAULT = "60";
    const string ENDPOINT_IDENTITY_FILE_PROPERTY = "ch.hevs.cloudio.endpoint.ssl.clientCert";
    const string CERT_AUTHORITY_FILE_PROPERTY = "ch.hevs.cloudio.endpoint.ssl.authorityCert";
    const string ENDPOINT_IDENTITY_KEY_PROPERTY = "ch.hevs.cloudio.endpoint.ssl.clientKey";
    const string SSL_VERIFY_HOSTNAME_PROPERTY = "ch.hevs.cloudio.endpoint.ssl.verifyHostname";
    const string SSL_VERIFY_HOSTNAME_DEFAULT = "true";

}

#endif //CLOUDIO_ENDPOINT_CPP_CLOUDIOENDPOINTPROPERTYCONSTANTS_H
