//
// Created by lucas on 02/11/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTECONSTRAINEXCEPTION_H
#define CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTECONSTRAINEXCEPTION_H

#include <iostream>

namespace cloudio {

class CloudioAttributeConstrainException : public std::exception {
    private:
        std::string message;

    public:
        CloudioAttributeConstrainException(const std::string &msg);

        // exception interface
        const char *what();

    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTECONSTRAINEXCEPTION_H
