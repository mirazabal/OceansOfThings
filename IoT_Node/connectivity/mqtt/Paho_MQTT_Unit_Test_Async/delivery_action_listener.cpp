#include "delivery_action_listener.h"


delivery_action_listener::delivery_action_listener() : done_(false)
{

}

delivery_action_listener::~delivery_action_listener()
{

}

void delivery_action_listener::on_failure(const mqtt::itoken& tok)
{
		action_listener::on_failure(tok);
		done_ = true;
}

void delivery_action_listener::on_success(const mqtt::itoken& tok)
{
		action_listener::on_success(tok);
		done_ = true;
}

bool delivery_action_listener::is_done() const
{
	return done_;
}

