#pragma once
#include <stdlib.h>
#include "types.h"
#include "utils.h"

KEY* make_keys_list(char* text, int text_length);

int is_key(char* start_pos, const char* end_of_text);

int is_value_array(char* end_pos_of_key);

char* is_value_json_object(char* end_pos_of_key, int* length);