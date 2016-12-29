#ifndef INC_NMEA_H
#define INC_NMEA_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "parser_types.h"
#include "base_sentence.h"

void nmea_init();

void nmea_cleanup();

void nmea_register_parse(nmea_parser_module_t *parser);

nmea_parser_module_t *nmea_get_parse( nmea_t parse);

nmea_basic_t *nmea_parse(char const* sentence, size_t length, int check_checksum);

void nmea_free(nmea_basic_t *data);

#endif  /* INC_NMEA_H */
