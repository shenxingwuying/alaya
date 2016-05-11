#include <pthread.h>

class SpinLock {
  public:
    SpinLock();

  private:
    pthread_spin_t spin_;
}
