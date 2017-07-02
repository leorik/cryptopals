// Problem 3
// https://cryptopals.com/sets/1/challenges/3
//
// Created by leorik on 02.07.2017.
//

#include <stddef.h>
#include <mem.h>
#include <malloc.h>
#include <stdio.h>
#include "xorCipher.h"
#include "../common.h"

const char* MOST_OCCURRENT_ENGLISH_CHARS = "ETAOIN SHRDLUetaoinshrdlu";

uint countOccurrencesForByte(byte *bytes, size_t bytesAmount, byte byteChar) {
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

byte* testByteAgainstChar(byte* cipherBytes, size_t bytesAmount, byte mostOccurrentByte, char englishChar) {
    printf("Testing byte %.2x for char '%c':\n", mostOccurrentByte, englishChar);
    byte key = mostOccurrentByte ^ englishChar;
    printf("Assuming key %.2x\n", key);

    byte *decipheredText = calloc(bytesAmount + 1, sizeof(byte));
    for (uint idx = 0; idx < bytesAmount; idx++) {
        byte decipheredByte = *(cipherBytes + idx) ^key;

        if (decipheredByte > 0x1F && decipheredByte < 0x7E) {
            *(decipheredText + idx) = decipheredByte;
        } else {
            printf("Key failed for symbol %.2x\n\n", decipheredByte);
            free(decipheredText);
            return NULL;
        }
    }

    return decipheredText;
}

int xorCipherTest() {
    char* cipherText = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
    printf("Cipher text: %s\n", cipherText);

    size_t cipherBytesAmount = strlen(cipherText) / 2;
    void *cipherBytes = malloc(cipherBytesAmount);
    if (byteStrToBytes(cipherText, cipherBytes, cipherBytesAmount) != RESULT_OK)
        return 1;

    byte mostOccurringByte = findMostOccurringByte(cipherBytes, cipherBytesAmount);

    printf("Most occurrent byte for cipher text: %.2x\n", mostOccurringByte);

    size_t charsCount = strlen(MOST_OCCURRENT_ENGLISH_CHARS);

    byte* decipheredText = NULL;
    for (uint idx = 0; idx < charsCount; idx++) {
        byte *testResult = testByteAgainstChar(cipherBytes, cipherBytesAmount, mostOccurringByte, *(MOST_OCCURRENT_ENGLISH_CHARS + idx));

        if (testResult != NULL) {
            decipheredText = testResult;
            break;
        }
    }

    if (decipheredText != NULL) {
        printf("Deciphered text: %s", decipheredText);
        free(decipheredText);
    } else {
        printf("Deciphiring failed, key not found");
    }

    return 0;
}
