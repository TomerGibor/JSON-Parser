#include "parser.h"


KEY* make_keys_list(char* text, int text_length){
    KEY *head = NULL, *cur = NULL, *new = NULL;
    char* c = text, *json_child_start = NULL;
    int key_length = 0, json_child_length = 0, last_character_backslash = 0;

    for (int i = 0; i < text_length; i++, c++) {
        if(*c == '\\')
            last_character_backslash = 1;
        if(*c == '"' && !last_character_backslash){
            if((key_length = is_key(c, text + text_length)) == -1)
                continue;
            new = (KEY*) calloc(1, sizeof(KEY));
            new->start = c + 1; // skip double quote
            new->length = key_length;
            // skip also start and end double quote and colon when passing end pos of key
            new->is_array = is_value_array(c + key_length + 3);
            if((json_child_start = is_value_json_object(c + key_length + 3,
                    &json_child_length)) != NULL){
                new->child = make_keys_list(json_child_start, json_child_length);
                c += json_child_length; // skip child keys so as not to include them twice
            }
            if(head == NULL){ // first key in list
                head = new;
                cur = head;
            }else{
                cur->next = new;
                cur = new;
            }
        }
        if(*c != '\\')
            last_character_backslash = 0;
    }
    return head;
}


// if is key, returns key length, otherwise, returns -1
int is_key(char* start_pos, const char* end_of_text){
    int length = 0;
    start_pos++; // skip opening double quote
    // not allowing escape characters in keys so continue until double quote
    while(*(start_pos++) != '"' && start_pos <= end_of_text)
        length++;
    if(*(start_pos) != ':')
        length = -1; // key must end with colon, otherwise it's just a string
    return length;
}

int is_value_array(char* end_pos_of_key){
    while(is_space_character(*end_pos_of_key))
        end_pos_of_key++; // if space character, continue to next character
    if(*end_pos_of_key == '[')
        return 1; // value is array
    else
        return 0; // other kind of value, not an array
}

// if value is JSON object, returns start position of object, otherwise, returns NULL
char* is_value_json_object(char* end_pos_of_key, int* length) {
    unsigned int num_opening_curly_brackets = 0, last_character_backslash = 0, in_string = 0;
    char* start = NULL;

    while (1) {
        if(is_space_character(*end_pos_of_key))
            end_pos_of_key++; // if space character, continue to next character
        else if (*end_pos_of_key == '{') {
            start = end_pos_of_key++;
            num_opening_curly_brackets = 1;
            while (num_opening_curly_brackets != 0) {
                switch (*end_pos_of_key) {
                    case '\\':
                        last_character_backslash = 1; // account for escaped double quote
                        break;
                    case '"':
                        if(!last_character_backslash)
                            in_string ^= 1;
                        break;
                    case '{':
                        if(!in_string)
                            num_opening_curly_brackets++;
                        break;
                    case '}':
                        if (!in_string)
                            num_opening_curly_brackets--;
                        break;
                }
                if(*end_pos_of_key != '\\')
                    last_character_backslash = 0;
                (*length)++;
                end_pos_of_key++;
            }
            return start; // return start position of JSON object
        } else
            return NULL; // other kind of value, not an object
    }
}
