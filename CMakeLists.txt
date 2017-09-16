cmake_minimum_required(VERSION 3.7)
project(cryptopals)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c set1/base64.c set1/base64.h common.c common.h set1/xor.c set1/xor.h set1/xorCipher.c set1/xorCipher.h set1/xorListCipher.c set1/xorListCipher.h)
add_executable(cryptopals ${SOURCE_FILES})