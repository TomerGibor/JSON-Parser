cmake_minimum_required(VERSION 3.10)
project(JSON_Parser C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(JSON_Parser
        main.c
        parser.c
        parser.h
        types.h
        file_operations.c
        file_operations.h
        printers.c
        printers.h
        utils.c
        utils.h)
