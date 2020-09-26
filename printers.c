#include "printers.h"

void print_value_by_key(KEY* keys, char* received_keys){
    char* token = NULL;

    received_keys = strdup(received_keys); // strtok must receive a string which it can write on
    token = strtok(received_keys, DELIM); // get first token

    for (KEY* key = keys; key!= NULL;) { // loop over keys
        if(strncmp(key->start, token, key->length) == 0){
            token = strtok(NULL, DELIM); // get next token
            if(token == NULL){ // reached final key
                if(key->is_array)
                    print_array_or_object(key, SQUARE); // print array
                else if(key->child != NULL)
                    print_array_or_object(key, CURLY); // print object
                else
                    print_normal_value(key);
                return;
            }else{
                key = key->child;
            }
        }
        else
            key = key->next;
    }
    printf("Key not found!\n");
}

void print_normal_value(KEY* key){
    unsigned int chars_to_print = 0, in_string = 0, last_char_backslash = 0;
    char* start_pos = key->start + key->length + 1; // skip also end double quote
    char* pos = NULL;

    while(is_space_character(*start_pos) || *start_pos == ':')
        start_pos++; // skip space characters and colon

    pos = start_pos;
    // loop until reached comma (separating key-value pairs) or end of object
    while(!(!in_string && (*pos == ',' || *pos == '}'))){
        if(*pos == '\\')
            last_char_backslash = 1; // account for escaped double quote
        if(*pos == '"' && !last_char_backslash)
            in_string ^= 1;
        if(*pos != '\\')
            last_char_backslash = 0;
        chars_to_print++;
        pos++;
    }
    printf("%.*s\n", chars_to_print, start_pos);
}

void print_array_or_object(KEY* key, enum BRACKET bracket){
    unsigned int chars_to_print = 0, in_string = 0, last_char_backslash = 0, num_brackets = 1;
    char* start_pos = key->start + key->length + 1; // skip also end double quote
    char* pos = NULL;

    while(is_space_character(*start_pos) || *start_pos == ':')
        start_pos++; // skip space characters and colon

    pos = start_pos;
    pos++; // skip first opening bracket
    while(num_brackets != 0){
        if(*pos == '\\')
            last_char_backslash = 1; // account for escaped double quote
        else if(*pos == '"' && !last_char_backslash)
            in_string ^= 1;
        if(!in_string && *pos == (bracket==CURLY ? '{' : '['))
            num_brackets++;
        else if(!in_string && *pos == (bracket==CURLY ? '}' : ']'))
            num_brackets--;
        if(*pos != '\\')
            last_char_backslash = 0;
        chars_to_print++;
        pos++;
    }
    chars_to_print++; // print also end bracket
    printf("%.*s\n", chars_to_print, start_pos);
}
