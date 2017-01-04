#pragma once


#include <map>

#include "mqtt/iclient_persistence.h"
#include "mqtt/ipersistable.h"


class sample_mem_persistence : public mqtt::iclient_persistence
{

public:

	sample_mem_persistence();
	~sample_mem_persistence();

	void open(const std::string& clientId, const std::string& serverURI) override;
	
	void close() override;
	
	void clear() override;
	
	bool contains_key(const std::string& key) override;
	
	mqtt::ipersistable_ptr get(const std::string& key) const override;
	
	std::vector<std::string> keys() const override;
	
	void put(const std::string& key, mqtt::ipersistable_ptr persistable) override;
	
	void remove(const std::string& key) override;
private:
	bool open_;
	std::map<std::string, mqtt::ipersistable_ptr> store_;

};


