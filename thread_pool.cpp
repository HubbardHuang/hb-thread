#include <iostream>

#include "thread_pool.h"

namespace hb {

size_t ThreadPool::thread_numbers_ = 0;
std::vector<std::shared_ptr<Thread>> ThreadPool::thread_group_;
std::list<ThreadPool::task_type> ThreadPool::task_group_;
Mutex ThreadPool::stdout_mutex_;
Mutex ThreadPool::mutex_;
ConVar ThreadPool::task_group_is_not_empty_;

void
TestThreadPool() {
    ThreadPool tp(4);
    std::vector<ThreadPool::task_type> task_group;
    ThreadPool::task_type task1 = []() {
        std::cout << "Thread " << pthread_self() << ": ";
        std::cout << "task 1	." << std::endl;
    };
    task_group.push_back(task1);
    ThreadPool::task_type task2 = []() {
        std::cout << "Thread " << pthread_self() << ": ";
        std::cout << "task 2	." << std::endl;
    };
    task_group.push_back(task2);
    ThreadPool::task_type task3 = []() {
        std::cout << "Thread " << pthread_self() << ": ";
        std::cout << "task 3	." << std::endl;
    };
    task_group.push_back(task3);
    ThreadPool::task_type task4 = []() {
        std::cout << "Thread " << pthread_self() << ": ";
        std::cout << "task 4	." << std::endl;
    };
    task_group.push_back(task4);
    ThreadPool::task_type task5 = []() {
        std::cout << "Thread " << pthread_self() << ": ";
        std::cout << "task 5	." << std::endl;
    };
    task_group.push_back(task5);
    ThreadPool::task_type task6 = []() {
        std::cout << "Thread " << pthread_self() << ": ";
        std::cout << "task 6	." << std::endl;
    };
    task_group.push_back(task6);
    ThreadPool::task_type task7 = []() {
        std::cout << "Thread " << pthread_self() << ": ";
        std::cout << "task 7	." << std::endl;
    };
    task_group.push_back(task7);
    ThreadPool::task_type task8 = []() {
        std::cout << "Thread " << pthread_self() << ": ";
        std::cout << "task 8	." << std::endl;
    };
    task_group.push_back(task8);
    ThreadPool::task_type task9 = []() {
        std::cout << "Thread " << pthread_self() << ": ";
        std::cout << "task 9	." << std::endl;
    };
    task_group.push_back(task9);
    ThreadPool::task_type task10 = []() {
        std::cout << "Thread " << pthread_self() << ": ";
        std::cout << "task 10	." << std::endl;
    };
    task_group.push_back(task10);
    ThreadPool::task_type task11 = []() {
        std::cout << "Thread " << pthread_self() << ": ";
        std::cout << "task 11	." << std::endl;
    };
    task_group.push_back(task11);
    ThreadPool::task_type task12 = []() {
        std::cout << "Thread " << pthread_self() << ": ";
        std::cout << "task 12	." << std::endl;
    };
    task_group.push_back(task12);
    ThreadPool::task_type task13 = []() {
        std::cout << "Thread " << pthread_self() << ": ";
        std::cout << "task 13	." << std::endl;
    };
    task_group.push_back(task13);
    ThreadPool::task_type task14 = []() {
        std::cout << "Thread " << pthread_self() << ": ";
        std::cout << "task 14	." << std::endl;
    };
    task_group.push_back(task14);
    ThreadPool::task_type task15 = []() {
        std::cout << "Thread " << pthread_self() << ": ";
        std::cout << "task 15	." << std::endl;
    };
    task_group.push_back(task15);
    ThreadPool::task_type task16 = []() {
        std::cout << "Thread " << pthread_self() << ": ";
        std::cout << "task 16	." << std::endl;
    };
    task_group.push_back(task16);
    ThreadPool::task_type task17 = []() {
        std::cout << "Thread " << pthread_self() << ": ";
        std::cout << "task 17	." << std::endl;
    };
    task_group.push_back(task17);
    ThreadPool::task_type task18 = []() {
        std::cout << "Thread " << pthread_self() << ": ";
        std::cout << "task 18	." << std::endl;
    };
    task_group.push_back(task18);
    ThreadPool::task_type task19 = []() {
        std::cout << "Thread " << pthread_self() << ": ";
        std::cout << "task 19	." << std::endl;
    };
    task_group.push_back(task19);
    ThreadPool::task_type task20 = []() {
        std::cout << "Thread " << pthread_self() << ": ";
        std::cout << "task 20	." << std::endl;
    };
    task_group.push_back(task20);
    ThreadPool::task_type task21 = []() {
        std::cout << "Thread " << pthread_self() << ": ";
        std::cout << "task 21	." << std::endl;
    };
    task_group.push_back(task21);

    for (auto task : task_group) {
        tp.AddTask(task);
    }
}

ThreadPool::ThreadPool(int thread_number) {
    thread_numbers_ = thread_number;
    // // if adding "this" into the "[]" of lambda, type error happened.
    // same_operation_ = [](void* arg) -> void* {
    //     while (true) {
    //         // LockGuard lock(&mutex_);
    //         // take a task away from the task group
    //         // perform the gotten task
    //     }
    //     return (void*)0;
    // };
    Start();
}

ThreadPool::~ThreadPool() {
    for (auto thread : thread_group_) {
        thread->Join();
    }
}

void
ThreadPool::Start() {
    for (int i = 0; i < thread_numbers_; i++) {
        Thread::function_type current_task = TakeTaskAndPerform;
        thread_group_.push_back(std::make_shared<Thread>(current_task));
    }
}

void
ThreadPool::AddTask(task_type task) {
    LockGuard lock(&mutex_);
    task_group_.push_back(task);
    task_group_is_not_empty_.NotifyAll();
}

void*
ThreadPool::TakeTaskAndPerform(void* arg) {
    while (true) {
        task_type new_task;
        {
            LockGuard lock(&mutex_);
            while (task_group_.empty()) {
                std::cout << "waiting..." << std::endl;
                task_group_is_not_empty_.Wait(&mutex_);
            }
            // take a task away from the task group
            new_task = task_group_.front();
            task_group_.pop_front();
        }
        // perform the gotten task
        LockGuard lock(&stdout_mutex_);
        new_task();
    }
    return (void*)0;
}

} // namespace hb