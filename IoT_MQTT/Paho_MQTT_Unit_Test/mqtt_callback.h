#include "mqtt/callback.h"

class mqtt_callback : public mqtt::callback
{
public:
	mqtt_callback();
	virtual ~mqtt_callback();

	void connection_lost(const std::string& cause) override; 

	// We're not subscrived to anything, so this should never be called.
	void message_arrived(const std::string& topic, mqtt::message_ptr msg) override;

	void delivery_complete(mqtt::idelivery_token_ptr tok) override;
};

