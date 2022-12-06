// Created by lucas on 02/11/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_TOPICUUIDHELPER_H
#define CLOUDIO_ENDPOINT_CPP_TOPICUUIDHELPER_H

#include "../include/ICloudioAttributeContainer.h"
#include "../include/ICloudioObjectContainer.h"
#include "../include/ICloudioNodeContainer.h"

#include <string>
#include <list>

using namespace std;

namespace cloudio {

    class CloudioAttribute;

    string getAttributeTopic(CloudioAttribute *attribute);

    string getAttributeContainerTopic(ICloudioAttributeContainer *attributeContainer);

    string getObjectContainerTopic(ICloudioObjectContainer *objectContainer);

    string getNodeContainerTopic(ICloudioNodeContainer *nodeContainer);

    list<string> split(const string &s, const string &delimiter);

} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_TOPICUUIDHELPER_H
