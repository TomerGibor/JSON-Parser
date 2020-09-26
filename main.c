/*
 * Written by Tomer Gibor 26-Sep-20.
 */
#include <stdio.h>
#include <string.h>
#include "types.h"
#include "parser.h"
#include "file_operations.h"
#include "printers.h"
#define MAX_KEYS_LENGTH 64
#define EXIT "exit"
#define HELP "help"

void free_keys(KEY* head){
    KEY *cur = head, *next = NULL;

    while(cur != NULL){
        next = cur->next;
        free(cur);
        cur = next;
    }
}

int main(int argc, char* argv[]) {
    int file_size = 0;
    char* file_text = NULL;
    KEY* keys = NULL;
    char received_keys[MAX_KEYS_LENGTH];

    if(argc != 2){
        printf("USAGE: %s <file_name>", argv[0]);
        return 0;
    }

    file_text = open_file(argv[1], &file_size);
    if(file_text == NULL)
        return 0;

    keys = make_keys_list(file_text, file_size);
    if(keys == NULL){
        perror("Empty file!\n");
        return 0;
    }

    printf("Welcome to my JSON parser!\n");
    printf("To exit, type \"exit\". If you need help, type \"help\"\n");
    printf("$JSON-parser: enter key (if nested keys, separated by \"->\")\n");
    while(1){
        memset(received_keys, 0, MAX_KEYS_LENGTH); // empty out old received keys
        printf("$JSON-parser: ");
        fgets(received_keys, MAX_KEYS_LENGTH, stdin);
        if(strncmp(received_keys, EXIT, sizeof(EXIT) - 1) == 0){
            printf("Thanks for choosing my JSON parser, have a nice day!");
            break;
        }
        else if(strncmp(received_keys, HELP, sizeof(HELP) - 1) == 0){
            printf("$JSON-parser: enter key (if nested keys, separated by \"->\")\n");
        }
        else // input is keys
            print_value_by_key(keys, received_keys);


    }
    free(file_text);
    free_keys(keys);
    return 1;
}