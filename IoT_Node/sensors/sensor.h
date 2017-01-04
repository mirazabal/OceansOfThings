#ifndef sensor_h
#define sensor_h

#include <vector>
#include <string>

class sensor{

public:
	sensor();
	virtual ~sensor();

	virtual std::vector<std::string> get_data() = 0;


private:


};




#endif
