//
// Created by lucas on 31/10/22.
//

#include "../include/InvalidPropertyException.h"

using namespace std;

namespace cloudio {
    InvalidPropertyException::InvalidPropertyException(const string &msg) : runtime_error(msg) {

    }
} // cloudio
