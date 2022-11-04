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

    class CloudioEndpoint : public ICloudioNodeContainer {

    public:
        CloudioEndpoint(string uuidOrAppName, ICloudioMessageFormat *cloudioMessageFormat = nullptr,
                        ITransportLayer *transportLayer = nullptr);

        ~CloudioEndpoint();

        string getVersion();

        list<CloudioNode *> getNodes();

        list<string> getSupportedFormats();

        string getName();

        void addNode(CloudioNode *node);

        void attributeHasChangedByEndpoint(CloudioAttribute *attribute);

    private:
        string uuid;
        string version = "v0.2";
        list<CloudioNode *> nodes;
        list<string> supportedFormats{"JSON"};
        ICloudioMessageFormat *messageFormat;
        ITransportLayer *transportLayer;

    };

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP__CLOUDIOENDPOINT_H
