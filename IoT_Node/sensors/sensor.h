#ifndef sensor_h
#define sensor_h

#include <functional>

class sensor{

public:
	sensor();
	virtual ~sensor();

	virtual void get_data_async(std::function<void ( const char *, size_t)> const& ) = 0;

private:

};




#endif
