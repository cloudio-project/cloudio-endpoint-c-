/*
 * CJsonMessageFormat.h
 *
 *  Created on: 7 Feb 2023
 *      Author: Lucas Bonvin
 */
#ifdef ESP_PLATFORM
#ifndef COMPONENTS_CLOUDIO_ENDPOINT_CPP_INCLUDE_CJSONMESSAGEFORMAT_H_
#define COMPONENTS_CLOUDIO_ENDPOINT_CPP_INCLUDE_CJSONMESSAGEFORMAT_H_

#include "ICloudioMessageFormat.h"
#include "CloudioObject.h"

#include "cJSON.h"

namespace cloudio {

    class CJsonMessageFormat : public ICloudioMessageFormat{
    public:
        CJsonMessageFormat();
        virtual ~CJsonMessageFormat();

        // ICloudioMessageFormat interface
        std::string serializeEndpoint(CloudioEndpoint *endpoint);

        std::string serializeNode(CloudioNode *node);

        std::string serializeAttribute(CloudioAttribute *attribute);

        std::string serializeDidSetAttribute(CloudioAttribute *attribute, const std::string &correlationID);

        void deserializeAttribute(const std::string &payload, CloudioAttribute *attribute);

        std::string deserializeSetAttribute(const std::string &payload, CloudioAttribute *attribute);

    private:
        static cJSON * jsonSerializeEndpoint(CloudioEndpoint *endpoint);

        static cJSON * jsonSerializeNode(CloudioNode *node);

        static cJSON * jsonSerializeObject(CloudioObject *object);

        static cJSON * jsonSerializeAttribute(CloudioAttribute *attribute);
    };
} // cloudio
#endif /* COMPONENTS_CLOUDIO_ENDPOINT_CPP_INCLUDE_CJSONMESSAGEFORMAT_H_ */
#endif //ESP_PLATFORM