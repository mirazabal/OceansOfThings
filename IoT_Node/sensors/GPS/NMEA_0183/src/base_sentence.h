#ifndef BASE_SENTENCE_NMEA_H
#define BASE_SENTENCE_NMEA_H

#include "parser_types.h"

typedef int (*allocate_data_f) (nmea_parser_t *);
typedef int (*set_default_f) (nmea_parser_t *);
typedef int (*free_data_f) (nmea_basic_t *);
typedef int (*parse_f) (nmea_parser_t *, char *, int);

struct nmea_parser_module_s {
	nmea_parser_t parser;
	int errors;
	void *handle;

	/* Functions */
	allocate_data_f allocate_data;
	set_default_f set_default;
	free_data_f free_data;
	parse_f parse;
};

typedef struct nmea_parser_module_s nmea_parser_module_t;

typedef int (*init_f) (nmea_parser_t *);


#endif //  BASE_SENTENCE_NMEA_H

