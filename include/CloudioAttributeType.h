//
// Created by lucas on 21/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTETYPE_H
#define CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTETYPE_H

#include <string>

namespace cloudio {

    enum CloudioAttributeType {
        Invalid,
        Boolean,
        Integer,
        Number,
        String
    };

    std::string to_string(CloudioAttributeType constraint);
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTETYPE_H
