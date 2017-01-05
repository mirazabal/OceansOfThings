cmake_minimum_required (VERSION 2.6)
project (NMEA_0183_sensor)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--no-as-needed -ldl")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -ldl")
set(CMAKE_CPPFLAGS "-fprofile-arcs -ftest-coverage " )
set(CMAKE_LDFLAGS " -fprofile-arcs")
set(CMAKE_CFLAGS "-fprofile-arcs -ftest-coverage " )



include_directories(${NMEA_0183_sensor_SOURCE_DIR})

include_directories(~/workspace/OceansOfThings/IoT_Node/include)
include_directories(~/workspace/OceansOfThings/IoT_Node/include/gtest)

include_directories(${NMEA_0183_sensor_SOURCE_DIR}/NMEA_0183)
include_directories(${NMEA_0183_sensor_SOURCE_DIR}/NMEA_0183/gpgga)
include_directories(${NMEA_0183_sensor_SOURCE_DIR}/NMEA_0183/gpgll)
include_directories(${NMEA_0183_sensor_SOURCE_DIR}/NMEA_0183/gprmc)

include_directories(${NMEA_0183_sensor_SOURCE_DIR}/NMEA_0183/src)



file(GLOB NMEA_0183_sensor_SRC
    "*.h"
	"../*.h"
	"gpgga/*.h"
	"gpgll/*.h"
	"gpgrmc/*.h"
	"src/*.h"
	"*.hpp"
	"*.c"
    "gpgga/*.c"
	"gpgll/*.c"
	"gprmc/*.c"
	"src/*.c"
	"*.cpp"
	"../*.cpp"
)

add_executable(NMEA_0183_sensor ${NMEA_0183_sensor_SRC})


find_library(GTEST_LIBRARY gtest ~/workspace/OceansOfThings/IoT_Node/lib_x64/googlemock/gtest) 

TARGET_LINK_LIBRARIES(NMEA_0183_sensor PUBLIC ${GTEST_LIBRARY} pthread)


