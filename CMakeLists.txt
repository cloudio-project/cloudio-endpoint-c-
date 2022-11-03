cmake_minimum_required(VERSION 3.23)
project(cloudio_endpoint_cpp)

set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(libcppproperties REQUIRED)

find_package(nlohmann_json 3.2.0 REQUIRED)

add_library(cloudio_endpoint_cpp
        include/CloudioAttribute.h
        include/CloudioNode.h
        include/CloudioEndpoint.h
        include/ICloudioEndpointConfiguration.h
        include/ICloudioMessageFormat.h
        include/JsonNlohmannMessageFormat.h
        include/PropertiesEndpointConfiguration.h
        include/CloudioAttributeConstraint.h
        include/CloudioObject.h
        include/CloudioAttributeType.h
        include/ITransportLayer.h
        include/PahoMqttCppTransportLayer.h
        include/InvalidPropertyException.h
        include/CloudioEndpointPropertyConstants.h
        include/ICloudioAttributeContainer.h
        include/ICloudioObjectContainer.h
        include/ICloudioNodeContainer.h
        include/TopicUuidHelper.h
        include/INamedItem.h
        include/CloudioAttributeConstrainException.h
        src/CloudioAttribute.cpp
        src/CloudioNode.cpp
        src/CloudioEndpoint.cpp
        src/JsonNlohmannMessageFormat.cpp
        src/PropertiesEndpointConfiguration.cpp
        src/CloudioObject.cpp
        src/PahoMqttCppTransportLayer.cpp
        src/InvalidPropertyException.cpp
        src/TopicUuidHelper.cpp
        src/CloudioAttributeConstrainException.cpp)

include_directories(${CPP_PROPERTIES_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${CPP_PROPERTIES_LIBRARY} paho-mqtt3as paho-mqttpp3)
