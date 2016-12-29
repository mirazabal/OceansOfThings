extern "C"{

#include "gpgga.h"
#include "../src/nmea.h"

};

#include "../include/gtest/gtest.h"

namespace
{
	class GPGGA_TEST : public ::testing::Test 
	{
		protected:
		virtual ~GPGGA_TEST(){};
		
		virtual void SetUp(){
			parser_ = (nmea_parser_module_t*)malloc(sizeof( nmea_parser_module_t));
			ASSERT_FALSE( NULL == parser_);
			parser_->allocate_data = &allocate_data_GPGGA;
			parser_->set_default = &set_default_GPGGA;
			parser_->free_data = &free_data_GPGGA;
			parser_->parse = &parse_GPGGA;
			parser_->parser.type = NMEA_GPGGA;
		}

		virtual void TearDown(){
			free(parser_);
			parser_ = NULL;
		}
		
		nmea_parser_module_t *parser_;
	};
	
	TEST_F(GPGGA_TEST, register_parser)
	{
		ASSERT_TRUE( NULL ==  nmea_get_parse(parser_->parser.type ));
		nmea_register_parse(parser_);
		ASSERT_EQ( NULL ,  nmea_get_parse( NMEA_GPGLL ));
		ASSERT_EQ( NULL ,  nmea_get_parse( NMEA_GPRMC ));
		nmea_parser_module_s *p = nmea_get_parse(parser_->parser.type );
		ASSERT_TRUE(  p != NULL );
		ASSERT_EQ( p->parser.type , NMEA_GPGGA );

		nmea_parser_module_s *p2 = nmea_get_parse(parser_->parser.type );
		ASSERT_TRUE(  p2 != NULL );
		ASSERT_EQ( p2->parser.type , NMEA_GPGGA );

	}

	TEST_F(GPGGA_TEST, parse_simple_sentence)
	{
		char sentence[] = "$GPGGA,191410,4735.5634,N,00739.3538,E,1,04,4.4,351.5,M,48.0,M,,*45\n\n";

		nmea_register_parse(parser_);
		nmea_basic_t* data = nmea_parse(sentence, strlen( sentence ), 0 );		
		ASSERT_TRUE( NULL !=  data  );
		ASSERT_EQ( NMEA_GPGGA , data->type);

		nmea_gpgga_t *gpgga = (nmea_gpgga_t *) data;

		printf("  Degrees: %d\n", gpgga->latitude.degrees);

		nmea_free(data);
	}

	TEST_F(GPGGA_TEST, parse_error_in_sentence_no_$)
	{
		char sentence[] = "GPGGA,4916.45,12311.12,W,225444,A\n\n";
		nmea_register_parse(parser_);
		nmea_basic_t* data = nmea_parse(sentence, strlen( sentence ), 0 );		
	
		ASSERT_TRUE( NULL ==  data  );
	
		nmea_free(data);
	}

	TEST_F(GPGGA_TEST, parse_error_in_sentence_no_EOF)
	{
		char sentence[] = "$GPGGA,4916.45,S,12311.12,W,225444,A\n";
		nmea_register_parse(parser_);
		nmea_basic_t* data =	nmea_parse(sentence, strlen( sentence ), 0 );		
		ASSERT_TRUE( NULL ==  data  );
	
		nmea_free(data);
	}

	TEST_F(GPGGA_TEST, parse_sentence_excess_chars)
	{
		char sentence[] = "qwe456$GPGGA,4916.45,S,12311.12,W,225444,A\n\n456789 ";
		/* find start (a dollar $ign) */
		char *start = (char*)memchr(sentence, '$', strlen(sentence));
		ASSERT_TRUE( NULL != start);

		/* find end of line */
		char *end = (char*)memchr(start, '\n' , strlen(sentence) );
		ASSERT_TRUE( NULL != end);

		nmea_register_parse(parser_);

		int sentenceLenght = int( end - start + 2);
		nmea_basic_t* data =	nmea_parse(start , sentenceLenght , 0 );		
	
		ASSERT_TRUE( NULL !=  data  );
		ASSERT_EQ( NMEA_GPGGA , data->type);

		nmea_gpgga_t *gpgga = (nmea_gpgga_t *) data;

		nmea_free(data);
	}
}// end of namespace



int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc,argv);
	auto retVal = RUN_ALL_TESTS();
	return 0;
};

