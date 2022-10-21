# cloudio-endpoint-cplusplus

## Requirements

### Libraries

#### Uses with operating system
The cloudio-endpoint-cplusplus uses 3 libraries when deployed on device with an operating system:

- [Eclipse Paho MQTT C++ Client Library](https://github.com/eclipse/paho.mqtt.cpp)
- [JSON for Modern C++](https://github.com/nlohmann/json)
- [cpp-properties](https://github.com/fredyw/cpp-properties/)

##### Eclipse Paho MQTT C++ Client Library

Follow the Eclipse instruction on how to install from the [git repository](https://github.com/eclipse/paho.mqtt.cpp) 
using CMake. 
**Build the library with PAHO_WITH_SSL!** The library is then used in the cloudio-endpoint-cpp CMake project .

##### JSON for Modern C++

Follow the instruction on how to install from the [git repository](https://github.com/nlohmann/json) and 
[official website](https://json.nlohmann.me/integration/CMake/) using CMake.


##### cpp-properties

Execute ```./build.sh``` as described in the [git repository](https://github.com/fredyw/cpp-properties/). The script 
CMake as per the other libraries. The library is then used in the cloudio-endpoint-cpp CMake project.

## Use the library in your CMake project

Clone this git repository and build the CMake project.
Once built, you can integrate the library with its dependency in your own CMake project. You can follow the example file 
of in the CMakeExample folder. 