#ifndef INC_NMEA_GPGLL_H
#define INC_NMEA_GPGLL_H

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../src/parse.h"

/* Value indexes */
#define NMEA_GPGLL_LATITUDE		0
#define NMEA_GPGLL_LATITUDE_CARDINAL	1
#define NMEA_GPGLL_LONGITUDE		2
#define NMEA_GPGLL_LONGITUDE_CARDINAL	3
#define NMEA_GPGLL_TIME			4




struct nmea_gpgll_s {
	nmea_basic_t base;
	nmea_position longitude;
	nmea_position latitude;
	struct tm time;
};

typedef struct nmea_gpgll_s nmea_gpgll_t;


int init_GPGLL(nmea_parser_t *parser);

int allocate_data_GPGLL(nmea_parser_t *parser);

int set_default_GPGLL(nmea_parser_t *parser);

int parse_GPGLL(nmea_parser_t *parser, char *value, int val_index);

int free_data_GPGLL(nmea_basic_t *data);




#endif  /* INC_NMEA_GPGLL_H */
