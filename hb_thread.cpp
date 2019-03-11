#include "hb_thread.h"
#include <sys/types.h>

namespace hb {

void
Thread::Join() {
    pthread_join(info_, nullptr);
}

void
Thread::Detach() {
    pthread_attr_setdetachstate(&attr_, PTHREAD_CREATE_DETACHED);
}

Thread::~Thread() {
    pthread_attr_destroy(&attr_);
}

Mutex::Mutex() {
    pthread_mutexattr_init(&attr_);
    // TODO: set attr
    pthread_mutex_init(&mutex_, &attr_);
}

Mutex::~Mutex() {
    pthread_mutex_destroy(&mutex_);
    pthread_mutexattr_destroy(&attr_);
}

void
Mutex::Lock() {
    pthread_mutex_lock(&mutex_);
}

void
Mutex::Unlock() {
    pthread_mutex_unlock(&mutex_);
}

LockGuard::LockGuard(Mutex* target) {
    mutex_ = target;
    mutex_->Lock();
}

LockGuard::~LockGuard() {
    mutex_->Unlock();
}

ConVar::ConVar() {
    pthread_condattr_init(&attr_);
    // TODO: set attr
    pthread_cond_init(&con_var_, &attr_);
}

ConVar::~ConVar() {
    pthread_cond_destroy(&con_var_);
    pthread_condattr_destroy(&attr_);
}

void
ConVar::Wait(Mutex* mutex) {
    pthread_cond_wait(&con_var_, &mutex->mutex_);
}

void
ConVar::NotifyOne() {
    pthread_cond_signal(&con_var_);
}

void
ConVar::NotifyAll() {
    pthread_cond_broadcast(&con_var_);
}

}; // namespace hb