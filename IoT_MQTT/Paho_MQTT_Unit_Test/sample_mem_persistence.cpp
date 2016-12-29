#include "sample_mem_persistence.h"

#include "mqtt/client.h"

#include <iostream>

sample_mem_persistence::sample_mem_persistence() : open_(false)
{

}

sample_mem_persistence::~sample_mem_persistence()
{

}

// "Open" the store
void sample_mem_persistence::open(const std::string& clientId, const std::string& serverURI)
{
	std::cout << "[Opening persistence for '" << clientId << "' at '" << serverURI << "']" << std::endl;
	open_ = true;
}

// Close the persistent store that was previously opened.
void sample_mem_persistence::close()
{
	std::cout << "[Closing persistence store.]" << std::endl;
	open_ = false; 
}

// Clears persistence, so that it no longer contains any persisted data.
void sample_mem_persistence::clear()
{
	std::cout << "[Clearing persistence store.]" << std::endl;
	store_.clear(); 
}

// Returns whether or not data is persisted using the specified key.
bool sample_mem_persistence::contains_key(const std::string &key)
{
	return store_.find(key) != store_.end();
}

// Gets the specified data out of the persistent store.
mqtt::ipersistable_ptr sample_mem_persistence::get(const std::string& key) const
{
	std::cout << "[Searching persistence for key '"
		<< key << "']" << std::endl;
	auto p = store_.find(key);
	if (p == store_.end())
		throw mqtt::persistence_exception();
	std::cout << "[Found persistence data for key '"
		<< key << "']" << std::endl;
	return p->second;
}

// Returns the keys in this persistent data store.
std::vector<std::string> sample_mem_persistence::keys() const
{
	std::vector<std::string> ks;
	for (const auto& k : store_)
		ks.push_back(k.first);
	return ks;
}

// Puts the specified data into the persistent store.
void sample_mem_persistence::put(const std::string& key, mqtt::ipersistable_ptr persistable)
{
	std::cout << "[Persisting data with key '" << key << "']" << std::endl;
	store_[key] = persistable;
}

// Remove the data for the specified key.
void sample_mem_persistence::remove(const std::string &key)
{
	std::cout << "[Persistence removing key '" << key << "']" << std::endl;
	auto p = store_.find(key);
	if (p == store_.end())
		throw mqtt::persistence_exception();
	store_.erase(p);
	std::cout << "[Persistence key removed '" << key << "']" << std::endl;
}

