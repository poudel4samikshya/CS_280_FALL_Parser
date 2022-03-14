cmake_minimum_required(VERSION 3.17)
project(CS_280_FALL_Parser)

set(CMAKE_CXX_STANDARD 11)

add_executable(CS_280_FALL_Parser main.cpp lex.cpp parse.cpp lex.h parse.h)