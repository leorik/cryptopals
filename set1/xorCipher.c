// Problem 3
// https://cryptopals.com/sets/1/challenges/3
//
// Created by leorik on 02.07.2017.
//

#include <mem.h>
#include <malloc.h>
#include <stdio.h>
#include "xorCipher.h"

uint countOccurrencesForByte(const byte *bytes, size_t bytesAmount, byte byteChar) {
    uint counter = 0;
    for (uint idx = 0; idx < bytesAmount; idx++) {
        if (byteChar == *(bytes + idx)) counter++;
    }

    return counter;
}


byte findMostOccurringByte(byte *bytes, size_t bytesAmount) {
    uint mostOccurrences = 0;
    byte mostOccurrentByte = 0;

    for (uint idx = 0; idx < bytesAmount; idx++) {
        byte byteChar = *(bytes + idx);
        uint occurrences = countOccurrencesForByte(bytes, bytesAmount, byteChar);

        if (occurrences > mostOccurrences) {
            mostOccurrences = occurrences;
            mostOccurrentByte = byteChar;
        }
    }

    return mostOccurrentByte;
}

byte* testByteAgainstChar(const byte* cipherBytes, size_t bytesAmount, byte mostOccurrentByte, char englishChar) {
#ifdef VERBOSE
    printf("Testing byte %.2x for char '%c':\n", mostOccurrentByte, englishChar);
#endif

    byte key = mostOccurrentByte ^ englishChar;

#ifdef VERBOSE
    printf("Assuming key %.2x\n", key);
#endif

    byte *decipheredText = calloc(bytesAmount + 1, sizeof(byte));
    for (uint idx = 0; idx < bytesAmount; idx++) {
        byte decipheredByte = *(cipherBytes + idx) ^key;

        if (decipheredByte > ASCII_CODEPAGE_READABLE_SYMBOLS_START && decipheredByte < ASCII_CODEPAGE_READABLE_SYMBOLS_END) {
            *(decipheredText + idx) = decipheredByte;
        } else {
#ifdef VERBOSE
            printf("Key failed for symbol %.2x\n\n", decipheredByte);
#endif
            free(decipheredText);
            return NULL;
        }
    }

#ifdef VERBOSE
    printf("Code confirmed as %.2x\n", key);
#endif

    return decipheredText;
}

FUNC_RESULT tryDecipherText(char* text, byte** resultBuffer) {
    size_t cipherBytesAmount = strlen(text) / 2;
    void *cipherBytes = malloc(cipherBytesAmount);
    if (byteStrToBytes(text, cipherBytes, cipherBytesAmount) != RESULT_OK)
        return RESULT_NOT_OK;

    byte mostOccurringByte = findMostOccurringByte(cipherBytes, cipherBytesAmount);

#ifdef VERBOSE
    printf("Most frequent byte for cipher text: %.2x\n", mostOccurringByte);
#endif

    size_t charsCount = strlen(MOST_FREQUENT_ENGLISH_CHARS);

    byte* decipheredText = NULL;
    for (uint idx = 0; idx < charsCount; idx++) {
        byte *testResult = testByteAgainstChar(cipherBytes, cipherBytesAmount, mostOccurringByte, *(MOST_FREQUENT_ENGLISH_CHARS + idx));

        if (testResult != NULL) {
            decipheredText = testResult;
            break;
        }
    }

    if (decipheredText != NULL) {
        *resultBuffer = decipheredText;

        return RESULT_OK;
    }

    return RESULT_NOT_OK;
}

int xorCipherTest() {
    char* cipherText = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    printf("Cipher text: %s\n", cipherText);

    byte *decipheredText = malloc(sizeof(byte*));
    const FUNC_RESULT decipheringResult = tryDecipherText(cipherText, &decipheredText);

    if (decipheringResult == RESULT_OK) {
        printf("Deciphered text: %s", decipheredText);
        free(decipheredText);
    } else {
        printf("Deciphering failed, key not found");
    }

    return 0;
}
