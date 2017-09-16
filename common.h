//
// Created by leorik on 02.07.2017.
//

#ifndef CRYPTOPALS_COMMON_H
#define CRYPTOPALS_COMMON_H

#include <stddef.h>

typedef unsigned char byte;
typedef unsigned int uint;

typedef enum {RESULT_OK, RESULT_NOT_OK} FUNC_RESULT;

int compareStrings(const char *str1, const char *str2);

FUNC_RESULT byteStrToBytes(const char *str, byte *result, size_t resultLen);

char* bytesToByteStr(const byte* bytes, size_t bytesAmount);

FUNC_RESULT bytesToBase64(const byte *bytes, size_t bytesAmount, char *base64Str);

size_t getBase64Len(size_t bytesAmount);

extern const char* MOST_FREQUENT_ENGLISH_CHARS;

extern const uint ASCII_CODEPAGE_READABLE_SYMBOLS_START;

extern const uint ASCII_CODEPAGE_READABLE_SYMBOLS_END;

#endif //CRYPTOPALS_COMMON_H
