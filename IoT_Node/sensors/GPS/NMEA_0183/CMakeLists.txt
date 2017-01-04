cmake_minimum_required (VERSION 2.6)
project (NMEA_0183)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--no-as-needed -ldl")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -ldl")
set(CMAKE_CPPFLAGS "-fprofile-arcs -ftest-coverage " )
set(CMAKE_LDFLAGS " -fprofile-arcs")
set(CMAKE_CFLAGS "-fprofile-arcs -ftest-coverage " )



include_directories(${NMEA_0183_SOURCE_DIR})
include_directories(~/workspace/NMEA_0183/include/gtest)
include_directories(${NMEA_0183_SOURCE_DIR}/include)

include_directories(${NMEA_0183_SOURCE_DIR}/gpgga)
include_directories(${NMEA_0183_SOURCE_DIR}/gpgll)
include_directories(${NMEA_0183_SOURCE_DIR}/gprmc)

include_directories(${NMEA_0183_SOURCE_DIR}/SQLite)
include_directories(${NMEA_0183_SOURCE_DIR}/src)



file(GLOB NMEA_0183_SRC
    "*.h"
	"gpgga/*.h"
	"gpgll/*.h"
	"gpgrmc/*.h"
	"src/*.h"
	"SQLite/*.h"
	"SQLite/sqlite_src/*.h"
	"*.hpp"
	"*.c"
    "gpgga/*.c"
	"gpgll/*.c"
	"gprmc/*.c"
	"src/*.c"
	"SQLite/*.c"
	"SQLite/sqlite_src/*.c"
	"*.cpp"
)

add_executable(NMEA_0183 ${NMEA_0183_SRC})

#find_library(GPRMC_LIBRARY gprmc HINTS /home/mikel/workspace/NMEA_0183/libnmea/examples/include/nmea)

#TARGET_LINK_LIBRARIES(Minimum PUBLIC ${NMEA_LIBRARY} ${GPGGA_LIBRARY}   ${GPGLL_LIBRARY}  ${GPRMC_LIBRARY}  pthread )

find_library(GTEST_LIBRARY gtest ~/workspace/NMEA_0183/lib_x86/googlemock/gtest) 

TARGET_LINK_LIBRARIES(NMEA_0183 PUBLIC ${GTEST_LIBRARY} pthread)


