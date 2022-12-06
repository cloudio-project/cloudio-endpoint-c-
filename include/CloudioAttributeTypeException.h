//
// Created by lucas on 06/12/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTETYPEEXCEPTION_H
#define CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTETYPEEXCEPTION_H

#include <iostream>

using namespace std;

namespace cloudio {

    class CloudioAttributeTypeException : public exception {
    private:
        string message;

    public:
        CloudioAttributeTypeException(const string &msg);

        // exception interface
        const char *what();

    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTETYPEEXCEPTION_H
