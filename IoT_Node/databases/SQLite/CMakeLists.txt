cmake_minimum_required (VERSION 2.6)
project (SQLite)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--no-as-needed -ldl")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -ldl -fprofile-arcs -ftest-coverage")
set(CMAKE_CPPFLAGS "-fprofile-arcs -ftest-coverage " )
set(CMAKE_LDFLAGS " -fprofile-arcs")
set(CMAKE_CFLAGS "-fprofile-arcs -ftest-coverage " )


include_directories(${SQLite_SOURCE_DIR})
include_directories(~/workspace/NMEA_0183/SQlite/sqlite-amalgamation-3150200/)
include_directories(~/workspace/NMEA_0183/include/gtest/)
include_directories(~/workspace/NMEA_0183/include)
include_directories(~/workspace/NMEA_0183/SQlite/sqlite_src)


SET(CMAKE_EXE_LINKER_FLAGS="-fprofile-arcs -ftest-coverage")


file(GLOB SQLite_SRC
    "*.h"
	"sqlite_src/*.h"
	"sqlite_src/*.c"
	"*.c"
	"*.hpp"
    "*.cpp"
)

add_executable(SQLite ${SQLite_SRC})

find_library(GTEST_LIBRARY gtest ~/workspace/NMEA_0183/lib_x86/googlemock/gtest) 

TARGET_LINK_LIBRARIES(SQLite PUBLIC ${GTEST_LIBRARY} pthread)


