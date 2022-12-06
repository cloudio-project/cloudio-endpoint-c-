//
// Created by lucas on 05/12/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_CLOUDIOMESSAGEFORMATFACTORY_H
#define CLOUDIO_ENDPOINT_CPP_CLOUDIOMESSAGEFORMATFACTORY_H

#include <string>

using namespace std;

namespace cloudio {

    class ICloudioMessageFormat;

    class CloudioMessageFormatFactory {

    public:

        static ICloudioMessageFormat *messageFormat(char messageFormatId);

        static ICloudioMessageFormat *messageFormat(const string &messageFormatName);
    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_CLOUDIOMESSAGEFORMATFACTORY_H
