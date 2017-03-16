cmake_minimum_required (VERSION 2.6)
project (Paho_MQTT)

option(USE_ARCH_32 "build application with 32 bits " OFF) # OFF is the default


set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--no-as-needed -ldl")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -ldl")
set(CMAKE_CPPFLAGS "-fprofile-arcs -ftest-coverage " )
set(CMAKE_LDFLAGS " -fprofile-arcs")
set(CMAKE_CFLAGS "-fprofile-arcs -ftest-coverage " )




include_directories(${Paho_MQTT_SOURCE_DIR})
include_directories(${Paho_MQTT_SOURCE_DIR}/../include/gtest)
include_directories(${Paho_MQTT_SOURCE_DIR}/../include)

#include_directories(${Paho_MQTT_SOURCE_DIR}/../src/Paho_MQTT_c)
include_directories(${Paho_MQTT_SOURCE_DIR}/../src/paho.mqtt.c/src)

#include_directories(${Paho_MQTT_SOURCE_DIR}/../src/Paho_MQTT_cpp)
#include_directories(${Paho_MQTT_SOURCE_DIR}/../src/Paho_MQTT_cpp/mqtt)

include_directories(${Paho_MQTT_SOURCE_DIR}/../src/paho.mqtt.cpp/src)
include_directories(${Paho_MQTT_SOURCE_DIR}/../src/Paho_MQTT_cpp/src/mqtt)


file(GLOB Paho_MQTT_SRC
	#	"../src/Paho_MQTT_c/*.h"
	"../src/paho.mqtt.c/src/*.h"

	#	"../src/Paho_MQTT_cpp/*.h"
	"../src/paho.mqtt.cpp/src/mqtt/*.h"
	"*.h"
	"*.hpp"
	
	"*.c"
	"*.cpp"
)

add_executable(Paho_MQTT  ${Paho_MQTT_SRC})


if(USE_ARCH_32 )
	find_library(GTEST_LIBRARY gtest ~/workspace/OceansOfThings/NMEA_0183/lib_x86/googlemock/gtest) 
	find_library(MQTT_LIBRARY_C paho-mqtt3a HINTS ~/workspace/OceansOfThings/IoT_MQTT/lib_x86/MQTT/Paho_c)
	find_library(MQTT_LIBRARY_CPP mqttpp HINTS ~/workspace/OceansOfThings/IoT_MQTT/lib_x86/MQTT/Paho_cpp)
else()
	find_library(GTEST_LIBRARY gtest ~/workspace/OceansOfThings/IoT_Node/lib_x64/googlemock/gtest) 
	find_library(MQTT_LIBRARY_C paho-mqtt3a HINTS ~/workspace/OceansOfThings/IoT_Node/lib_x64/mqtt)
	find_library(MQTT_LIBRARY_CPP mqttpp HINTS ~/workspace/OceansOfThings/IoT_Node/lib_x64/mqtt)
endif(USE_ARCH_32)

TARGET_LINK_LIBRARIES(Paho_MQTT PUBLIC ${GTEST_LIBRARY} ${MQTT_LIBRARY_C} ${MQTT_LIBRARY_CPP} pthread)

