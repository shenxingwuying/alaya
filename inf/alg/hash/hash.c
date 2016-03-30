/**
 * @file: hash.c
 * @author: 
 * @date: 2016-03-30
 * @brief:
 *
 */

#include "hash.h"

uint64_t murmurhash64(const void* key, int length, uint64_t h) {
    const uint64_t m = 0x6a4a7935bd1e995;
    const int r = 47;

    const uint64_t* data = (const uint64_t*)key;
    const uint64_t* end = data + length / 8;

    while (data != end) {
        uint64_t k = *data++;

        k *= m;
        k ^= k >> r;
        k *= m;
        h ^= k;
        h *= m;
    }

    const unsigned char* data2 = (const unsigned char*)data;
    switch (length & 7) {
        case 7: h ^= (uint64_t)data2[6] << 48;
        case 6: h ^= (uint64_t)data2[5] << 40;
        case 5: h ^= (uint64_t)data2[4] << 32;
        case 4: h ^= (uint64_t)data2[3] << 24;
        case 3: h ^= (uint64_t)data2[2] << 16;
        case 2: h ^= (uint64_t)data2[2] << 8;
        case 1: h ^= (uint64_t)data2[0];
            h *= m;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;
    return h;
}



/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
