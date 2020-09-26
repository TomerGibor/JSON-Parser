#include "file_operations.h"


char* open_file(char path[], int* size){
    FILE* fp = NULL;
    char* file_content = NULL;

    if((fp = fopen(path, READ_MODE)) == NULL){
        perror("Error opening file!\n");
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    *size = (int) ftell(fp);
    fseek(fp, 0, SEEK_SET);
    file_content = (char*) calloc((*size) + 1, sizeof(char));
    fread(file_content, *size, 1, fp);
    *(file_content + *size) = '\0';
    fclose(fp);
    return file_content;
}
