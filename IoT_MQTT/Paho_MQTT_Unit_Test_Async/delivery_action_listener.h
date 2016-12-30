#ifndef DELIVERY_ACTION_LISTENER_H
#define DELIVERY_ACTION_LISTENER_H

#include "action_listener.h"


class delivery_action_listener : public action_listener
{
	public:
		delivery_action_listener();
		virtual ~delivery_action_listener();

		bool is_done() const;

	private:
		void on_failure(const mqtt::itoken& tok) override; 
		void on_success(const mqtt::itoken& tok) override;

		bool done_;
};

/////////////////////////////////////////////////////////////////////////////

#endif

