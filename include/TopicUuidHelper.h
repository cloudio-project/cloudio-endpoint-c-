// Created by lucas on 02/11/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_TOPICUUIDHELPER_H
#define CLOUDIO_ENDPOINT_CPP_TOPICUUIDHELPER_H

#include "../include/ICloudioAttributeContainer.h"
#include "../include/ICloudioObjectContainer.h"
#include "../include/ICloudioNodeContainer.h"

#include <string>
#include <queue>

namespace cloudio {

    class CloudioAttribute;

    std::string getAttributeTopic(CloudioAttribute *attribute);

    std::string getAttributeContainerTopic(ICloudioAttributeContainer *attributeContainer);

    std::string getObjectContainerTopic(ICloudioObjectContainer *objectContainer);

    std::string getNodeContainerTopic(ICloudioNodeContainer *nodeContainer);

    std::queue<std::string> split(const std::string &s, const std::string &delimiter);

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_TOPICUUIDHELPER_H
