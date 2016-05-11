/*****************************************************************
 *
 *  Copyright (c) 2016 shenxingwuying. All Rights Reserved
 *
 *****************************************************************/


/**
 * @file: WritableFile.h
 * @author: duyuqi(shenxingwuying@gmail.com)
 * @date: 2016-05-10
 * @brief: 
 *
 */

#ifndef ALAYA_WRITABLE_H
#define ALAYA_WRITABLE_H

#include <assert.h>
#include <stdio.h>
#include "Status.h"
#include "Slice.h"
#include <string>

class WritableFile {
    public:
        WritableFile() {}
        virtual ~WritableFile();

        virtual Status Append(const Slice& data) = 0;
        virtual Status Close() = 0;
        virtual Status Flush() = 0;
        virtual Status Sync() = 0;

    private:
        // No copying allowed
        WritableFile(const WritableFile&);
        void operator=(const WritableFile&);
};

class PosixWritableFile : public WritableFile {
    private:
        std::string filename_;
        FILE* file_;
    public:
        PosixWritableFile(std::string filename, FILE* file) : filename_(filename), file_(file) {}
        ~PosixWritableFile() {
            if (file_ != NULL) {
                fclose(file_);
            }
        }

        Status Open() {
        
        }
        Status Create() {
            std::string filename = GetFileName();
            fopen(filename.c_str(), "w+");
        
        }
        Status Append(const Slice& data) {
            size_t r = fwrite(data.data(), 1, data.size(), file_);
            if (r != data.size()) {
                return IOError(filename_, errno);
            }
            return Status::OK();
        }
        Status Close() {
            Status result;
            if (fclose(file_) != 0) {
                result = Status::IOError(filename_, errno);
            }
            file_ = NULL;
            return result;
        }
        Status Flush() {
            if (fflush(file_) != 0) {
                return Status::IOError(filename_, errno);
            }
            return Status::OK();
        }
        Status Sync() {
            if (fsync(fileno(file_)) != 0) {
                return Status::IOError(filename_, errno);
            }
            return Status::OK();
        }
}

#endif

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
