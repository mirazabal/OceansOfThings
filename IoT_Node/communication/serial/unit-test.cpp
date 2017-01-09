#include "CallbackAsyncSerial.h"

#include <chrono>
#include <iostream>
#include <memory>
#include <functional>
#include <thread>
#include <string>
#include <stdlib.h>

#include "gtest/gtest.h"

#ifdef _WIN32
	
#elif defined __unix__

#elif defined __APPLE__
	
#endif

namespace
{
	class Serial_TEST : public ::testing::Test 
	{
		protected:
			virtual ~Serial_TEST(){};

			virtual void SetUp(){
			}

			virtual void TearDown(){
			}
			
			std::unique_ptr< serial::CallbackAsyncSerial> c;
			
				};

	TEST_F(Serial_TEST, connect)
	{
		static constexpr auto const portName{"/dev/pts/20"};
		static constexpr auto const portSpeed{115200};

		if(c == nullptr){
			system("~/workspace/OceansOfThings/IoT_Node/communication/serial/portSimulator/portSimulator.sh");
			ASSERT_NO_THROW(c = std::make_unique<serial::CallbackAsyncSerial>(portName, portSpeed) );		
		}
	}

	TEST_F(Serial_TEST, set_callback_ )
	{
		if(c == nullptr){
			static constexpr auto const portName{"/dev/pts/20"};
			static constexpr auto const portSpeed{115200};

			ASSERT_NO_THROW(c = std::make_unique<serial::CallbackAsyncSerial>(portName, portSpeed) );		
		}

		std::function< void ( const char* data, size_t size) > fp = [](const char* d, size_t t){
			std::string str(d,t);
			std::cout << str << std::endl;
		};
		
		c->setCallback(fp);
		
		system("~/workspace/OceansOfThings/IoT_Node/communication/serial/portSimulator/portSimulator.sh");

		std::this_thread::sleep_for(std::chrono::seconds(3));

	}

}// end of namespace

int main(int argc, char **argv)
{	
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}

