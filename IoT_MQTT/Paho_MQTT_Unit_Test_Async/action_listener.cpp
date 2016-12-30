#include "action_listener.h"

#include <iostream>

void action_listener::on_failure(const mqtt::itoken& tok)
{
	std::cout << "\n\tListener: Failure on token: " << tok.get_message_id() << std::endl;
}

void action_listener::on_success(const mqtt::itoken& tok)
{
	std::cout << "\n\tListener: Success on token: " << tok.get_message_id() << std::endl;
}

