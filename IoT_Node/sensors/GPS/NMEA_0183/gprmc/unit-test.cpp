extern "C"{
#include "gprmc.h"
#include "../src/nmea.h"
};

#include "../include/gtest/gtest.h"

namespace
{
	class GPRMC_TEST : public ::testing::Test 
	{
		protected:
		virtual ~GPRMC_TEST(){};
		
		virtual void SetUp(){
			parser_ = (nmea_parser_module_t*)malloc(sizeof( nmea_parser_module_t));
			ASSERT_FALSE( NULL == parser_);
			parser_->allocate_data = &allocate_data_GPRMC;
			parser_->set_default = &set_default_GPRMC;
			parser_->free_data = &free_data_GPRMC;
			parser_->parse = &parse_GPRMC;
			parser_->parser.type = NMEA_GPRMC;
		}

		virtual void TearDown(){
			free(parser_);
			parser_ = NULL;
		}
		
		nmea_parser_module_t *parser_;
	};
	

	TEST_F(GPRMC_TEST, register_parser)
	{
		ASSERT_TRUE( NULL ==  nmea_get_parse(parser_->parser.type ));
		nmea_register_parse(parser_);
		ASSERT_EQ( NULL ,  nmea_get_parse( NMEA_GPGGA ));
		ASSERT_EQ( NULL ,  nmea_get_parse( NMEA_GPGLL ));
		nmea_parser_module_s *p = nmea_get_parse(parser_->parser.type );
		ASSERT_TRUE(  p != NULL );
		ASSERT_EQ( p->parser.type , NMEA_GPRMC );

		nmea_parser_module_s *p2 = nmea_get_parse(parser_->parser.type );
		ASSERT_TRUE(  p2 != NULL );
		ASSERT_EQ( p2->parser.type , NMEA_GPRMC );

	}

	TEST_F(GPRMC_TEST, parse_simple_sentence)
	{
		char sentence[] = "$GPRMC,081836,A,3751.65,S,14507.36,E,000.0,360.0,130998,011.3,E*62\n\n";
			
		nmea_register_parse(parser_);
		nmea_basic_t* data = nmea_parse(sentence, strlen( sentence ), 0 );		
		ASSERT_TRUE( NULL !=  data  );
		ASSERT_EQ( NMEA_GPRMC , data->type);

		nmea_gprmc_t *gprmc = (nmea_gprmc_t *) data;

		printf("GPRMC Sentence\n");
		printf("Longitude:\n");
		printf("  Degrees: %d\n", gprmc->longitude.degrees);
		printf("  Minutes: %f\n", gprmc->longitude.minutes);
		printf("  Cardinal: %c\n", (char) gprmc->longitude.cardinal);
		printf("Latitude:\n");
		printf("  Degrees: %d\n", gprmc->latitude.degrees);
		printf("  Minutes: %f\n", gprmc->latitude.minutes);
		printf("  Cardinal: %c\n", (char) gprmc->latitude.cardinal);
	
		nmea_free(data);
	}

	TEST_F(GPRMC_TEST, parse_error_in_sentence_no_$)
	{
		char sentence[] = "GPRMC,081836,A,3751.65,S,14507.36,E,000.0,360.0,130998,011.3,E*62\n\n";

		nmea_register_parse(parser_);
		nmea_basic_t* data = nmea_parse(sentence, strlen( sentence ), 0 );		
	
		ASSERT_TRUE( NULL ==  data  );
	
		nmea_free(data);
	}

	TEST_F(GPRMC_TEST, parse_error_in_sentence_no_EOF)
	{

		char sentence[] = "$GPRMC,4916.45,12311.12,W,225444,A\n";
		nmea_register_parse(parser_);
		nmea_basic_t* data =	nmea_parse(sentence, strlen( sentence ), 0 );		
		ASSERT_TRUE( NULL ==  data  );
	
		nmea_free(data);
	}

	TEST_F(GPRMC_TEST, parse_sentence_excess_chars)
	{
		char sentence[] = "i234ew$GPRMC,081836,A,3751.65,S,14507.36,E,000.0,360.0,130998,011.3,E*62\n\n wer";

		/* find start (a dollar $ign) */
		char *start = (char*)memchr(sentence, '$', strlen(sentence));
		ASSERT_TRUE( NULL != start);

		/* find end of line */
		char *end = (char*)memchr(start, '\n' , strlen(sentence) );
		ASSERT_TRUE( NULL != end);

		nmea_register_parse(parser_);

		int sentenceLenght = int( end - start + 2);
		nmea_basic_t* data = nmea_parse(start , sentenceLenght , 0 );		
	
		ASSERT_TRUE( NULL !=  data  );
		ASSERT_EQ( NMEA_GPRMC , data->type);

		nmea_gprmc_t *gprmc = (nmea_gprmc_t *) data;

		nmea_free(data);
	}
}// end of namespace

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc,argv);
	return RUN_ALL_TESTS();
};

