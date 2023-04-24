//
// Created by lucas on 06/03/23.
//

#include "../include/Transaction.h"

using namespace std;

namespace cloudio {

    Transaction::Transaction() {}

    std::map<std::string, CloudioAttribute *> Transaction::getAttributes(){
        return this->attributes;
    }

    void Transaction::addAttribute(CloudioAttribute *attribute) {

        string attributeTopic = getAttributeTopic(attribute);

        if(this->attributes.find(attributeTopic) == this->attributes.end())
        {
            this->attributes[attributeTopic] = attribute;
        }
    }

    void Transaction::clearAttributes() {
        this->attributes.clear();
    }
} /* namespace cloudio */