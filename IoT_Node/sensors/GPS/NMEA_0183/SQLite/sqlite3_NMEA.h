#ifndef SQLITE_NMEA_H
#define SQLITE_NMEA_H


int open_database();
int close_database();
int create_table();
int drop_table();
int create_sql_data(char const* sCommandType, char const* sCommandData, char* sResult, int const sResultSize);
int insert_data(char* sSQL);

#endif // SQLITE_NMEA_H

