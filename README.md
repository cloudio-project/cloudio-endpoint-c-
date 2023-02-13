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

There is many way to install the JSON for Modern C++ libraries described here[git repository](https://github.com/nlohmann/json) and
[official website](https://json.nlohmann.me/integration/CMake/) using CMake.

However we recommend compiling it from source:
```
git clone https://github.com/nlohmann/json
cd json/
mkdir build && cd build
cmake ..
make
sudo make install
```


##### cpp-properties

You will need to clone the library in the same parent folder as the cloud.iO cpp library to make the compiling work.

Execute ```./build.sh``` as described in the [git repository](https://github.com/fredyw/cpp-properties/). The script
CMake as per the other libraries. The library is then used in the cloudio-endpoint-cpp CMake project.

#### Uses with ESP32
On ESP32, The cloudio-endpoint-cplusplus uses only esp-idf components:

- [cJSON](https://github.com/DaveGamble/cJSON)

## Use the library in your CMake project (with operating system)

Clone this git repository and build the CMake project.
Once built, you can integrate the library with its dependency in your own CMake project. You can follow the example file
of in the CMakeExample folder.

## Use the library as esp-idf component
Clone this git repository and save it in your esp-idf components project folder. You will need to use the 
CMakeLists_ESP_32_Component.txt cmake file. Replace the CMakeLists.txt by the CMakeLists_ESP_32_Component.txt file. 

Your esp-idf project will need to manage the network to make the cloudio-endpoint-cplusplus mqtt works. With ESP-32 we 
don't use filesystem to store the certificate or the properties, the alternative is the following:

### Properties
The Endpoint can be configured by using Maps with the help of the MapEndpointConfiguration class and give it to the 
endpoint at its creation:
 ``` c++
std::map<std::string, std::string> propertiesMap =
{ { "ch.hevs.cloudio.endpoint.keepAliveInterval", "5" }, {
"ch.hevs.cloudio.endpoint.ssl.verifyHostname", "false" }, {
"ch.hevs.cloudio.endpoint.uuid",
"your-endpoint-uuid" }, {
"ch.hevs.cloudio.endpoint.hostUri",
"mqtts://your-cloudio-server:port" }, {
"ch.hevs.cloudio.endpoint.messageFormat", "JSON" } };
MapEndpointConfiguration *customMapConfiguration =
new MapEndpointConfiguration(propertiesMap);

CloudioEndpoint myEndpoint = CloudioEndpoint("Test", nullptr, nullptr,
			customMapConfiguration);
```

### Certificates

We use custom esp-idf CMake command ```target_add_binary_data``` to insert file content (PEM certificate content) inside 
the *.elf binary image.

The certificate files names needs to be respected:
- caCertificate.PEM
- clientCertificate.PEM
- clientPrivateKey.PEM

In the main esp-idf CMakeLists.txt file, you need to add :
```cmake
target_add_binary_data(${CMAKE_PROJECT_NAME}.elf "main/clientCertificate.PEM" TEXT)
target_add_binary_data(${CMAKE_PROJECT_NAME}.elf "main/clientPrivateKey.PEM" TEXT)
target_add_binary_data(${CMAKE_PROJECT_NAME}.elf "main/caCertificate.PEM" TEXT)
```
The structure of the Project should look like that:
```
esp-idf-project/
├─ components/
│  ├─ cloudio-endpoint-cpp/
│  │  ├─ include/
│  │  ├─ src/
│  │  ├─ CMakeLists.txt
├─ main/
│  ├─ build/
│  ├─ app_main.cpp
│  ├─ caCertificate.PEM
│  ├─ clientCertificate.PEM
│  ├─ clientPrivateKey.PEM
│  ├─ CMakeListst.txt
├─ CMakeLists.txt
├─ sdkconfig
```