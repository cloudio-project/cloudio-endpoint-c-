//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP__CLOUDIOENDPOINT_H
#define CLOUDIO_ENDPOINT_CPP__CLOUDIOENDPOINT_H

#include "CloudioNode.h"
#include "ITransportLayer.h"
#include "ICloudioMessageFormat.h"

namespace cloudio {

    class CloudioEndpoint {

    public:
        CloudioEndpoint(string uuidOrAppName, ICloudioMessageFormat *cloudioMessageFormat = nullptr,
                        ITransportLayer *transportLayer = nullptr);

        ~CloudioEndpoint();

        string getVersion();

        list<CloudioNode *> getNodes();

        list<string> getSupportedFormats();

        void addNode(CloudioNode *node);

    private:
        string uuid;
        string version = "v0.2";
        list<CloudioNode *> nodes;
        list<string> supportedFormats{"JSON"};
        ICloudioMessageFormat *messageFormat;
        ITransportLayer *transportLayer;

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


    };

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP__CLOUDIOENDPOINT_H
