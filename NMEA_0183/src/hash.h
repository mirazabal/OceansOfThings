#ifndef INC_HASH_H
#define INC_HASH_H

//#define _XOPEN_SOURCE 500 /* Enable certain library functions (strdup) on linux.  See feature_test_macros(7) */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "parser_types.h"
#include "base_sentence.h"

struct entry_s {
	char *key;
	nmea_parser_module_t *value;
	struct entry_s *next;
};

typedef struct entry_s entry_t;

struct hashtable_s {
	int size;
	struct entry_s **table;	
};

typedef struct hashtable_s hashtable_t;


hashtable_t *ht_create( int size );

int ht_hash( hashtable_t *hashtable, char *key );

entry_t *ht_newpair( char *key, nmea_parser_module_t *value );

void ht_set( hashtable_t *hashtable, char *key, nmea_parser_module_t *value );

nmea_parser_module_t *ht_get( hashtable_t *hashtable, char *key );

#endif // HASH_H

