#include "fake_camera.h"



fake_camera::fake_camera()
{

}

fake_camera::~fake_camera()
{

}

std::vector<std::string> fake_camera::get_data()
{
	std::vector<std::string> vs;

	vs.emplace_back("Data simulated from fake camera ");
	return vs;
}
