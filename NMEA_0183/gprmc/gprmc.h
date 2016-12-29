#ifndef INC_NMEA_GPRMC_H
#define INC_NMEA_GPRMC_H

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../src/nmea.h"

/* Value indexes */
#define NMEA_GPRMC_LATITUDE		2
#define NMEA_GPRMC_LATITUDE_CARDINAL	3
#define NMEA_GPRMC_LONGITUDE		4
#define NMEA_GPRMC_LONGITUDE_CARDINAL	5
#define NMEA_GPRMC_TIME			0
#define NMEA_GPRMC_DATE			8


struct  nmea_gprmc_s{
	nmea_t base;
	nmea_position longitude;
	nmea_position latitude;
	struct tm time;
};

typedef struct nmea_gprmc_s nmea_gprmc_t;

int init_GPRMC(nmea_parser_t *parser);

int allocate_data_GPRMC(nmea_parser_t *parser);

int set_default_GPRMC(nmea_parser_t *parser);

int parse_GPRMC(nmea_parser_t *parser, char *value, int val_index);

int free_data_GPRMC(nmea_basic_t *data);

#endif  /* INC_NMEA_GPRMC_H */
