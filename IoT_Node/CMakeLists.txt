cmake_minimum_required (VERSION 2.6)
project (Node)
#SET(PROJECT_TEST_NAME Node)


ENABLE_TESTING()


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

option(USE_ARM "build application with ARM" ON) # OFF is the default

if(USE_ARM)	
	message("ARM compiler selected" ) 
	set(CMAKE_CXX_COMPILER "/home/mikel/rpi/tools/arm-bcm2708/gcc-linaro-arm-linux-gnueabihf-raspbian/bin/arm-linux-gnueabihf-g++")
	message("Debug mode selected" ) 
	#set (CMAKE_BUILD_TYPE = Debug)

	SET(CMAKE_CXX_FLAGS="-g -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -fprofile-arcs -ftest-coverage")
	 
	SET(CMAKE_C_FLAGS="-g -O0 -Wall -W -fprofile-arcs -ftest-coverage")
else()
	add_definitions(-DFAKE_CAMERA)
endif(USE_ARM)


include_directories(${Node_SOURCE_DIR})
include_directories(${Node_SOURCE_DIR}/include)
include_directories(${Node_SOURCE_DIR}/include/jpeg)

file(GLOB Node_SRC
    "*.h"
    "*.cpp"
)


#SET(CMAKE_SHARED_LINKER_FLAGS="-fprofile-arcs -ftest-coverage")
SET(CMAKE_EXE_LINKER_FLAGS="-fprofile-arcs -ftest-coverage")


add_executable(Node ${Node_SRC})



if(USE_ARM)
	find_library(MQTT_LIBRARY mqttpp HINTS /home/mikel/workspace/IoT_MTTQ/lib_ARM32/mqtt)
	
	find_library(MQTT_LIBRARY_C paho-mqtt3a HINTS /home/mikel/workspace/IoT_MTTQ/lib_ARM32/mqtt)

	find_library(RASPI_LIBRARY raspicam HINTS /home/mikel/workspace/IoT_MTTQ/lib_ARM32)
	find_library(JPEG_LIBRARY jpeg HINTS ~/workspace/IoT_MTTQ/lib_ARM32/jpeg/) 
	find_library(GTEST_LIBRARY gtest ~/workspace/IoT_MTTQ/lib_ARM32/googlemock/gtest) 

	#TARGET_LINK_LIBRARIES(Node PUBLIC ${GTEST_LIBRARY} ${MQTT_LIBRARY} ${MQTT_LIBRARY_C} ${RASPI_LIBRARY} ${JPEG_LIBRARY} pthread gcov)	

	TARGET_LINK_LIBRARIES(Node PUBLIC ${GTEST_LIBRARY} ${MQTT_LIBRARY} ${MQTT_LIBRARY_C} ${RASPI_LIBRARY} ${JPEG_LIBRARY} pthread gcov)	

else()
	find_library(MQTT_LIBRARY_C paho-mqtt3a HINTS /home/mikel/workspace/IoT_MTTQ/lib_x64/mttq)
	find_library(MQTT_LIBRARY mqttpp HINTS /home/mikel/workspace/IoT_MTTQ/lib_x64/mttq)
	find_library(RASPI_LIBRARY raspicam HINTS /home/mikel/workspace/IoT_MTTQ/lib_x64/raspicam)
	find_library(GTEST_LIBRARY gtest ~/workspace/IoT_MTTQ/lib_x64/googlemock/gtest) 
	find_library(JPEG_LIBRARY jpeg HINTS ~/workspace/IoT_MTTQ/lib_x64/jpeg/) 

	TARGET_LINK_LIBRARIES(Node PUBLIC ${GTEST_LIBRARY} ${MQTT_LIBRARY} ${MQTT_LIBRARY_C} ${RASPI_LIBRARY} ${JPEG_LIBRARY} pthread )
endif(USE_ARM)


