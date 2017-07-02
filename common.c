//
// Created by leorik on 02.07.2017.
//

#include <stddef.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <mem.h>
#include "common.h"

const char *BASE_64_ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

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

char* bytesToByteStr(const byte* bytes, size_t bytesAmount) {
    char* byteStr = calloc((bytesAmount * 2) + 1, sizeof(char));
    for (uint idx = 0; idx < bytesAmount; idx++) {
        uint strIdx = idx * 2;
        byte byte = *(bytes + idx);
        sprintf(byteStr + strIdx, "%.2x", byte);
    }

    return byteStr;
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
        byte secondCode = (byte) (((firstOctet & 0x3) << 4) | (secondOctet >> 4));
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

        byte thirdCode = (byte) (((secondOctet & 0xF) << 2) | (thirdOctet >> 6));
        *(base64Str + base64CharIdx) = BASE_64_ALPHABET[thirdCode];

        if (base64Len < ++base64CharIdx)
            return RESULT_NOT_OK;

        if (!thirdIdxInRange) break;

        byte fourthCode = (byte) (thirdOctet & 0x3F);
        *(base64Str + base64CharIdx) = BASE_64_ALPHABET[fourthCode];

        if (base64Len < ++base64CharIdx)
            return RESULT_NOT_OK;
    }

    return RESULT_OK;
}