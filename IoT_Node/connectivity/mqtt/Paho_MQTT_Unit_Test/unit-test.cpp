#include <iostream>
#include <memory>
#include <string>

#include "sample_mem_persistence.h"
#include "mqtt/client.h"
#include "mqtt_callback.h"

#include "gtest/gtest.h"

#ifdef _WIN32
	
#elif defined __unix__
	#include <stdio.h>
	#include <stdlib.h>
#elif defined __APPLE__
	
#endif

constexpr char ADDRESS[] = {"tcp://localhost:1883"};
constexpr auto CLIENTID{"SyncPublisher"};

constexpr auto QOS{1};
constexpr auto TIMEOUT{10000};


namespace
{
	class MQTT_TEST : public ::testing::Test 
	{
		protected:
			virtual ~MQTT_TEST(){};

			void set_conn_ops()
			{
				connOpts.set_keep_alive_interval(20);
				connOpts.set_clean_session(true);
			}

			virtual void SetUp(){
#ifdef _WIN32

#elif defined __unix__
				system("./../NodeMQTT/nodeBroker.sh");
#elif defined __APPLE__

#endif
				if( client == nullptr){

					client = std::make_unique<mqtt::client>(ADDRESS, CLIENTID, &persist);
					client->set_callback(cb);

					set_conn_ops();
				}
			}	

			virtual void TearDown(){
				//			client->disconnect();
			}

			sample_mem_persistence persist;
			mqtt_callback cb;
			std::unique_ptr<mqtt::client> client;
			mqtt::connect_options connOpts;
	};
	
	TEST_F(MQTT_TEST, simple_connection)
	{
		ASSERT_NO_THROW( client->connect(connOpts));
		ASSERT_NO_THROW( client->disconnect() );
		/*
		   try{
		   client->connect(connOpts);

		   client->disconnect();
		   }
		   catch (const mqtt::persistence_exception& exc) {
		   std::cerr << "Persistence Error: " << exc.what() << " [" << exc.get_reason_code() << "]" << std::endl;
		   }
		   catch (const mqtt::exception& exc) {
		   std::cerr << "Error: " << exc.what() << " [" << exc.get_reason_code() << "]" << std::endl;
		   }
		   */
	}

	TEST_F(MQTT_TEST, publish_message_pointer)
	{
		ASSERT_NO_THROW(client->connect(connOpts));

		constexpr auto PAYLOAD{"Message from publish_message_pointer"};
		mqtt::message_ptr pubmsg = std::make_shared<mqtt::message>(PAYLOAD);
		pubmsg->set_qos(QOS);

		constexpr auto TOPIC{"presence"};
		ASSERT_NO_THROW( client->publish(TOPIC, pubmsg) );

		ASSERT_NO_THROW(client->disconnect());
	}

	TEST_F(MQTT_TEST, publish_itemized)
	{
		ASSERT_NO_THROW(client->connect(connOpts));

		const char* PAYLOAD2 = "Message from publish_itemized";
		constexpr auto TOPIC{"presence"};
		ASSERT_NO_THROW(client->publish(TOPIC, PAYLOAD2, strlen(PAYLOAD2)+1, 0, false));

		ASSERT_NO_THROW(client->disconnect());
	}

	TEST_F(MQTT_TEST, publish_listener_no_token)
	{
		ASSERT_NO_THROW(client->connect(connOpts));

		// Now try with a listener, but no token
		constexpr auto PAYLOAD{ "Message from publish_listener_no_token"};
		auto pubmsg = std::make_shared<mqtt::message>(PAYLOAD);
		pubmsg->set_qos(QOS);
		constexpr auto TOPIC{"presence"};
		ASSERT_NO_THROW(client->publish(TOPIC, pubmsg));
		ASSERT_NO_THROW(client->disconnect());
	}

}// end of namespace

int main(int argc, char **argv)
{	
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
};
