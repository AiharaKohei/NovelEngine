//
//  Utils.cpp
//  NovelEngine
//
//  Created by 相原昂平 on 2014/11/20.
//
//

#include "Utils.h"

const int Utils::conversionCharBytesFromCharCode(const unsigned char code){
    int charSize;
    if (code < 0x80) {
        charSize = 1;
    } else if (code < 0xE0) {
        charSize = 2;
    } else if (code < 0xF0) {
        charSize = 3;
    } else {
        charSize = 4;
    }
    return charSize;
}