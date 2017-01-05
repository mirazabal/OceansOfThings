#include "NMEA_0183_sensor.h"

extern "C"
{
#include "src/parser_types.h"
#include "gpgga/gpgga.h"
#include "gpgll/gpgll.h"
#include "gprmc/gprmc.h"
};

struct  NMEA_0183_sensor::Impl
{
	public:
		void parse_modules();
		void free_parsed_modules();	
	private:
		void parse_module_gpgga();
		void parse_module_gpggl();
		void parse_module_gprmc();

		// old style nice C ...
		nmea_parser_module_t* gpgll_; 
		nmea_parser_module_t* gpgga_;
		nmea_parser_module_t* gprmc_;
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
	ASSERT_FALSE( NULL == gpgga_);
	gpgga_->allocate_data = &allocate_data_GPGGA;
	gpgga_->set_default = &set_default_GPGGA;
	gpgga_->free_data = &free_data_GPGGA;
	gpgga_->parse = &parse_GPGGA;
	gpgga_->parser.type = NMEA_GPGGA;
}

void NMEA_0183_sensor::Impl::parse_module_gprmc()
{
	gprmc_ = (nmea_parser_module_t*)malloc(sizeof( nmea_parser_module_t));
	ASSERT_FALSE( NULL == gprmc_);
	gprmc_->allocate_data = &allocate_data_GPRMC;
	gprmc_->set_default = &set_default_GPRMC;
	gprmc_->free_data = &free_data_GPRMC;
	gprmc_->parse = &parse_GPRMC;
	gprmc_->parser.type = NMEA_GPRMC;
}

NMEA_0183_sensor::NMEA_0183_sensor() : pImpl(std::make_unique<Impl>())
{
	pImpl->parse_modules();
}

NMEA_0183_sensor::~NMEA_0183_sensor()
{
	pImpl->free_parsed_modules();
}

std::vector<std::string> NMEA_0183_sensor::get_data()
{
	return std::vector<std::string>();
}

