cmake_minimum_required(VERSION 3.5)
project(Comilao)

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES main.c board.c board.h utils.c utils.h list.c list.h file.c file.h)
add_executable(Comilao ${SOURCE_FILES})