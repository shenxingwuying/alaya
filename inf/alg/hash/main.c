/*****************************************************************
 *
 *  Copyright (c) 2016 KingSoft.com, Inc. All Rights Reserved
 *
 *****************************************************************/


/**
 * @file: main.c
 * @author: duyuqi(duyuqi@kingsoft.com)
 * @date: 2016-03-30
 * @brief:
 *
 */
#include <stdio.h>
#include "hash.h"
#include <string.h>

int main() {
    char a[64] = "hello.list";
    uint64_t hash;
    hash = murmurhash64(a, strlen(a), 0x00000000);
    printf("%lu\n", hash);
    hash = murmurhash64("hello", 5, 0x00000000);
    printf("%lu\n", hash);
    hash = murmurhash64("hello1", 6, 0x00000000);
    printf("%lu\n", hash);
    hash = murmurhash64("hello2", 6, 0x00000000);
    printf("%lu\n", hash);
    hash = murmurhash64("hello20", 7, 0x00000000);
    printf("%lu\n", hash);

    return 0;
}



/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
