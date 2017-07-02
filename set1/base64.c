//
// Problem 1
// https://cryptopals.com/sets/1/challenges/1
//
// Created by leorik on 27.06.2017.
//

#include "base64.h"
#include "../common.h"
#include <string.h>
#include <stdlib.h>

size_t getPaddedBytesLen(size_t bytesAmount) {
    size_t bytesAmountDivisionRemainder = bytesAmount % 3;

    if (0 != bytesAmountDivisionRemainder) {
        return bytesAmount + (3 - bytesAmountDivisionRemainder);
    } else {
        return bytesAmount;
    }
}

FUNC_RESULT getHexCharsCountFromStr(const char* str, size_t* size) {
    size_t len = strlen(str);

    if (0 != (len % 2)) return RESULT_NOT_OK;

    *size = getPaddedBytesLen(len / 2);

    return RESULT_OK;
}

int base64Test() {
    char *str = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
    size_t bytesAmount;
    FUNC_RESULT countResult = getHexCharsCountFromStr(str, &bytesAmount);

    if (RESULT_NOT_OK == countResult)
        return EXIT_FAILURE;

    byte* bytes = calloc(bytesAmount, sizeof(byte));
    FUNC_RESULT bytesResult = byteStrToBytes(str, bytes, bytesAmount);

    if (RESULT_NOT_OK == bytesResult)
        return EXIT_FAILURE;

    size_t base54Len = getBase64Len(bytesAmount);

    char *base64Str = calloc(base54Len+1, sizeof(char));

    FUNC_RESULT base64ConversionResult = bytesToBase64(bytes, bytesAmount, base64Str);
    if (RESULT_NOT_OK == base64ConversionResult)
        return EXIT_FAILURE;

    compareStrings("SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t", base64Str);

    free(bytes);
    return EXIT_SUCCESS;
}



