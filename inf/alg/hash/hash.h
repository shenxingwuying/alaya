/**
 * @file: hash.h
 * @author: duyuqi(duyuqi@kingsoft.com)
 * @date: 2016-03-30
 * @brief:
 *
 */


#ifndef _HASH_FUNC_H
#define _HASH_FUNC_H

#include <stdint.h>

uint64_t murmurhash64(const void* key, int length, uint64_t h);
uint32_t stringhash(const void* key, int length);

#endif
