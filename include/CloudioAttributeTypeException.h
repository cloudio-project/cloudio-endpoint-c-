//
// Created by lucas on 06/12/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTETYPEEXCEPTION_H
#define CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTETYPEEXCEPTION_H

#include <iostream>

namespace cloudio {

class CloudioAttributeTypeException : public std::exception {
    private:
        std::string message;

    public:
        CloudioAttributeTypeException(const std::string &msg);

        // exception interface
        const char *what();

    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTETYPEEXCEPTION_H
