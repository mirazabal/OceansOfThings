#ifndef fake_camera_h
#define fake_camera_h

#include "sensor.h"

#include <fstream>
#include <string>
#include <vector>

class fake_camera : public sensor  {

public: 
	fake_camera();  
	virtual ~fake_camera();

	std::vector<std::string> get_data() override ;
private:

};

#endif

