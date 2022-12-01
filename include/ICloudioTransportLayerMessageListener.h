//
// Created by lucas on 01/12/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_ICLOUDIOTRANSPORTLAYERMESSAGELISTENER_H
#define CLOUDIO_ENDPOINT_CPP_ICLOUDIOTRANSPORTLAYERMESSAGELISTENER_H

#include <string>

using namespace std;

namespace cloudio {

    class ICloudioTransportLayerMessageListener {
    public:
        virtual void messageArrived(string topic, string payload) = 0;
    };

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_ICLOUDIOTRANSPORTLAYERMESSAGELISTENER_H
