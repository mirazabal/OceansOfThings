extern "C"
{
#include "src/parser_types.h"
#include "gpgga/gpgga.h"
#include "gpgll/gpgll.h"
#include "gprmc/gprmc.h"
#include "SQLite/sqlite3_NMEA.h"
};

#include "include/gtest/gtest.h"

namespace
{
	class NMEA_0183_TEST : public ::testing::Test 
	{
		protected:
		virtual ~NMEA_0183_TEST(){};
		
		void parse_module_gpggl(){
			gpgll_ = (nmea_parser_module_t*)malloc(sizeof( nmea_parser_module_t));
			ASSERT_FALSE( NULL == gpgll_);
			gpgll_->allocate_data = &allocate_data_GPGLL;
			gpgll_->set_default = &set_default_GPGLL;
			gpgll_->free_data = &free_data_GPGLL;
			gpgll_->parse = &parse_GPGLL;
			gpgll_->parser.type = NMEA_GPGLL;

		}

		void parse_module_gpgga(){
			gpgga_ = (nmea_parser_module_t*)malloc(sizeof( nmea_parser_module_t));
			ASSERT_FALSE( NULL == gpgga_);
			gpgga_->allocate_data = &allocate_data_GPGGA;
			gpgga_->set_default = &set_default_GPGGA;
			gpgga_->free_data = &free_data_GPGGA;
			gpgga_->parse = &parse_GPGGA;
			gpgga_->parser.type = NMEA_GPGGA;
		}

		void parse_module_gprmc(){
			gprmc_ = (nmea_parser_module_t*)malloc(sizeof( nmea_parser_module_t));
			ASSERT_FALSE( NULL == gprmc_);
			gprmc_->allocate_data = &allocate_data_GPRMC;
			gprmc_->set_default = &set_default_GPRMC;
			gprmc_->free_data = &free_data_GPRMC;
			gprmc_->parse = &parse_GPRMC;
			gprmc_->parser.type = NMEA_GPRMC;
		}



		virtual void SetUp(){
			parse_module_gpgga();
			parse_module_gprmc();
			parse_module_gpggl();

			nmea_register_parse(gpgga_);
			nmea_register_parse(gpgll_);
			nmea_register_parse(gprmc_);
			
			ASSERT_EQ(0, open_database());
			ASSERT_EQ(0, create_table());		
		}	
		
		virtual void TearDown(){
			free(gpgll_);
			gpgll_ = NULL;
			free(gpgga_);
			gpgga_ = NULL;
			free(gprmc_);
			gprmc_ = NULL;
		}


		nmea_parser_module_t* gpgll_; 
		nmea_parser_module_t* gpgga_;
		nmea_parser_module_t* gprmc_;

	};
	
	TEST_F(NMEA_0183_TEST, parse_simple_sentence_gpgga)
	{
		char sentence[] = "$GPGGA,191410,4735.5634,N,00739.3538,E,1,04,4.4,351.5,M,48.0,M,,*45\n\n";
		nmea_basic_t* data = nmea_parse(sentence, strlen(sentence), 0);	

		ASSERT_NE( data , nullptr);

		ASSERT_EQ(NMEA_GPGGA, data->type);
		nmea_gpgga_t* nmea_gp = (nmea_gpgga_t*)data;

		char sResult[255];
		int const sResultSize = sizeof(sResult)/ sizeof(sResult[0]);
		ASSERT_EQ(0, create_sql_data( TYPE_STRING[data->type], sentence, sResult, sResultSize ) );
		ASSERT_EQ(0, insert_data(sResult));

		if(data != NULL)
			nmea_free(data);
	}

	TEST_F(NMEA_0183_TEST, parse_simple_sentence_GPGLL)
	{
		char sentence[] = "$GPGLL,4916.45,N,12311.12,W,225444,A\n\n";
		nmea_basic_t* data = nmea_parse(sentence, strlen( sentence ), 0 );		
		ASSERT_TRUE( NULL !=  data  );
		ASSERT_EQ( NMEA_GPGLL , data->type);

		nmea_gpgll_t *gpgll = (nmea_gpgll_t *) data;
/*
		printf("GPGLL Sentence\n");
		printf("Longitude:\n");
		printf("  Degrees: %d\n", gpgll->longitude.degrees);
		printf("  Minutes: %f\n", gpgll->longitude.minutes);
		printf("  Cardinal: %c\n", (char) gpgll->longitude.cardinal);
		printf("Latitude:\n");
		printf("  Degrees: %d\n", gpgll->latitude.degrees);
		printf("  Minutes: %f\n", gpgll->latitude.minutes);
		printf("  Cardinal: %c\n", (char) gpgll->latitude.cardinal);
*/
		char sResult[255];
		int const sResultSize = sizeof(sResult)/ sizeof(sResult[0]);
		ASSERT_EQ(0, create_sql_data( TYPE_STRING[data->type], sentence, sResult, sResultSize ) );
		ASSERT_EQ(0, insert_data(sResult));

		if(data != NULL)	
			nmea_free(data);
	}

	TEST_F(NMEA_0183_TEST, parse_simple_sentence_GPRMC)
	{
		char sentence[] = "$GPRMC,081836,A,3751.65,S,14507.36,E,000.0,360.0,130998,011.3,E*62\n\n";
			
		nmea_basic_t* data = nmea_parse(sentence, strlen( sentence ), 0 );		
		ASSERT_TRUE( NULL !=  data  );
		ASSERT_EQ( NMEA_GPRMC , data->type);

		nmea_gprmc_t *gprmc = (nmea_gprmc_t *) data;
/*
		printf("GPRMC Sentence\n");
		printf("Longitude:\n");
		printf("  Degrees: %d\n", gprmc->longitude.degrees);
		printf("  Minutes: %f\n", gprmc->longitude.minutes);
		printf("  Cardinal: %c\n", (char) gprmc->longitude.cardinal);
		printf("Latitude:\n");
		printf("  Degrees: %d\n", gprmc->latitude.degrees);
		printf("  Minutes: %f\n", gprmc->latitude.minutes);
		printf("  Cardinal: %c\n", (char) gprmc->latitude.cardinal);
*/
		if(data != NULL)	
			nmea_free(data);
	}

}// end of namespace

int main(int argc, char **argv)
{	
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
};
