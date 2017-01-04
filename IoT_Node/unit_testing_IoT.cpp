#include "include/gtest/gtest.h"
#include "camera_NoIr_V2.h"
#include "fake_camera.h"
#include "rpi_node.h"

#include <memory>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>
#include <iostream>
#include <exception>
#include <vector>

namespace {

 class IoT_Test : public ::testing::Test {
protected:
	IoT_Test():r("Node")  {
	              }
	virtual ~IoT_Test() {
	                      }
	virtual void SetUp() {
	#ifndef FAKE_CAMERA
		r.add_sensor("NoIR", std::make_shared<camera_NoIR_V2>());
	#else
		r.add_sensor("NoIR", std::make_shared<fake_camera>());
	#endif	
		r.try_connect("tcp://5.10.201.121:1883");

	}
	//
	virtual void TearDown() {
	 }
	rpi_node r;
};

TEST_F(IoT_Test, SendImage) {

	for(int i = 0; i < 1000; i++){

	std::shared_ptr<sensor> camSen = r.get_sensor("NoIR");
	std::vector<std::string> data = camSen->get_data();

//	ASSERT_GT(0, data.size() );
	r.send_data("image",data.at(0));

	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	
}	//


TEST_F(IoT_Test, SendMessage) {

	for(int i = 0; i < 1000; i++){
	r.send_data("new message","Different Messages "+ std::to_string(i) );

	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
	
}	//

}  // namespace


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

