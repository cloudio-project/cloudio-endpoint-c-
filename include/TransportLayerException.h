//
// Created by lucas on 04/11/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_TRANSPORTLAYEREXCEPTION_H
#define CLOUDIO_ENDPOINT_CPP_TRANSPORTLAYEREXCEPTION_H

#include <iostream>

namespace cloudio {

class TransportLayerException : public std::exception {
    private:
        std::string message;

    public:
        TransportLayerException(const std::string &msg);

        // exception interface
        const char *what();

    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_TRANSPORTLAYEREXCEPTION_H
