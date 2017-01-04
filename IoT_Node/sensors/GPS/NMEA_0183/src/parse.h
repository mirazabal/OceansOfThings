#ifndef INC_NMEA_PARSE_H
#define INC_NMEA_PARSE_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#ifndef __USE_XOPEN
	#define __USE_XOPEN
#endif

#ifndef  _GNU_SOURCE
	#define _GNU_SOURCE
#endif

#include <time.h>

#include "parser_types.h"
#include "hash.h"
#include "base_sentence.h"


#define NMEA_TIME_FORMAT	"%H%M%S"
#define NMEA_TIME_FORMAT_LEN	6

#define NMEA_DATE_FORMAT	"%d%m%y"
#define NMEA_DATE_FORMAT_LEN	6

int _is_value_set(char const *value);

char *_crop_sentence(char* sentence, size_t length);

int _split_string_by_comma(char const* source, size_t sourceSize, char **values, size_t max_values);

nmea_parser_module_t *nmea_get_parser_by_type(nmea_t type);

nmea_parser_module_t *nmea_get_parser_by_sentence(char const*sentence);

nmea_t nmea_get_type(char const*sentence);

uint8_t nmea_get_checksum(char const*sentence);

int nmea_has_checksum(char const* sentence, size_t length);

int nmea_validate(char const*sentence, size_t length, int check_checksum);

int nmea_position_parse(char *s, nmea_position *pos);

nmea_cardinal_t nmea_cardinal_direction_parse(char *s);

int nmea_time_parse(char *s, struct tm *time);

int nmea_date_parse(char *s, struct tm *time);


extern nmea_parser_module_t **parsers;
extern hashtable_t *hashtable; // = ht_create( 65536 );
extern int n_parsers;

#endif  /* INC_NMEA_PARSE_H */
