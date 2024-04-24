#include<iostream>
#include<thread>
#include<mutex>
#include <sstream>
using namespace std;

// std::unique_lock is more flexible than std::lock_guard.
// Objects of std::unique_lock manage the locking and unlocking operations on the mutex object with exclusive ownership
// (no other unique_lock objects owning the ownership of a mutex object).
// So in concurrent programming, it is recommended to use std::unique_lock.

// std::lock_guard cannot explicitly call lock and unlock, and std::unique_lock can be called anywhere after the declaration.
// It can reduce the scope of the lock and provide higher concurrency.

int v = 1;

void criticalSection(int change_v) {
     std::mutex mtx;
 
    std::unique_lock<std::mutex> lock(mtx);
    lock.lock();
    v = change_v;
    std::stringstream msg;
    msg << endl << "thread: " << std::this_thread::get_id();
    msg << "\tchange_v: " << change_v;
    msg << "\tcriticalSection V = " << v;
    std::cout << msg.str();

    lock.unlock();
    // Other threads can acquire v now !!!
    lock.lock();

    v++;
    std::stringstream msg_1;
    msg_1 << endl << "-- thread: " << std::this_thread::get_id();
    msg_1 << "\tcriticalSection V = " << v;
    std::cout << msg_1.str();
}

int main() {
    std::thread t1(criticalSection, 5);
    std::thread t2(criticalSection, 999);

    t1.join();
    t2.join();

    std::cout << endl << "Main V = " << v;
    return 0;
}