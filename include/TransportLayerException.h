//
// Created by lucas on 04/11/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_TRANSPORTLAYEREXCEPTION_H
#define CLOUDIO_ENDPOINT_CPP_TRANSPORTLAYEREXCEPTION_H

#include <iostream>

using namespace std;

namespace cloudio {

    class TransportLayerException : public exception {
    private:
        string message;

    public:
        TransportLayerException(const string &msg);

        // exception interface
        const char *what();

    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_TRANSPORTLAYEREXCEPTION_H
