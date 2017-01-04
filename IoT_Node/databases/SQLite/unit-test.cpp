extern "C"{
	#include "sqlite3_NMEA.h"
};

#include "../include/gtest/gtest.h"

namespace
{
	class SQLite_TEST : public ::testing::Test 
	{
		protected:
		virtual ~SQLite_TEST(){};
		
		virtual void SetUp(){
		}

		virtual void TearDown(){
		}
	};
	
	TEST_F(SQLite_TEST, sqlite_open)
	{
		ASSERT_EQ( 0, open_database() );
	}

	TEST_F(SQLite_TEST, sqlite_create_table )
	{
		ASSERT_EQ( 0, open_database() );
		ASSERT_EQ( 0, create_table() );
	}

	TEST_F(SQLite_TEST, sqlite_drop_table )
	{
		ASSERT_EQ( 0, open_database() );
		ASSERT_EQ( 0, create_table() );
		ASSERT_EQ( 0, drop_table() );
	}

	TEST_F(SQLite_TEST, sqlite_insert_data)
	{
		ASSERT_EQ( 0, open_database() );
		ASSERT_EQ(0, create_table() );
		char sResult[150];
	 	int const sResultSize = sizeof(sResult) / sizeof(sResult[0]);	
		ASSERT_EQ( 0, create_sql_data( "GPGGL", "this is skampilation ", sResult , sResultSize ) );
		ASSERT_EQ( 0, insert_data(sResult ) );
	}

}// end of namespace



int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc,argv);
	auto retVal = RUN_ALL_TESTS();
	return 0;
};

