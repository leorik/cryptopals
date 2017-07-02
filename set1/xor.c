//
// Problem 2
// https://cryptopals.com/sets/1/challenges/2
//
// Created by leorik on 02.07.2017.
//


#include <stddef.h>
#include <mem.h>
#include <malloc.h>
#include "../common.h"

int xorTest() {
    char* firstValue = "1c0111001f010100061a024b53535009181c";
    char* secondValue = "686974207468652062756c6c277320657965";
    char* resultValue = "746865206b696420646f6e277420706c6179";

    if (strlen(firstValue) != strlen(secondValue))
        return 1;

    size_t byteAmount = strlen(firstValue) / 2;

    byte *firstBytes = malloc(byteAmount);
    if (byteStrToBytes(firstValue, firstBytes, byteAmount) != RESULT_OK)
        return 1;

    byte *secondBytes = malloc(byteAmount);
    if (byteStrToBytes(secondValue, secondBytes, byteAmount) != RESULT_OK)
        return 1;

    byte *resultBytes = malloc(byteAmount);
    for (uint idx = 0; idx < byteAmount; idx++) {
        *(resultBytes + idx) = *(firstBytes + idx) ^ *(secondBytes + idx);
    }
    
    free(firstBytes);
    free(secondBytes);

    char *resultStr = bytesToByteStr(resultBytes, byteAmount);
    free(resultBytes);

    compareStrings(resultValue, resultStr);

    return 0;
}
