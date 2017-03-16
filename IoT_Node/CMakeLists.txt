cmake_minimum_required (VERSION 2.6)
project (iot_node)

ENABLE_TESTING()

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--no-as-needed -ldl")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -ldl -Wall ")
set(CMAKE_CPPFLAGS "-fprofile-arcs -ftest-coverage " )
set(CMAKE_LDFLAGS " -fprofile-arcs")
set(CMAKE_CFLAGS "-fprofile-arcs -ftest-coverage " )

include_directories(${iot_node_SOURCE_DIR})
include_directories(~/workspace/OceansOfThings/IoT_Node/include)
include_directories(~/workspace/OceansOfThings/IoT_Node/include/gtest)

include_directories(~/workspace/OceansOfThings/IoT_Node/sensors)
include_directories(~/workspace/OceansOfThings/IoT_Node/sensors/GPS)

include_directories(~/workspace/OceansOfThings/IoT_Node/sensors/GPS/NMEA_0183)
include_directories(~/workspace/OceansOfThings/IoT_Node/sensors/connectivity/mqtt/src)
include_directories(~/workspace/OceansOfThings/IoT_Node/sensors/connectivity/mqtt/Paho_MQTT_Unit_Test_Async)


include_directories(~/boost_1_63_0/boost)

file(GLOB iot_node_SRC
	
	"sensors/GPS/NMEA_0183/src/*.h"
	"sensors/GPS/NMEA_0183/src/*.c"
	"sensors/GPS/NMEA_0183/gpgga/*.h"
	"sensors/GPS/NMEA_0183/gpgga/*.c"
	"sensors/GPS/NMEA_0183/gpgll/*.h"
	"sensors/GPS/NMEA_0183/gpgll/*.c"
	"sensors/GPS/NMEA_0183/gprmc/*.h"
	"sensors/GPS/NMEA_0183/gprmc/*.c"

	"sensors/GPS/*.h"
	"sensors/GPS/*.cpp"

	"sensors/*.h"
	"sensors/*.cpp"


	"communication/serial/*.h"
	"communication/serial/*.cpp"


	"connectivity/mqtt/*.h"
	"connectivity/mqtt/*.cpp"

	"connectivity/mqtt/src/paho.mqtt.c/src/*.h"
	"connectivity/mqtt/src/paho.mqtt.c/src/*.cpp"

	"connectivity/mqtt/src/paho.mqtt.cpp/src/*.h"
	"connectivity/mqtt/src/paho.mqtt.cpp/src/*.cpp"

	"connectivity/mqtt/Paho_MQTT_Unit_Test_Async/*.h"
	"connectivity/mqtt/Paho_MQTT_Unit_Test_Async/*.cpp"

	"*.h"
    "*.cpp"
)

SET(CMAKE_EXE_LINKER_FLAGS="-fprofile-arcs -ftest-coverage")


add_executable(iot_node ${iot_node_SRC})
find_library(MQTT_LIBRARY_C paho-mqtt3a HINTS ~/workspace/OceansOfThings/IoT_Node/lib_x64/mqtt)
find_library(MQTT_LIBRARY_CPP mqttpp HINTS ~/workspace/OceansOfThings/IoT_Node/lib_x64/mqtt)
find_library(BOOST_SYSTEM_LIBRARY boost_system HINTS ~/boost_1_63_0/stage/lib)
find_library(BOOST_THREAD_LIBRARY boost_thread HINTS ~/boost_1_63_0/stage/lib)
find_library(GTEST_LIBRARY gtest ~/workspace/OceansOfThings/IoT_Node/lib_x64/googlemock/gtest)

TARGET_LINK_LIBRARIES(iot_node PUBLIC ${GTEST_LIBRARY} ${MQTT_LIBRARY_C} ${MQTT_LIBRARY_CPP}  ${BOOST_SYSTEM_LIBRARY} ${BOOST_THREAD_LIBRARY} pthread )


