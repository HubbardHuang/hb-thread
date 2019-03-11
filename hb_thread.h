#ifndef HB_THREAD_H
#define HB_THREAD_H

#include <functional>
#include <map>
#include <memory>
#include <pthread.h>
#include <unistd.h>
#include <utility>

namespace hb {

class Thread {
public:
    using id_type = pid_t;
    using attr_type = pthread_attr_t;
    using info_type = pthread_t;
    using function_type = void* (*)(void*);
    // using function_type = std::function<void*(void*)>;
    // template <typename ArgsType>
    // Thread(function_type function, std::shared_ptr<ArgsType>&& args,
    //        std::shared_ptr<attr_type>&& attr) {
    //     // lock
    //     attr_type attr_temp;
    //     pthread_attr_init(&attr_temp);
    //     attr_ = std::make_shared<attr_type>(&attr_temp, pthread_attr_destroy);
    //     pthread_attr_setdetachstate(attr_.get(), PTHREAD_CREATE_JOINABLE);
    //     pthread_create(info_, attr_.get(), function, args.get());
    //     // unlock
    // }
    Thread(function_type function) {
        pthread_attr_init(&attr_);
        pthread_attr_setdetachstate(&attr_, PTHREAD_CREATE_JOINABLE);
        pthread_create(&info_, &attr_, function, nullptr);
    }
    ~Thread();
    void Join();
    void Detach();

private:
    info_type info_;
    attr_type attr_;
    Thread(const Thread&) = delete;
    Thread& operator=(const Thread&) = delete;
};

class Mutex {
public:
    using mutex_type = pthread_mutex_t;
    using attr_type = pthread_mutexattr_t;
    Mutex();
    ~Mutex();
    void Lock();
    void Unlock();

private:
    mutex_type mutex_;
    attr_type attr_;
    Mutex(const Mutex&) = delete;
    Mutex& operator=(const Mutex&) = delete;
    friend class ConVar;
};

class LockGuard {
public:
    LockGuard(Mutex*);
    ~LockGuard();

private:
    Mutex* mutex_;
    LockGuard(const LockGuard&) = delete;
    LockGuard& operator=(const LockGuard&) = delete;
};

class ConVar {
public:
    using con_var_type = pthread_cond_t;
    using attr_type = pthread_condattr_t;
    ConVar();
    ~ConVar();
    void Wait(Mutex*);
    void NotifyOne();
    void NotifyAll();

private:
    con_var_type con_var_;
    attr_type attr_;
    ConVar(const ConVar&) = delete;
    ConVar& operator=(const ConVar&) = delete;
};

}; // namespace hb

#endif