//
// Created by lucas on 31/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_INVALIDPROPERTYEXCEPTION_H
#define CLOUDIO_ENDPOINT_CPP_INVALIDPROPERTYEXCEPTION_H

#include <iostream>
#include <string>

namespace cloudio {
class InvalidPropertyException : public std::exception {
    private:
        std::string message;

    public:
        InvalidPropertyException(const std::string &msg);

        const char *what();

    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_INVALIDPROPERTYEXCEPTION_H
