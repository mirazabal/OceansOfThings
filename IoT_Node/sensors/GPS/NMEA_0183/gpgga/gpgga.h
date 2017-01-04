#ifndef INC_NMEA_GPGGA_H
#define INC_NMEA_GPGGA_H

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../src/nmea.h"

/* Value indexes */
#define NMEA_GPGGA_TIME			0
#define NMEA_GPGGA_LATITUDE		1
#define NMEA_GPGGA_LATITUDE_CARDINAL	2
#define NMEA_GPGGA_LONGITUDE		3
#define NMEA_GPGGA_LONGITUDE_CARDINAL	4
#define NMEA_GPGGA_N_SATELLITES		6
#define NMEA_GPGGA_ALTITUDE		8
#define NMEA_GPGGA_ALTITUDE_UNIT	9

struct nmea_gpgga_s {
	nmea_t base;
	struct tm time;
	nmea_position longitude;
	nmea_position latitude;
	int n_satellites;
	int altitude;
	char altitude_unit;
};

typedef struct nmea_gpgga_s nmea_gpgga_t;


int init_GPGGA(nmea_parser_t *parser);

int allocate_data_GPGGA(nmea_parser_t *parser);

int set_default_GPGGA(nmea_parser_t *parser);

int parse_GPGGA(nmea_parser_t *parser, char *value, int val_index);

int free_data_GPGGA(nmea_basic_t *data);

#endif  /* INC_NMEA_GPGGA_H */

