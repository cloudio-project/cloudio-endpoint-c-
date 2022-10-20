//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_JSONNLOHMANNMESSAGEFORMAT_H
#define CLOUDIO_ENDPOINT_CPP_JSONNLOHMANNMESSAGEFORMAT_H

#include "ICloudioMessageFormat.h"
namespace cloudio {
    class JsonNlohmannMessageFormat : public ICloudioMessageFormat {

    public:
        JsonNlohmannMessageFormat();
        ~JsonNlohmannMessageFormat();

        char* serializeEndpoint(CloudioEndpoint endpoint);
        char* serializeNode(CloudioNode node);
        char* serializeAttribute(CloudioAttribute<int> attribute);
        char* serializeAttribute(CloudioAttribute<double> attribute);
        char* serializeAttribute(CloudioAttribute<bool> attribute);
        char* serializeAttribute(CloudioAttribute<string> attribute);



    };
}//cloudio


#endif //CLOUDIO_ENDPOINT_CPP_JSONNLOHMANNMESSAGEFORMAT_H
