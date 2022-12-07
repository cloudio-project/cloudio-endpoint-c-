//
// Created by lucas on 06/12/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTETYPEEXCEPTION_H
#define CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTETYPEEXCEPTION_H

#include <iostream>

namespace cloudio {

    class CloudioAttributeTypeException : public std::runtime_error {
    private:
        std::string message;

    public:
        CloudioAttributeTypeException(const std::string &msg);
    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTETYPEEXCEPTION_H
