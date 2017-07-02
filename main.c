
#include <mem.h>
#include <malloc.h>
#include "set1/base64.h"
#include "common.h"

int main() {
    char* str = "1c0111001f010100061a024b53535009181c";
    size_t bytesAmount = strlen(str) / 2;

    byte* bytes = malloc(bytesAmount);
    byteStrToBytes(str, bytes, bytesAmount);

    char* str2 = bytesToByteStr(bytes, bytesAmount);

    compareStrings(str, str2);

    return 0;
}

