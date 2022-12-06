//
// Created by lucas on 20/10/22.
//

#ifndef CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTECONSTRAINT_H
#define CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTECONSTRAINT_H

namespace cloudio {

    enum CloudioAttributeConstraint {
        Static,
        Parameter,
        Status,
        SetPoint,
        Measure
    };

    const char *CloudioAttributeConstraintToString(CloudioAttributeConstraint constraint);
} // cloudio

#endif //CLOUDIO_ENDPOINT_CPP_CLOUDIOATTRIBUTECONSTRAINT_H
