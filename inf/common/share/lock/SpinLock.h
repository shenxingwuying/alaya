#include <pthread.h>

class SpinLock {
    public:
        SpinLock() {
            pthread_spin_init(&spin_, 0);
        }
        ~SpinLock() {
            pthread_spin_destroy(&spin_);
        }
        void Lock() {
            pthread_spin_lock(&spin_);
        }
        bool TryLock() {
            pthread_spin_trylock(&spin_);
        }
        void Unlock() {
            pthread_spin_unlock(&spin_);
        }

    private:
        pthread_spin_t spin_;
}
