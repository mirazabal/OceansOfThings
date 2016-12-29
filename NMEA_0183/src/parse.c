#include "parse.h"
#include "hash.h"

#define ARRAY_LENGTH(a) (sizeof a / sizeof (a[0]))

#ifndef __USE_XOPEN
	#define __USE_XOPEN
#endif

#ifndef _GNU_SOURCE
	#define _GNU_SOURCE
#endif



nmea_parser_module_t **parsers;
hashtable_t *hashtable; // = ht_create( 65536 );
int n_parsers;



int _is_value_set(const char *value)
{
	if (NULL == value || '\0' == *value) {
		return -1;
	}

	return 0;
}

char *_crop_sentence(char* sentence, size_t length)
{
	/* Skip type word, 7 characters (including $ and ,) */
	sentence += NMEA_PREFIX_LENGTH + 2;

	/* Null terminate before end of line/sentence, 2 characters */
	sentence[length - 9] = '\0';

	/* Remove checksum, if there is one */
	if ('*' == sentence[length - 12]) {
		sentence[length - 12] = '\0';
	}

	return sentence;
}

int _split_string_by_comma(char const* source, size_t sourceSize, char **values, size_t max_values)
{
	int i = 0;
	
	char* str = (char*)malloc(sourceSize);
	strncpy(str,source, sourceSize);

	values[i++] = str;
	while (i < max_values && NULL != (str = strchr(str, ','))) {
		*str = '\0';
		values[i++] = ++str;
	}
	free(str);
	return i;
}


nmea_parser_module_t *nmea_get_parser_by_type(nmea_t type)
{
	return ht_get(hashtable, (char*)TYPE_STRING[type]);
//	return parsers[(int) type - 1];
}

nmea_parser_module_t *nmea_get_parser_by_sentence(const char *sentence)
{
	char prefix[] = "NMEA_";
	char* substr = (char*)malloc(sizeof(char) * (NMEA_PREFIX_LENGTH + 1)) ;

	strncpy(substr, sentence + 1, NMEA_PREFIX_LENGTH);
	substr[NMEA_PREFIX_LENGTH] = '\0';

    char *new_str = (char*)malloc(strlen(prefix)+strlen(substr)+1);
	new_str[0] = '\0';
	strcat(new_str,prefix);
    strcat(new_str,substr);
	
	nmea_parser_module_t *parser;
	parser = ht_get(hashtable ,new_str);	
	free(substr);	
	free(new_str);

	return parser;

	/*
	for (i = 0; i < n_parsers; i++) {
		if (NULL == (parser = parsers[i])) {
			continue;
		}

		if (0 == strncmp(sentence + 1, TYPE_STRING[parser->parser.type], NMEA_PREFIX_LENGTH)) {
			return parser;
		}
	}
*/
//	return (nmea_parser_module_s *) NULL;
}


nmea_t nmea_get_type(const char *sentence)
{
	nmea_parser_module_t *parser = nmea_get_parser_by_sentence(sentence);
	if (NULL == parser) {
		return NMEA_UNKNOWN;
	}

	return parser->parser.type;
}

uint8_t nmea_get_checksum(const char *sentence)
{
	const char *n = sentence + 1;
	uint8_t chk = 0;

	/* While current char isn't '*' or sentence ending (newline) */
	while ('*' != *n && NMEA_END_CHAR_1 != *n && '\0' != *n) {
		chk ^= (uint8_t) *n;
		n++;
	}

	return chk;
}

int nmea_has_checksum(const char *sentence, size_t length)
{
	if ('*' == sentence[length - 5]) {
		return 0;
	}

	return -1;
}

int nmea_validate(const char *sentence, size_t length, int check_checksum)
{
	const char *n;

	/* should have atleast 9 characters */
	if (9 > length) {
		return -1;
	}

	/* should be less or equal to 82 characters */
	if (NMEA_MAX_LENGTH < length) {
		return -1;
	}

	/* should start with $ */
	if ('$' != *sentence) {
		return -1;
	}

	/* should end with \r\n, or other... */
	if ('\n' != sentence[length - 1] || '\n' != sentence[length - 2]) {
		return -1;
	}

	/* should have a 5 letter, uppercase word */
	n = sentence;
	while (++n < sentence + 6) {
		if (*n < 'A' || *n > 'Z') {
			/* not uppercase letter */
			return -1;
		}
	}

	/* should have a comma after the type word */
	if (',' != sentence[6]) {
		return -1;
	}

	/* check for checksum */
	if (1 == check_checksum && 0 == nmea_has_checksum(sentence, length)) {
		uint8_t actual_chk;
		uint8_t expected_chk;
		char checksum[3];

		checksum[0] = sentence[length - 4];
		checksum[1] = sentence[length - 3];
		checksum[2] = '\0';
		actual_chk = nmea_get_checksum(sentence);
		expected_chk = (uint8_t) strtol(checksum, NULL, 16);
		if (expected_chk != actual_chk) {
			return -1;
		}
	}

	return 0;
}

////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

int nmea_position_parse(char *s, nmea_position *pos)
{
	char *cursor;

	pos->degrees = 0;
	pos->minutes = 0;

	if (s == NULL || *s == '\0') {
		return -1;
	}

	/* decimal minutes */
	if (NULL == (cursor = strchr(s, '.'))) {
		return -1;
	}

	/* minutes starts 2 digits before dot */
	cursor -= 2;
	pos->minutes = atof(cursor);
	*cursor = '\0';

	/* integer degrees */
	cursor = s;
	pos->degrees = atoi(cursor);

	return 0;
}

nmea_cardinal_t nmea_cardinal_direction_parse(char *s)
{
	if (NULL == s || '\0'== *s) {
		return NMEA_CARDINAL_DIR_UNKNOWN;
	}

	switch (*s) {
	case NMEA_CARDINAL_DIR_NORTH:
		return NMEA_CARDINAL_DIR_NORTH;
	case NMEA_CARDINAL_DIR_EAST:
		return NMEA_CARDINAL_DIR_EAST;
	case NMEA_CARDINAL_DIR_SOUTH:
		return NMEA_CARDINAL_DIR_SOUTH;
	case NMEA_CARDINAL_DIR_WEST:
		return NMEA_CARDINAL_DIR_WEST;
	default:
		break;
	}

	return NMEA_CARDINAL_DIR_UNKNOWN;
}

int nmea_time_parse(char *s, struct tm *time)
{
	char *rv;

	memset(time, 0, sizeof (struct tm));

	if (s == NULL || *s == '\0') {
		return -1;
	}

	rv = strptime(s, NMEA_TIME_FORMAT, time);
	if (NULL == rv || (int) (rv - s) != NMEA_TIME_FORMAT_LEN) {
		return -1;
	}

	return 0;
}

int nmea_date_parse(char *s, struct tm *time)
{
	char *rv;

	// Assume it has been already cleared
	// memset(time, 0, sizeof (struct tm));

	if (s == NULL || *s == '\0') {
		return -1;
	}

	rv = strptime(s, NMEA_DATE_FORMAT, time);
	if (NULL == rv || (int) (rv - s) != NMEA_DATE_FORMAT_LEN) {
		return -1;
	}

	return 0;
}

