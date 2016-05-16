/*****************************************************************
 *
 *  Copyright (c) 2016 shenxingwuying. All Rights Reserved
 *
 *****************************************************************/


/**
 * @file: log_format.h
 * @author: duyuqi(shenxingwuying@gmail.com)
 * @date: 2016-05-11
 * @brief: 
 *
 */

#ifndef ALAYA_FIFO_PARAM
#define ALAYA_FIFO_PARAM

#include <stdio.h>
static const int kBlockSize = 32768;
static const int kFileSize = 64 * 1024 * 1024;
static const int kMaxRecord = kFileSize;

struct LogHeader {
    uint64_t sequence;
    uint32_t length;
    uint32_t crc32;
    char type;
};

struct LogEntry {
    struct LogHeader header;
    const char* content;
};




#endif



/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
