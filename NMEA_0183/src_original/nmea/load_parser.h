#ifndef INC_NMEA_LOAD_PARSER_H
#define INC_NMEA_LOAD_PARSER_H

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <dlfcn.h>
#include "nmea.h"
#include "parser_types.h"

/**
 * Load the parser libs into array.
 *
 * Returns 0 on success, or -1 if an error occurs.
 */
int nmea_load_parsers();

/**
 * Unload all the parser libs.
 */
void nmea_unload_parsers();

/**
 * Initiate a parser.
 *
 * Returns a sentence parser struct, or (nmea_parser_module_s *) NULL if an error occurs.
 */
nmea_parser_module_s *nmea_init_parser(const char *filename);

/**
 * Get a parser for a sentence type.
 *
 * Returns the sentence parser struct, should be checked for NULL.
 */
nmea_parser_module_s *nmea_get_parser_by_type(nmea_t type);

/**
 * Get a parser for a sentence type by a sentence string.
 *
 * Returns the sentence parser struct, should be checked for NULL.
 */
nmea_parser_module_s *nmea_get_parser_by_sentence(const char *sentence);

#endif  /* INC_NMEA_PARSER_H */
