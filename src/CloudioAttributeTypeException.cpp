//
// Created by lucas on 06/12/22.
//

#include "../include/CloudioAttributeTypeException.h"

using namespace std;

namespace cloudio {

    CloudioAttributeTypeException::CloudioAttributeTypeException(const string &msg) : runtime_error(msg) {

    }
} // cloudio