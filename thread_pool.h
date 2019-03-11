#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include "hb_thread.h"
#include <functional>
#include <list>
#include <memory>
#include <vector>

namespace hb {

void TestThreadPool();

class ThreadPool {
public:
    using task_type = void (*)(void);
    ThreadPool(int thread_number);
    void AddTask(task_type task);
    ~ThreadPool();
    void Start();

private:
    static size_t thread_numbers_;
    static std::vector<std::shared_ptr<Thread>> thread_group_;
    static std::list<task_type> task_group_;
    static Mutex stdout_mutex_;
    static Mutex mutex_; // Only one role can operate the task group each time
    static ConVar task_group_is_not_empty_;
    static void* TakeTaskAndPerform(void*);
    // size_t thread_numbers_;
    // std::vector<std::shared_ptr<Thread>> thread_group_;
    // std::list<task_type> task_group_;
    // Mutex mutex_; // Only one role can operate the task group each time
    // ConVar task_group_is_not_empty_;
    // void* TakeTaskAndPerform();
};

}; // namespace hb

#endif