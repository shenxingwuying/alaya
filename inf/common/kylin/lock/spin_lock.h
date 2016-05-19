/*****************************************************************
 *
 *  Copyright (c) 2016 shenxingwuying. All Rights Reserved
 *
 *****************************************************************/


/**
 * @file: spin_lock.h
 * @author: duyuqi(shenxingwuying@gmail.com)
 * @date: 2016-04-06
 * @brief: 
 *
 */

#ifndef ALAYA_INF_COMMON_KYLIN_LOCK_H
#define ALAYA_INF_COMMON_KYLIN_LOCK_H

namespace kylin {

    class SpinLock {
        public:
            SpinLock() {
            
            }
            ~SpinLock() {
            
            }

    
    
    
    
        private:
            pthread_spinlock_t lock_;
    }
}

#endif
/* vim: set expandtab ts=4 sw=4 sts=4 tw=100: */
