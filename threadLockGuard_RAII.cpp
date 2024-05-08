#include<iostream>
#include<thread>
#include<mutex>
#include <sstream>
using namespace std;

//  C++11 also provides a template class std::lock_guard for the RAII syntax for the mutex

 // C++ guarantees that all stack objects will be destroyed at the end of the declaration period,
 // such code is also extremely safe. Whether critical_section() returns normally or
 // if an exception is thrown in the middle, a stack rollback is thrown, and unlock() is automatically called.

// std::lock_guard cannot explicitly call lock and unlock

int v = 1;

void criticalSection(int change_v) {
    std::mutex mtx;

    std::lock_guard<std::mutex> lock(mtx);

    v = change_v;
    std::stringstream msg;
    msg << endl << "thread: " << std::this_thread::get_id();
    msg << "\tchange_v: " << change_v;
    msg << "\tcriticalSection V = " << v;
    std::cout << msg.str();
}

int main() {
    std::thread t1(criticalSection, 5);
    std::thread t2(criticalSection, 9);

    t1.join();
    t2.join();

    std::cout << endl << "Main V = " << v;
    return 0;
}