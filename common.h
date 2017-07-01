//
// Created by leorik on 02.07.2017.
//

#ifndef CRYPTOPALS_COMMON_H
#define CRYPTOPALS_COMMON_H

#include "qol.h"

FUNC_RESULT byteStrToBytes(const char *str, byte *result, size_t resultLen);

FUNC_RESULT bytesToBase64(const byte *bytes, const size_t bytesAmount, char *base64Str);

size_t getBase64Len(size_t bytesAmount);

#endif //CRYPTOPALS_COMMON_H
