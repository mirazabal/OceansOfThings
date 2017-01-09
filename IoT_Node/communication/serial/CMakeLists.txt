cmake_minimum_required (VERSION 2.6)
project (serial)


ENABLE_TESTING()

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--no-as-needed -ldl")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -ldl")
set(CMAKE_CPPFLAGS "-fprofile-arcs -ftest-coverage " )
set(CMAKE_LDFLAGS " -fprofile-arcs")
set(CMAKE_CFLAGS "-fprofile-arcs -ftest-coverage " )


include_directories(${serial_SOURCE_DIR})
include_directories(~/workspace/OceansOfThings/IoT_Node/include)
include_directories(~/workspace/OceansOfThings/IoT_Node/include/gtest)

include_directories(~/boost_1_63_0/boost)



file(GLOB serial_SRC
    "*.h"
    "*.cpp"
)

SET(CMAKE_EXE_LINKER_FLAGS="-fprofile-arcs -ftest-coverage")


add_executable(serial ${serial_SRC})

find_library(BOOST_SYSTEM_LIBRARY boost_system HINTS ~/boost_1_63_0/stage/lib)
find_library(BOOST_THREAD_LIBRARY boost_thread HINTS ~/boost_1_63_0/stage/lib)

find_library(GTEST_LIBRARY gtest ~/workspace/OceansOfThings/IoT_Node/lib_x64/googlemock/gtest)

TARGET_LINK_LIBRARIES(serial PUBLIC ${GTEST_LIBRARY} ${BOOST_SYSTEM_LIBRARY} ${BOOST_THREAD_LIBRARY} pthread )


