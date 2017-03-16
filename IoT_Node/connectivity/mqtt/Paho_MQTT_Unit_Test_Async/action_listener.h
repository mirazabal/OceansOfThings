#ifndef ACTION_LISTENER_H
#define ACTION_LISTENER_H

#include "mqtt/iaction_listener.h"
#include "mqtt/token.h"


class action_listener : public mqtt::iaction_listener
{
	protected:
		void on_failure(const mqtt::itoken& tok) override;
		void on_success(const mqtt::itoken& tok) override;
};

#endif

