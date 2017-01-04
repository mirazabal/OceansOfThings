#include <stdio.h>
#include <assert.h>
#include "sqlite3_NMEA.h"
#include "sqlite_src/sqlite3.h"

sqlite3 *db_;
char *zErrMsg_ = 0;
int rc_;
char const *databaseName_ = "test.db";  
		  
/* Create SQL Table */
char const*  sqlTable_ = "CREATE TABLE IF NOT EXISTS COMMAND_TABLE("  \
					"SQLTIME TIMESTAMP DEFAULT CURRENT_TIMESTAMP NOT NULL," \
					"COMMAND_TYPE           TEXT    NOT NULL," \
				    "COMMAND_DATA           TEXT    NOT NULL );";

char const* sqlDropTable_ = "DROP TABLE COMMAND_TABLE";


static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	for(i=0; i<argc; i++){
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int open_database()
{
	rc_ = sqlite3_open( databaseName_, &db_); 
	if( rc_ ){
		printf("Can't open database: %s\n", sqlite3_errmsg(db_));
		sqlite3_close(db_);
	}
	assert(rc_ == SQLITE_OK );
	return rc_;
}

int close_database()
{
	return sqlite3_close(db_);
}

int create_table()
{
	rc_ = sqlite3_exec(db_, sqlTable_, callback, 0, &zErrMsg_);
	if( rc_ != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg_);
		sqlite3_free(zErrMsg_);
	}
	assert(rc_ == SQLITE_OK );
	return rc_;
}

int drop_table()
{
	return sqlite3_exec(db_, sqlDropTable_, callback, 0, &zErrMsg_);
}

int create_sql_data(char const* sCommandType, char const* sCommandData, char* sResult, int const sResultSize)
{
	const int sSQLSize = sizeof(sResult)/sizeof(sResult[0]);
	const int cx = snprintf(sResult, sResultSize , 
			"INSERT INTO COMMAND_TABLE (COMMAND_TYPE,COMMAND_DATA) VALUES ('%s', '%s')", sCommandType, sCommandData);
	assert(cx > 0 );
	assert(cx < sResultSize);
	return  (cx > 0) && (cx < sResultSize) ? SQLITE_OK  : -1;
}

int insert_data(char* sSQL)
{
	rc_ = sqlite3_exec(db_, sSQL, callback, 0, &zErrMsg_);		
	if( rc_ !=SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", zErrMsg_);
		sqlite3_free(zErrMsg_);
	}
	assert(rc_ == SQLITE_OK );
	return rc_;
}

