//
// Created by lucas on 10/02/2023.
//

#ifndef CLOUDIO_ENDPOINT_CPP__ITIMESTAMPMANAGER_H
#define CLOUDIO_ENDPOINT_CPP__ITIMESTAMPMANAGER_H

#include <stdint.h>

namespace cloudio {

    class ITimestampManager {
    public:

        virtual ~ITimestampManager() {}

        virtual int64_t getTimestamp() = 0;

    };
} // cloudio
#endif //CLOUDIO_ENDPOINT_CPP__ITIMESTAMPMANAGER_H
