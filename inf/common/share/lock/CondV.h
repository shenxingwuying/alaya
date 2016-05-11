#include <pthread.h>

class CondV {
    public:
        CondV() {
            pthread_cond_init(&cond_, NULL);
        }
        ~CondV() {
            pthread_cond_destory(&cond_);
        }
        void Wait(MutexLock& mutex) {
            pthread_cond_wait(&cond_, &(mutex.lock_));
        }
        void Wait(MutexLock& mutex, int timeout) {
            pthread_cond_timedwait(&cond_, &(mutex.lock_), timeout);
        }
        void Signal() {
            pthread_cond_signal(&cond_);
        }
        void SignalAll() {
            pthread_cond_broadcase(&cond_);
        }
    private:
        pthread_cond_t cond_;
}
