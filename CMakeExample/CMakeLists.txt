cmake_minimum_required(VERSION 3.23)
project(usingLib)

set(CMAKE_CXX_STANDARD 14)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(libcppproperties REQUIRED)
find_package(libcloudio REQUIRED)

add_executable(usingLib main.cpp)

include(FindPkgConfig)

include_directories(${CLOUDIO_INCLUDE_DIR} ${CPP_PROPERTIES_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} ${CLOUDIO_LIBRARY} ${CPP_PROPERTIES_LIBRARY} paho-mqtt3as paho-mqttpp3 )
