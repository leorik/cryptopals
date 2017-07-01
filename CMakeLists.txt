cmake_minimum_required(VERSION 3.7)
project(cryptopals)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c set1/base64.c set1/base64.h qol.h)
add_executable(cryptopals ${SOURCE_FILES})