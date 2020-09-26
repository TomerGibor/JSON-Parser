cmake_minimum_required(VERSION 3.10)
project(JSON_Parser C)

set(CMAKE_C_STANDARD 11)

add_executable(JSON_Parser main.c types.h parser.c parser.h file_operations.c file_operations.h printers.c printers.h utils.c utils.h)