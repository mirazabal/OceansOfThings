cmake_minimum_required (VERSION 2.6)
project (NMEA_0183_sensor)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--no-as-needed -ldl")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -ldl -Wall")
set(CMAKE_CPPFLAGS "-fprofile-arcs -ftest-coverage " )
set(CMAKE_LDFLAGS " -fprofile-arcs")
set(CMAKE_CFLAGS "-fprofile-arcs -ftest-coverage " )


#include_directories(${NMEA_0183_sensor_SOURCE_DIR})

include_directories(~/workspace/OceansOfThings/IoT_Node/include)
include_directories(~/workspace/OceansOfThings/IoT_Node/include/gtest)

include_directories(~/workspace/OceansOfThings/IoT_Node/sensors/GPS/NMEA_0183)
include_directories(~/workspace/OceansOfThings/IoT_Node/sensors/GPS/NMEA_0183/gpgll/)

#include_directories(~/workspace/OceansOfThings/IoT_Node/sensors/GPS/NMEA_0183/gpgga)
#include_directories(~/workspace/OceansOfThings/IoT_Node/sensors/GPS/NMEA_0183/gprmc)
#include_directories(~/workspace/OceansOfThings/IoT_Node/sensors/GPS/NMEA_0183/src)

file(GLOB NMEA_0183_sensor_SRC
    "*.h"
	"../*.h"
	
	"../GPS/NMEA_0183/src/*.h"
	"../GPS/NMEA_0183/src/*.c"
	
	"../GPS/NMEA_0183/gpgll/*.h"
	"../GPS/NMEA_0183/gpgll/*.c"

	"../GPS/NMEA_0183/gpgga/*.h"
	"../GPS/NMEA_0183/gpgga/*.c"

	"../GPS/NMEA_0183/gprmc*.h"
	"../GPS/NMEA_0183/gprmc/*.c"

	"../../communication/serial/*.h"
	"../../communication/serial/*.cpp"
	
	"*.hpp"
	"*.c"
	"*.cpp"
	"../*.cpp"
)

add_executable(NMEA_0183_sensor ${NMEA_0183_sensor_SRC})


find_library(GTEST_LIBRARY gtest ~/workspace/OceansOfThings/IoT_Node/lib_x64/googlemock/gtest) 

find_library(BOOST_SYSTEM_LIBRARY boost_system HINTS ~/boost_1_63_0/stage/lib)
find_library(BOOST_THREAD_LIBRARY boost_thread HINTS ~/boost_1_63_0/stage/lib)


TARGET_LINK_LIBRARIES(NMEA_0183_sensor PUBLIC ${GTEST_LIBRARY} ${BOOST_SYSTEM_LIBRARY} ${BOOST_THREAD_LIBRARY}  pthread)


