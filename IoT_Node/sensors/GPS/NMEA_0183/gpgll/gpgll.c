#include "gpgll.h"
#include "../src/parse.h"


int init_GPGLL(nmea_parser_t *parser)
{
	/* Declare what sentence type to parse */
	NMEA_PARSER_TYPE(parser, NMEA_GPGLL);
	NMEA_PARSER_PREFIX(parser, "GPGLL");
	return 0;
}

int allocate_data_GPGLL(nmea_parser_t *parser)
{
	parser->data = (nmea_basic_t*)malloc(sizeof (nmea_gpgll_t));
	if (NULL == parser->data) {
		return -1;
	}
	return 0;
}

int set_default_GPGLL(nmea_parser_t *parser)
{
	memset(parser->data, 0, sizeof (nmea_gpgll_t));
	return 0;
}

int free_data_GPGLL(nmea_basic_t *data)
{
	free(data);
	return 0;
}

int parse_GPGLL(nmea_parser_t *parser, char *value, int val_index)
{
	nmea_gpgll_t *data = (nmea_gpgll_t *) parser->data;

	switch (val_index) {
	case NMEA_GPGLL_TIME:
		/* Parse time */
		if (-1 == nmea_time_parse(value, &data->time)) {
			return -1;
		}
		break;

	case NMEA_GPGLL_LATITUDE:
		/* Parse latitude */
		if (-1 == nmea_position_parse(value, &data->latitude)) {
			return -1;
		}
		break;

	case NMEA_GPGLL_LATITUDE_CARDINAL:
		/* Parse cardinal direction */
		data->latitude.cardinal = nmea_cardinal_direction_parse(value);
		if (NMEA_CARDINAL_DIR_UNKNOWN == data->latitude.cardinal) {
			return -1;
		}
		break;

	case NMEA_GPGLL_LONGITUDE:
		/* Parse longitude */
		if (-1 == nmea_position_parse(value, &data->longitude)) {
			return -1;
		}
		break;

	case NMEA_GPGLL_LONGITUDE_CARDINAL:
		/* Parse cardinal direction */
		data->longitude.cardinal = nmea_cardinal_direction_parse(value);
		if (NMEA_CARDINAL_DIR_UNKNOWN == data->longitude.cardinal) {
			return -1;
		}
		break;

	default:
		break;
	}
	return 0;
}

