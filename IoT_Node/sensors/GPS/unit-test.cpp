
#include "include/gtest/gtest.h"
#include "NMEA_0183_sensor.h"


namespace
{
	class NMEA_0183_sensor_TEST : public ::testing::Test 
	{
		protected:
		virtual ~NMEA_0183_sensor_TEST(){};
	

		virtual void SetUp(){
			auto a = sens.get_data();	
		}	
		
		virtual void TearDown(){
		}

		NMEA_0183_sensor sens;
	};
	TEST_F(NMEA_0183_sensor_TEST, parse_simple_sentence_GPRMC)
	{

	}

}// end of namespace

int main(int argc, char **argv)
{	
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
}

