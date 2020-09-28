#include "utils.h"

int is_space_character(char c){
    return c == ' ' || c == '\r' || c == '\n' || c == '\t';
}

void free_keys(KEY* head){
    KEY *cur = head, *next = NULL;

    while(cur != NULL){
        next = cur->next;
        free(cur);
        cur = next;
    }
}
