#include "camera_NoIr_V2.h"

#include "include/boost/gil/gil_all.hpp"                                              
#include "include/boost/gil/extension/io/jpeg_io.hpp"                                             

#include <memory>
#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>
#include <stdexcept>
#include <exception>

typedef struct {
	unsigned char red,green,blue;     
}PPMPixel;

class PPMImage{
	public:
	PPMPixel* data;
};

camera_NoIR_V2::camera_NoIR_V2()
{
	if ( !camera_.open()) {
		throw(std::runtime_error( "Error opening camera. Is the camera connected?"));
	}
}

camera_NoIR_V2::~camera_NoIR_V2()
{

}

std::string camera_NoIR_V2::grab_encoded64( )
{
	camera_.grab();
	return encode_base64(get_image());
}

std::string camera_NoIR_V2::get_image( )
{
	int data_lenght = camera_.getImageTypeSize ( raspicam::RASPICAM_FORMAT_RGB ); 
	std::unique_ptr<unsigned char> data( new unsigned char[data_lenght]);	

	//extract the image in rgb format
    camera_.retrieve ( data.get(),raspicam::RASPICAM_FORMAT_RGB );

	std::string filename("out.jpeg");
	convert_and_safe_uchar_to_jpeg( data.get(), filename );
	return ( convert_file_to_string(filename) );
}

void camera_NoIR_V2::convert_and_safe_uchar_to_jpeg(unsigned char* data, std::string const& filename)
{	
	int cam_height = camera_.getHeight();
	int cam_width = camera_.getWidth();
	int numPixels = cam_height * cam_width;

	// unsafe but effective
	PPMImage img_;
	img_.data = (PPMPixel*)data;

	unsigned char r[numPixels];                              
	unsigned char g[numPixels];                                             
	unsigned char b[numPixels];

	for(int i = 0; i < numPixels ; i++){
			r[i] = img_.data[i].red;	
			g[i] = img_.data[i].green;
			b[i] = img_.data[i].blue;
		}                                          

	boost::gil::rgb8c_planar_view_t view = boost::gil::planar_rgb_view(cam_width, cam_height,
																	r, g, b, cam_width);
	boost::gil::jpeg_write_view(filename, view); 
}

std::string camera_NoIR_V2::convert_file_to_string(std::string const& filename)
{
	std::ifstream t(filename);
	std::stringstream buffer;
	buffer << t.rdbuf();
	return buffer.str();
}	

std::string camera_NoIR_V2::encode_base64(std::string const& source){
	return base64_encoder_.encode(reinterpret_cast<const unsigned char*>(source.c_str()), source.size() );
}

std::vector<std::string> camera_NoIR_V2::get_data(){
	std::string encoded_str = grab_encoded64();
	std::vector<std::string> vs{ encoded_str };
	return vs;
}

