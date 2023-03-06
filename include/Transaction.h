//
// Created by lucas on 06/03/23.
//

#ifndef CLOUDIO_ENDPOINT_CPP_TRANSACTION_H
#define CLOUDIO_ENDPOINT_CPP_TRANSACTION_H

#include <map>

#include "../include/TopicUuidHelper.h"

namespace cloudio {
    class Transaction {
    public:

        Transaction();

        std::map<std::string, CloudioAttribute *> getAttributes();

        void addAttribute(CloudioAttribute *attribute);

        void clearAttributes();

    private:
        std::map<std::string, CloudioAttribute *> attributes;
    };
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_TRANSACTION_H
