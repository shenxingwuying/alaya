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

class Status {
    public:
        Status() : state_(NULL) {}
        Status(const Status& s) {
            state_ = (s.state_ == NULL ? NULL : CopyState(s.state_));
        }
        Status(Code code, Slice msg, Slice msg2) {
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
            return (state == NULL) ? kOk : static_case<Code>(state_[4]);
        }
}



/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
