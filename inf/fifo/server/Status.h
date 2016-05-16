/*****************************************************************
 *
 *  Copyright (c) 2016 shenxingwuying. All Rights Reserved
 *
 *****************************************************************/


/**
 * @file: Status.h
 * @author: duyuqi(shenxingwuying@gmail.com)
 * @date: 2016-05-10
 * @brief: 
 *
 */

#include <errno.h>

class Status {
    public:
        Status() : state_(NULL) {}
        Status(const Status& s) {
            state_ = (s.state_ == NULL ? NULL : CopyState(s.state_));
        }
        Status(Code code, Slice msg, Slice msg2) {
            uint32_t len1 = msg.size();
            uint32_t len2 = msg2.size();
            uint32_t size = len1 + (len2 ? len2 + 2 : 0);
            state_ = new char[5+size];

            memcpy(state_, &size, sizeof(uint32_t));
            state_[4] = static_cast<char>(code);
            memcpy(state_+5, msg.data(), len1);
            if (len2) {
                state_[len1+5] = ':';
                state_[len1+6] = ' ';
                memcpy(state_+len1+7, msg2.data(), len2);
            }
        }
        ~Status() {
            if (state_ != NULL) {
                delete[] state_;
            }
        }
        static const char* CopyState(const char* s) {
            uint32_t size;
            memcpy(&size, s, sizeof(uint32_t));
            char* result = new char[size+5];
            memcpy(result, s, size+5);
            return result;
        }
        static Status OK() {
            return Status();
        }
        static Status IOError(const std::string& msg, int errcode) const {
            return Status::IOError(msg, strerror(errcode));
        }
        static Status IOError(const Slice& msg, const Slice& msg2 = Slice()) {
            return Status(kIOError, msg, msg2);
        }

    private:
          // OK status has a NULL state_.  Otherwise, state_ is a new[] array
          // of the following form:
          //    state_[0..3] == length of message
          //    state_[4]    == code
          //    state_[5..]  == message
        const char* state_;
        enum Code {
            kOk,
            kNotFound,
            kCorruption,
            kNotSupport,
            kInvaildArgument,
            kIOError
        }
        Code code() {
            return (state == NULL) ? kOk : static_cast<Code>(state_[4]);
        }
};



/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
