#pragma once

typedef struct _KEY{
    char* start;
    int length;
    struct _KEY* child;
    struct _KEY* next;
    int is_array;
} KEY;