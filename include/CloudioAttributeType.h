//
// Created by lucas on 21/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTETYPE_H
#define CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTETYPE_H

namespace cloudio {

    enum CloudioAttributeType {
        Invalid,
        Boolean,
        Integer,
        Number,
        String
    };

    const char *CloudioAttributeTypeToString(CloudioAttributeType constraint);
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTETYPE_H
