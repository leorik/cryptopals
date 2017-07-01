//
// Problem 1
// https://cryptopals.com/sets/1/challenges/1
//
// Created by leorik on 27.06.2017.
//

#include "base64.h"
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

const char *BASE_64_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

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

FUNC_RESULT byteStrToBytes(const char *str, byte *result, size_t resultLen) {
    for (int idx = 0; idx < resultLen; idx++) {
        int correctedIdx = idx * 2;
        char* hexByte = malloc(2);
        *hexByte = str[correctedIdx];
        *(hexByte+1) = str[correctedIdx+1];

        *(result + idx) = (byte) strtol(hexByte, 0, 16);
        free(hexByte);
    }

    return RESULT_OK;
}

size_t getBase64Len(size_t bytesAmount) {
    return bytesAmount + (bytesAmount/3);
}

FUNC_RESULT bytesToBase64(const byte *bytes, const size_t bytesAmount, char *base64Str) {
    size_t base64Len = getBase64Len(bytesAmount);
    uint base64CharIdx = 0;
    for (size_t idx = 0; idx < (bytesAmount/3); idx++) {
        size_t operationalIdx = idx * 3;

        byte firstOctet = *(bytes + operationalIdx);
        byte firstCode = firstOctet >> 2;
        *(base64Str + base64CharIdx) = BASE_64_ALPHABET[firstCode];

        if (base64Len < ++base64CharIdx)
            return RESULT_NOT_OK;

        size_t secondIdx = operationalIdx + 1;

        if (secondIdx >= bytesAmount) break;

        byte secondOctet = *(bytes + secondIdx);
        byte secondCode = (byte) (((firstOctet & 3) << 4) | (secondOctet >> 4));
        *(base64Str + base64CharIdx) = BASE_64_ALPHABET[secondCode];

        if (base64Len < ++base64CharIdx)
            return RESULT_NOT_OK;

        size_t thirdIdx = operationalIdx + 2;
        bool thirdIdxInRange = thirdIdx < bytesAmount;

        byte thirdOctet;

        if (thirdIdxInRange) {
            thirdOctet = *(bytes + thirdIdx);
        } else {
            thirdOctet = 0;
        }

        byte thirdCode = (byte) (((secondOctet & 15) << 2) | (thirdOctet >> 6));
        *(base64Str + base64CharIdx) = BASE_64_ALPHABET[thirdCode];

        if (base64Len < ++base64CharIdx)
            return RESULT_NOT_OK;

        if (!thirdIdxInRange) break;

        byte fourthCode = (byte) (thirdOctet & 63);
        *(base64Str + base64CharIdx) = BASE_64_ALPHABET[fourthCode];

        if (base64Len < ++base64CharIdx)
            return RESULT_NOT_OK;
    }

    return RESULT_OK;
}

int compareStrings(const char *str1, const char *str2) {
    size_t strlen1 = strlen(str1);
    size_t strlen2 = strlen(str2);

    if (strlen1 != strlen2) {
        printf("Length mismatch: %d and %d\n", strlen1, strlen2);
    }
    size_t nominalLen;

    if (strlen1 < strlen2) {
        nominalLen = strlen1;
    } else {
        nominalLen = strlen2;
    }

    for (size_t i = 0; i < nominalLen; i++) {
        char ch1 = *(str1 + i);
        char ch2 = *(str2 + i);
        if (ch1 != ch2) {
            printf("Mismatch from symbol %d: %c and %c", i, ch1, ch2);

            return EXIT_SUCCESS;
        }
    }

    printf("Strings match");
    return EXIT_SUCCESS;
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



