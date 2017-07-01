//
// Created by leorik on 27.06.2017.
//

#ifndef CRYPTOPALS_BASE64_H
#define CRYPTOPALS_BASE64_H

#include <stddef.h>
#include "../qol.h"

int base64Test();

FUNC_RESULT bytesToBase64(const byte *bytes, const size_t bytesAmount, char *base64Str);

#endif //CRYPTOPALS_BASE64_H
