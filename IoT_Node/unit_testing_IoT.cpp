#include "include/gtest/gtest.h"
#include "iot_node.h"
#include "sensors/GPS/NMEA_0183_sensor.h"

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
	IoT_Test(): node {"Node"}
   	{
    }

	virtual ~IoT_Test()
   	{
	}

	virtual void SetUp() {

		std::string uri{"tcp://localhost:1883"};
		std::shared_ptr<NMEA_0183_sensor> sens;
		ASSERT_NO_THROW( sens = std::make_shared<NMEA_0183_sensor>()  );
		node.add_sensor("GPS", sens);
		std::cout << "After GPS add sensor" << std::endl;
//		node.try_connect("tcp://5.10.201.121:1883");

		node.try_connect(uri);

	}

	virtual void TearDown() {
	 }

	iot_node node;
};

TEST_F(IoT_Test, SendDataGPS) {

		std::shared_ptr<sensor> GPS_sensor = node.get_sensor("GPS");

		std::function< void ( const char* data, size_t size) > fp = [&](const char* d, size_t t){
				std::string str(d,t);
				node.send_data("new message", str );
				std::cout << str << std::endl;
			};

		GPS_sensor->get_data_async(fp);
		std::this_thread::sleep_for(std::chrono::milliseconds(30000));
}

}  // namespace


int main(int argc, char **argv) {
	
	system("./../IoT_Server/NodeMQTT/nodeBroker.sh");

	std::thread t( [&](){system("./sensors/GPS/portSimulator/portSimulator.sh");} ) ;
	
	::testing::InitGoogleTest(&argc, argv);
	
	auto retVal = RUN_ALL_TESTS();

	t.join();

	return retVal;

}

