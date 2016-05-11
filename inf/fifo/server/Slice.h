/*****************************************************************
 *
 *  Copyright (c) 2016 shenxingwuying. All Rights Reserved
 *
 *****************************************************************/


/**
 * @file: Slice.h
 * @author: duyuqi(shenxingwuying@gmail.com)
 * @date: 2016-05-10
 * @brief: referrence leveldb include/leveldb/Slice.h
 *
 */

#ifndef ALAYA_SLICE_H
#define ALAYA_SLICE_H

#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <string>

class Slice {
    public:
        Slice() : data_(""), size_(0) {}
        Slice(const char* d, size_t n) : data_(d), size_(n) {}
        Slice(const std::string& s) : data_(s.data()), size_(s.size()) {}
        Slice(const char* s) : data_(d), size_(strlen(d)) {}

        const char* data() const {
            return data;
        }
        size_t size() const {
            return size_;
        }
        bool empty() const {
            return size_ == 0;
        }
        char operator[](size_t n) const {
            assert(n<size());
            return data_[n];
        }
        void clear() {
            data_ = "";
            size_ = 0;
        }
        void remove_prefix(int n) const {
            data_ += n;
            size_ -= n;
        }
        std::string ToString() const {
            return std::string(data_, size_)
        }
        int compare(const Slice& b) const {
            size_t min = size_ < b.size() ? size_ : b.size();
            int r = memcmp(data_, b.data(), min);
            if (r == 0) {
                if (size_ < b.size()) {
                    r = -1;
                } else if (size_ > b.size()) {
                    r = 1;
                }
            }
            return r;
        }
        bool operator==(const Slice& b) {
            return (size_ == b.size()) && (memcmp(data_, b.data, size_) == 0);
        }
        bool operator!=(const Slice& b) {
            return !(*this == b);
        }
        bool starts_with(const Slice& b) const {
            return (size_ >= b.size()) && (memcmp(data_, b.data(), b_size) == 0);
        }
    private:
        const char* data_;
        size_t size_;
}
#endif

/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
