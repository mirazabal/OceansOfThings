#ifndef INC_NMEA_PARSER_TYPES_B_H
#define INC_NMEA_PARSER_TYPES_B_H

/* NMEA sentence types */
//typedef enum {
//	NMEA_UNKNOWN,
//	NMEA_GPGGA,
//	NMEA_GPGLL,
//	NMEA_GPRMC
//} nmea_t;


#define FOREACH_TYPE(TYPE) \
	        TYPE(NMEA_UNKNOWN)   \
			TYPE(NMEA_GPGGA)  \
			TYPE(NMEA_GPGLL)   \
			TYPE(NMEA_GPRMC)  \

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

typedef enum{
	    FOREACH_TYPE(GENERATE_ENUM)
} nmea_t;

static const char *TYPE_STRING[] = {
	    FOREACH_TYPE(GENERATE_STRING)
};


/* NMEA cardinal direction types */
typedef char nmea_cardinal_t;
#define NMEA_CARDINAL_DIR_NORTH		(nmea_cardinal_t) 'N'
#define NMEA_CARDINAL_DIR_EAST		(nmea_cardinal_t) 'E'
#define NMEA_CARDINAL_DIR_SOUTH		(nmea_cardinal_t) 'S'
#define NMEA_CARDINAL_DIR_WEST		(nmea_cardinal_t) 'W'
#define NMEA_CARDINAL_DIR_UNKNOWN	(nmea_cardinal_t) '\0'

/**
 * NMEA data base struct
 *
 * This struct will be extended by the parser data structs (ex: nmea_gpgll_s).
 */
struct nmea_basic_s{
	nmea_t type;
	int errors;
};

typedef struct nmea_basic_s nmea_basic_t;

/* GPS position struct */
typedef struct {
	double minutes;
	int degrees;
	nmea_cardinal_t cardinal;
} nmea_position;

/* NMEA sentence max length, including \r\n (chars) */
#define NMEA_MAX_LENGTH		82

/* NMEA sentence endings, should be \r\n according the NMEA 0183 standard */
#define NMEA_END_CHAR_1		'\n'
#define NMEA_END_CHAR_2		'\n'

/* NMEA sentence prefix length (num chars), Ex: GPGLL */
#define NMEA_PREFIX_LENGTH	5


struct nmea_parser_s {
	nmea_t type;
	char type_word[5];
	nmea_basic_t *data;
};
typedef struct nmea_parser_s nmea_parser_t;

//extern int init(nmea_parser_s *parser);
//extern int allocate_data(nmea_parser_s *parser);
//extern int set_default(nmea_parser_s *parser);
//extern int free_data(nmea_s *data);
//extern int parse(nmea_parser_s *parser, char *value, int val_index);

#define NMEA_PARSER_PREFIX(parser, type_prefix) strncpy(parser->type_word, type_prefix, NMEA_PREFIX_LENGTH)
#define NMEA_PARSER_TYPE(parser, nmea_type) parser->type = nmea_type

#endif  /* INC_NMEA_PARSER_TYPES_H */
