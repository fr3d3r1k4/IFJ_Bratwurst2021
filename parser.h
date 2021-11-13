#ifndef IFJ_BRATWURST2021_PARSER_H
#define IFJ_BRATWURST2021_PARSER_H

#include <stdbool.h>
#include "scanner.h"

#define PARSE_NO_ERR false
#define PARSE_ERR true

typedef bool parser_error_t;

typedef struct p_data {
    token_t* token;
} *p_data_ptr_t;

parser_error_t parser ();

#endif //IFJ_BRATWURST2021_PARSER_H