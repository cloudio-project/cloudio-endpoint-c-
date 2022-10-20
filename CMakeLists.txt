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
        src/CloudioAttribute.cpp
        src/CloudioNode.cpp
        src/CloudioEndpoint.cpp
        src/JsonNlohmannMessageFormat.cpp
        include/JsonNlohmannMessageFormat.h
        src/PropertiesEndpointConfiguration.cpp
        include/PropertiesEndpointConfiguration.h
        )

include_directories(${CPP_PROPERTIES_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${TEST_LIBRARY} paho-mqtt3as paho-mqttpp3 nlohmann_json::nlohmann_json libcppproperties)
