#Copyright (c) Microsoft. All rights reserved.
#Licensed under the MIT license. See LICENSE file in the project root for full license information.

#this is CMakeLists.txt for iothub_client_sample_mqtt
cmake_minimum_required(VERSION 2.8.11)

if(WIN32)
    message(FATAL_ERROR "This CMake file is only support Linux builds!")
endif()

set(AZUREIOT_INC_FOLDER ".." "/usr/include/azureiot" "/usr/include/azureiot/inc")

include_directories(${AZUREIOT_INC_FOLDER})
include_directories(/home/byte/workspace/IoTHack/azure-iot-sdk-c/iothub_client/inc/)
include_directories(/home/byte/workspace/IoTHack/azure-iot-sdk-c/c-utility/inc/)





set(iothub_client_sample_mqtt_c_files
    ../iothub_client_sample_mqtt.c
)

set(iothub_client_sample_mqtt_h_files
    ../iothub_client_sample_mqtt.h
)

add_executable(iothub_client_sample_mqtt ${iothub_client_sample_mqtt_c_files} ${iothub_client_sample_mqtt_h_files})

find_library(IOT_HUB_CLIENT iothub_client HINTS ~/workspace/IoTHack/azure-iot-sdk-c/build/iothub_client/)
find_library(IOT_HUB_CLIENT_MQTT_TRANSPORT iothub_client_mqtt_transport HINTS ~/workspace/IoTHack/azure-iot-sdk-c/build/iothub_client/)
find_library(IOT_UMQTT umqtt HINTS ~/workspace/IoTHack/azure-iot-sdk-c/build/umqtt/)
find_library(IOT_AZIOT_SHARED_UTIL aziotsharedutil HINTS ~/workspace/IoTHack/azure-iot-sdk-c/build/c-utility/)


target_link_libraries(iothub_client_sample_mqtt PUBLIC 
	${IOT_HUB_CLIENT}
	${IOT_HUB_CLIENT_MQTT_TRANSPORT}
	${IOT_AZIOT_SHARED_UTIL}
	${IOT_UMQTT}
    pthread
    curl
    ssl
    crypto
    m
)
