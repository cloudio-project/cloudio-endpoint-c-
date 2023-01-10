//
// Created by lucas on 06/12/22.
//
#include "../include/CloudioAttributeConstraint.h"

namespace cloudio {
    std::string to_string(CloudioAttributeConstraint constraint) {
        switch (constraint) {
            case CloudioAttributeConstraint::Static:
                return "Static";
            case CloudioAttributeConstraint::Parameter:
                return "Parameter";
            case CloudioAttributeConstraint::Status:
                return "Status";
            case CloudioAttributeConstraint::SetPoint:
                return "SetPoint";
            case CloudioAttributeConstraint::Measure:
                return "Measure";
            default:
                return "Invalid";
        }
    }
} // cloudio