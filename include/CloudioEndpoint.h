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
        CloudioEndpoint(const std::string &uuidOrAppName, ICloudioMessageFormat *cloudioMessageFormat = nullptr,
                        ITransportLayer *transportLayer = nullptr,
                        ICloudioEndpointConfiguration *endpointConfiguration = nullptr);

        ~CloudioEndpoint();

        std::string getVersion();

        std::list<CloudioNode *> getNodes();

        CloudioNode *getNodeByName(const std::string &nodeName);

        std::list<std::string> getSupportedFormats();

        std::string getName();

        void addNode(CloudioNode *node);

        // ICloudioNodeContainer interface
        void attributeHasChangedByEndpoint(CloudioAttribute *attribute);

        // ICloudioTransportLayerMessageListener interface
        void messageArrived(const std::string &topic, const std::string &payload);

    private:
        std::string uuid;
        std::string version = "v0.2";
        std::list<CloudioNode *> nodes;
        std::list<std::string> supportedFormats{"JSON", "CBOR"};
        ICloudioMessageFormat *messageFormat;
        ITransportLayer *transportLayer;
        ICloudioEndpointConfiguration *endpointConfiguration;

        void
        set(const std::string &topic, std::list<std::string> location, ICloudioMessageFormat *setMessageFormat, const std::string &payload);

    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP__CLOUDIOENDPOINT_H
