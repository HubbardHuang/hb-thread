#include "hb_thread.h"
#include "thread_pool.h"
#include <iostream>

int i = 0;
const int MAX = 100;
hb::Mutex mutex;

int
main(void) {
    // hb::Thread t1([](auto* args) -> auto {
    //     while (true) {
    //         hb::LockGuard lock(&mutex);
    //         if (i < MAX)
    //             std::cout << "thread 1: i = " << i++ << std::endl;
    //         else
    //             break;
    //     }
    //     return (void*)0;
    // });

    // hb::Thread t2([](auto* args) -> auto {
    //     while (true) {
    //         hb::LockGuard lock(&mutex);
    //         if (i < MAX)
    //             std::cout << "thread 2: i = " << i++ << std::endl;
    //         else
    //             break;
    //     }
    //     return (void*)0;
    // });

    // hb::Thread t3([](auto* args) -> auto {
    //     while (true) {
    //         hb::LockGuard lock(&mutex);
    //         if (i < MAX)
    //             std::cout << "thread 3: i = " << i++ << std::endl;
    //         else
    //             break;
    //     }
    //     return (void*)0;
    // });

    // t1.Join();
    // t2.Join();
    // t3.Join();
    hb::TestThreadPool();
    std::cout << "return to main()." << std::endl;
    return 0;
}