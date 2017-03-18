#include "nmea.h"
#include "hash.h"
#include "parse.h"


#define ARRAY_LENGTH(a) (sizeof a / sizeof (a[0]))
/**
 * Initiate the NMEA library and load the parser modules.
 *
 * This function will be called before the main() function.
 */
void __attribute__ ((constructor)) nmea_init(void);
void nmea_init()
{
	hashtable = ht_create(5000);
//	nmea_load_parsers();
}

/**
 * Unload the parser modules.
 *
 * This function will be called after the exit() function.
 */
void __attribute__ ((destructor)) nmea_cleanup(void);
void nmea_cleanup()
{
//	nmea_unload_parsers();
}

void nmea_free(nmea_basic_t *data)
{
	nmea_parser_module_t *parser;

	if (NULL == data) {
		return;
	}

	parser = nmea_get_parser_by_type(data->type);
	if (NULL == parser) {
		return;
	}

	parser->free_data(data);
}

void nmea_register_parse(nmea_parser_module_t *p)
{
	ht_set( hashtable , (char*)TYPE_STRING[p->parser.type] , p);
}

nmea_parser_module_t *nmea_get_parse(nmea_t t)
{
	return ht_get(hashtable, (char*)TYPE_STRING[t]);
}


nmea_basic_t *nmea_parse(char const *sentence, size_t length, int check_checksum)
{
	size_t n_vals, val_index;
	char *value;
	char *values[255];
	nmea_parser_module_t *parser;
	nmea_t type;

	/* Validate sentence string */
	if (-1 == nmea_validate(sentence, length, check_checksum)) {
		return (nmea_basic_t*) NULL;
	}

	type = nmea_get_type(sentence);
	if (NMEA_UNKNOWN == type) {
		return (nmea_basic_t*) NULL;
	}

	/* Crop sentence from type word and checksum */
	char* val_string = _crop_sentence((char*)sentence, length);
	if (NULL == val_string) {
		return (nmea_basic_t*) NULL;
	}

	/* Split the sentence into values */
	n_vals = _split_string_by_comma(val_string, length, values, ARRAY_LENGTH(values));
	if (0 == n_vals) {
		return (nmea_basic_t*) NULL;
	}

	/* Get the right parser */
	parser = nmea_get_parser_by_type(type);
	if (NULL == parser) {
		return (nmea_basic_t*) NULL;
	}

	/* Allocate memory for parsed data */
	parser->allocate_data((nmea_parser_t *) parser);
	if (NULL == parser->parser.data) {
		return (nmea_basic_t*) NULL;
	}

	/* Set default values */
	parser->set_default((nmea_parser_t *) parser);
	parser->errors = 0;

	/* Loop through the values and parse them... */
	for (val_index = 0; val_index < n_vals; val_index++) {
		value = values[val_index];
		if (-1 == _is_value_set(value)) {
			continue;
		}

		if (-1 == parser->parse((nmea_parser_t *) parser, value, val_index)) {
			parser->errors++;
		}
	}

	parser->parser.data->type = type;
	parser->parser.data->errors = parser->errors;

	return parser->parser.data;
}

