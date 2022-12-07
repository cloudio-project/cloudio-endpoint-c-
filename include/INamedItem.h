//
// Created by lucas on 02/11/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_INAMEDITEM_H
#define CLOUDIO_ENDPOINT_CPP_INAMEDITEM_H

#include <string>

namespace cloudio {

    class INamedItem {
    public:

        virtual ~INamedItem() {}

        virtual std::string getName() = 0;
    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_INAMEDITEM_H
