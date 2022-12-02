//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP__CLOUDIOENDPOINT_H
#define CLOUDIO_ENDPOINT_CPP__CLOUDIOENDPOINT_H

#include "CloudioNode.h"
#include "ITransportLayer.h"
#include "ICloudioMessageFormat.h"
#include "ICloudioNodeContainer.h"

namespace cloudio {

    class CloudioEndpoint : public ICloudioNodeContainer, public ICloudioTransportLayerMessageListener {

    public:
        CloudioEndpoint(string uuidOrAppName, ICloudioMessageFormat *cloudioMessageFormat = nullptr,
                        ITransportLayer *transportLayer = nullptr,
                        ICloudioEndpointConfiguration *endpointConfiguration = nullptr);

        ~CloudioEndpoint();

        string getVersion();

        list<CloudioNode *> getNodes();

        CloudioNode * getNodeByName(string nodeName);

        list<string> getSupportedFormats();

        string getName();

        void addNode(CloudioNode *node);


        // ICloudioNodeContainer interface
        void attributeHasChangedByEndpoint(CloudioAttribute *attribute);

        // ICloudioTransportLayerMessageListener interface
        void messageArrived(string topic, string payload);

    private:
        string uuid;
        string version = "v0.2";
        list<CloudioNode *> nodes;
        list<string> supportedFormats{"JSON"};
        ICloudioMessageFormat *messageFormat;
        ITransportLayer *transportLayer;
        ICloudioEndpointConfiguration *endpointConfiguration;

        void set(string topic, list<string> location, string payload);

    };

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP__CLOUDIOENDPOINT_H
