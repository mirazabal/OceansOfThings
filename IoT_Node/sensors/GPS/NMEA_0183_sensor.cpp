#include "NMEA_0183_sensor.h"

extern "C"
{
#include "src/parser_types.h"
#include "gpgga/gpgga.h"
#include "gpgll/gpgll.h"
#include "gprmc/gprmc.h"
};

#include "../../communication/serial/CallbackAsyncSerial.h"
#include <memory>
#include <stdexcept>

using namespace std;

struct  NMEA_0183_sensor::Impl
{
	public:
		Impl(): gpgll_{nullptr}, gpgga_{nullptr}, gprmc_{nullptr}, serialPort_{nullptr}
		{}

		void parse_modules();
		void free_parsed_modules();	
	
		void initSerialPort();
		void setSerialPortCallback(function<void(const char*, size_t)> const&);
	private:
		void parse_module_gpgga();
		void parse_module_gpggl();
		void parse_module_gprmc();

		// nice C ...
		nmea_parser_module_t* gpgll_; 
		nmea_parser_module_t* gpgga_;
		nmea_parser_module_t* gprmc_;
		
		unique_ptr< serial::CallbackAsyncSerial> serialPort_;
};

void NMEA_0183_sensor::Impl::parse_modules()
{
	parse_module_gpgga();
	parse_module_gpggl();
	parse_module_gprmc();
}

void NMEA_0183_sensor::Impl::free_parsed_modules()
{
	free(gpgll_);
	gpgll_ = NULL;
	free(gpgga_);
	gpgga_ = NULL;
	free(gprmc_);
	gprmc_ = NULL;
}

void NMEA_0183_sensor::Impl::parse_module_gpggl()
{
	gpgll_ = (nmea_parser_module_t*)malloc(sizeof( nmea_parser_module_t));
	gpgll_->allocate_data = &allocate_data_GPGLL;
	gpgll_->set_default = &set_default_GPGLL;
	gpgll_->free_data = &free_data_GPGLL;
	gpgll_->parse = &parse_GPGLL;
	gpgll_->parser.type = NMEA_GPGLL;
}

void NMEA_0183_sensor::Impl::parse_module_gpgga()
{
	gpgga_ = (nmea_parser_module_t*)malloc(sizeof( nmea_parser_module_t));
	assert( NULL != gpgga_);
	gpgga_->allocate_data = &allocate_data_GPGGA;
	gpgga_->set_default = &set_default_GPGGA;
	gpgga_->free_data = &free_data_GPGGA;
	gpgga_->parse = &parse_GPGGA;
	gpgga_->parser.type = NMEA_GPGGA;
}

void NMEA_0183_sensor::Impl::parse_module_gprmc()
{
	gprmc_ = (nmea_parser_module_t*)malloc(sizeof( nmea_parser_module_t));
	assert( NULL != gprmc_);
	gprmc_->allocate_data = &allocate_data_GPRMC;
	gprmc_->set_default = &set_default_GPRMC;
	gprmc_->free_data = &free_data_GPRMC;
	gprmc_->parse = &parse_GPRMC;
	gprmc_->parser.type = NMEA_GPRMC;
}

void NMEA_0183_sensor::Impl::initSerialPort()
{
	static std::string const portName{"/dev/pts/2"};
	static constexpr size_t const portSpeed{115200};

	try{
		if(serialPort_ == nullptr){
			std::unique_ptr<serial::CallbackAsyncSerial> uP( new serial::CallbackAsyncSerial(portName, portSpeed) );
			serialPort_ = std::move(uP); //make_unique<serial::CallbackAsyncSerial>(portName, portSpeed);	just c++11 :-(	
		}
	} catch(...) {
		throw std::runtime_error("Serial port problem. Simulation? Then $socat -d -d PTY PTY & in NMEA_0183_sensor");
	}


}

void NMEA_0183_sensor::Impl::setSerialPortCallback(function<void (const char*, size_t)> const& fp){
	assert(serialPort_ != nullptr);
	serialPort_->setCallback(fp);
}

NMEA_0183_sensor::NMEA_0183_sensor() : pImpl(new Impl()) //(make_unique<Impl>())
{
	pImpl->parse_modules();
	pImpl->initSerialPort();
}

NMEA_0183_sensor::~NMEA_0183_sensor()
{
	pImpl->free_parsed_modules();
}

void NMEA_0183_sensor::get_data_async( function<void(const char*, size_t)> const& fp){
	pImpl->setSerialPortCallback(fp);
}

