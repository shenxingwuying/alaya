#include <pthread.h>

class MutexLock {
public:
    MutexLock() {
        pthread_mutex_init(&mutex_, NULL);
    }
    ~/MutexLock() {
        pthread_mutex_destory(&mutex_);
    }
    Lock() {
        pthread_mutex_lock(&mutex_);
    }
    TryLock() {
        pthread_mutex_trylock(&mutex_);
    }
    UnLock() {
        pthread_mutex_unlock(&mutex_);
    }

private:
    pthread_mutex_t mutex_;
}
