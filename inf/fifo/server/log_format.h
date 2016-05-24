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

struct LogHeader {
    uint64_t sequence;
    // uint64_t timestamp;
    uint16_t length;
    uint16_t type;
    uint32_t crc32;
};

struct LogEntry {
    struct LogHeader header;
    const char* content;
};

enum RecordType {
    kZeroType = 0,
    kFullType,
    kFirstType,
    kMiddleType,
    kLastType
};

static const int kBlockSize = 32768;
static const int kMaxRecodeType = kLastType;
static const int kFileSize = 64 * 1024 * 1024;
static const int kMaxRecordSize = kFileSize;
static const int kHeaderSize = sizeof(struct LogHeader);

#endif



/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
