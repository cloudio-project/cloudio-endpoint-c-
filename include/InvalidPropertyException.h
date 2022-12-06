//
// Created by lucas on 31/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_INVALIDPROPERTYEXCEPTION_H
#define CLOUDIO_ENDPOINT_CPP_INVALIDPROPERTYEXCEPTION_H

#include <iostream>

using namespace std;

namespace cloudio {
    class InvalidPropertyException : public exception {
    private:
        string message;

    public:
        InvalidPropertyException(const string &msg);

        const char *what();

    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_INVALIDPROPERTYEXCEPTION_H
