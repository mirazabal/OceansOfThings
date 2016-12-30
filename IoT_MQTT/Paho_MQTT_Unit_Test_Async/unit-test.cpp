#include <iostream>
#include <cstdlib>
#include <string>
#include <thread>	// For sleep
#include <chrono>
#include <cstring>
#include "mqtt/async_client.h"

#include "callbackAsyncPublish.h"
#include "action_listener.h"
#include "delivery_action_listener.h"

#include "gtest/gtest.h"

constexpr auto ADDRESS {"tcp://localhost:1883"};
constexpr auto CLIENTID{"AsyncPublisher"};
constexpr auto TOPIC{"presence"};

const char* PAYLOAD1 = "Hello World!";
const char* PAYLOAD2 = "Hi there!";
const char* PAYLOAD3 = "Is anyone listening?";
const char* PAYLOAD4 = "Someone is always listening.";

const int  QOS = 1;
const long TIMEOUT = 10000L;

inline void sleep(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}
/*

int main(int argc, char* argv[])
{
	mqtt::async_client client(ADDRESS, CLIENTID);
	
	callbackAsyncPublish cb;
	client.set_callback(cb);

	try {
		mqtt::itoken_ptr conntok = client.connect();
		std::cout << "Waiting for the connection..." << std::flush;
		conntok->wait_for_completion();
		std::cout << "OK" << std::endl;

		// First use a message pointer.

		std::cout << "Sending message..." << std::flush;
		mqtt::message_ptr pubmsg = std::make_shared<mqtt::message>(PAYLOAD1);
		pubmsg->set_qos(QOS);
		client.publish(TOPIC, pubmsg)->wait_for_completion(TIMEOUT);
		std::cout << "OK" << std::endl;

		// Now try with itemized publish.

		std::cout << "Sending next message..." << std::flush;
		mqtt::idelivery_token_ptr pubtok;
		pubtok = client.publish(TOPIC, PAYLOAD2, std::strlen(PAYLOAD2), QOS, false);
		pubtok->wait_for_completion(TIMEOUT);
		std::cout << "OK" << std::endl;

		// Now try with a listener

		std::cout << "Sending next message..." << std::flush;
		action_listener listener;
		pubmsg = std::make_shared<mqtt::message>(PAYLOAD3);
		pubtok = client.publish(TOPIC, pubmsg, nullptr, listener);
		pubtok->wait_for_completion();
		std::cout << "OK" << std::endl;

		// Finally try with a listener, but no token

		std::cout << "Sending final message..." << std::flush;
		delivery_action_listener deliveryListener;
		pubmsg = std::make_shared<mqtt::message>(PAYLOAD4);
		client.publish(TOPIC, pubmsg, nullptr, deliveryListener);

		while (!deliveryListener.is_done()) {
			sleep(100);
		}
		std::cout << "OK" << std::endl;

		// Double check that there are no pending tokens

		std::vector<mqtt::idelivery_token_ptr> toks = client.get_pending_delivery_tokens();
		if (!toks.empty())
			std::cout << "Error: There are pending delivery tokens!" << std::endl;

		// Disconnect
		std::cout << "Disconnecting..." << std::flush;
		conntok = client.disconnect();
		conntok->wait_for_completion();
		std::cout << "OK" << std::endl;
	}
	catch (const mqtt::exception& exc) {
		std::cerr << "Error: " << exc.what() << std::endl;
		return 1;
	}

 	return 0;
}
*/

namespace
{
	class MQTT_ASYNC_TEST : public ::testing::Test 
	{
		protected:
			virtual ~MQTT_ASYNC_TEST(){};

			virtual void SetUp(){
#ifdef _WIN32

#elif defined __unix__
				system("./NodeMQTT/nodeBroker.sh");
#elif defined __APPLE__

#endif

				if(client == nullptr){
					client = std::make_unique(ADDRESS,CLIENTID);
					
				}
		}	
			virtual void TearDown(){
			}

		std::unique_ptr<mqtt::async_client> client; 
	};
	
	TEST_F(MQTT_ASYNC_TEST, simple_connection)
	{

		callbackAsyncPublish cb;
		client->set_callback(cb);

		try {
			mqtt::itoken_ptr conntok = client->connect();
			std::cout << "Waiting for the connection..." << std::flush;
			conntok->wait_for_completion();
			std::cout << "OK" << std::endl;

			// Disconnect
			std::cout << "Disconnecting..." << std::flush;
			conntok = client->disconnect();
			conntok->wait_for_completion();
			std::cout << "OK" << std::endl;
		}
		catch (const mqtt::exception& exc) {
			std::cerr << "Error: " << exc.what() << std::endl;
			return;
		}
	}

	TEST_F( MQTT_ASYNC_TEST, publish_message_pointer)
	{
		auto debugVar{50};
	}


}// end of namespace

int main(int argc, char **argv)
{	
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
};

