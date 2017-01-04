cmake_minimum_required (VERSION 2.6)
project (GPRMC)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--no-as-needed -ldl")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -ldl -fprofile-arcs -ftest-coverage")
set(CMAKE_CPPFLAGS "-fprofile-arcs -ftest-coverage " )
set(CMAKE_LDFLAGS " -fprofile-arcs")
set(CMAKE_CFLAGS "-fprofile-arcs -ftest-coverage " )

include_directories(${GPRMC_SOURCE_DIR})
include_directories(~/workspace/NMEA_0183/include/gtest)
include_directories(${GPRMC_SOURCE_DIR}/../include)
include_directories(${GPRMC_SOURCE_DIR}/../src)

SET(CMAKE_EXE_LINKER_FLAGS="-fprofile-arcs -ftest-coverage")


file(GLOB GPRMC_SRC
    "*.h"
	"../src/*.h"
	"*.c"
	"../src/*.c"
	"*.hpp"
    "*.cpp"
)

add_executable(GPRMC ${GPRMC_SRC})

find_library(GTEST_LIBRARY gtest ~/workspace/NMEA_0183/lib_x86/googlemock/gtest) 

TARGET_LINK_LIBRARIES(GPRMC PUBLIC ${GTEST_LIBRARY} pthread)

