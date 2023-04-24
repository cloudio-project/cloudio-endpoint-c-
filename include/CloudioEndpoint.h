//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP__CLOUDIOENDPOINT_H
#define CLOUDIO_ENDPOINT_CPP__CLOUDIOENDPOINT_H

#include "CloudioNode.h"
#include "ITransportLayer.h"
#include "ICloudioMessageFormat.h"
#include "ICloudioNodeContainer.h"
#include "Transaction.h"
#include <queue>

namespace cloudio {

    class CloudioEndpoint : public ICloudioNodeContainer, public ICloudioTransportLayerMessageListener {

    public:
        CloudioEndpoint(const std::string &uuidOrAppName, ICloudioMessageFormat *cloudioMessageFormat = nullptr,
                        ITransportLayer *transportLayer = nullptr,
                        ICloudioEndpointConfiguration *endpointConfiguration = nullptr);

        ~CloudioEndpoint();

        std::string getVersion();

        const std::vector<CloudioNode *> &getNodes();

        CloudioNode *getNodeByName(const std::string &nodeName);

        std::vector<std::string> getSupportedFormats();

        const std::string &getName() const;

        void addNode(CloudioNode *node);

        bool isOnline();

        void beginTransaction();

        void commitTransaction();

        void rollbackTransaction();
        // ICloudioNodeContainer interface
        void attributeHasChangedByEndpoint(CloudioAttribute &attribute);

        // ICloudioTransportLayerMessageListener interface
        void messageArrived(const std::string &topic, const std::string &payload);

    private:
        std::string uuid;
        std::string version = "v0.2";
        std::vector<CloudioNode *> nodes;
#ifdef __unix__
        std::vector<std::string> supportedFormats{"JSON", "CBOR"};
#elif ESP_PLATFORM
        std::vector<std::string> supportedFormats{"JSON"};
#elif __ZEPHYR__
        std::vector<std::string> supportedFormats{"JSON"};//TODO Zephyr
#endif
        ICloudioMessageFormat *messageFormat;
        ITransportLayer *transportLayer;
        ICloudioEndpointConfiguration *endpointConfiguration;

        Transaction *transaction;
        bool inTransaction = false;

        void
        set(const std::string &topic, std::queue<std::string> location, ICloudioMessageFormat *setMessageFormat,
            const std::string &payload);

    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP__CLOUDIOENDPOINT_H
