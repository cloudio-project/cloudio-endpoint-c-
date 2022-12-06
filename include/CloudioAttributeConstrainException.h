//
// Created by lucas on 02/11/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTECONSTRAINEXCEPTION_H
#define CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTECONSTRAINEXCEPTION_H

#include <iostream>

using namespace std;

namespace cloudio {

    class CloudioAttributeConstrainException : public exception {
    private:
        string message;

    public:
        CloudioAttributeConstrainException(const string &msg);

        const char *what();

    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTECONSTRAINEXCEPTION_H
