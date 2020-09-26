#pragma once
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "utils.h"
#define DELIM "->"

enum BRACKET{CURLY, SQUARE};

void print_value_by_key(KEY* keys, char* received_keys);

void print_normal_value(KEY* key);

void print_array_or_object(KEY* key, enum BRACKET bracket);
