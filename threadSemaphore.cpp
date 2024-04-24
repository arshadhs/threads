#include<iostream>
#include<thread>
#include<windows.h>
#include<mutex>
#include<semaphore.h>
using namespace std;

int GVAR = 0;
std::mutex myLock;
std::binary_semaphore
    smphSignalMainToThread{0},
    smphSignalThreadToMain{0};

int myThreadApi(string str) {

    static int sVar = 0;
    for (int i = 0; i < 10; i++) {
        myLock.lock();
        GVAR++;
        sVar++;
        cout << "\nHello: " << str << " GVAR: " << GVAR << " sVar: " << sVar;
        myLock.unlock();
        std::this_thread::sleep_for(1000ms);
        //Sleep(1);
    }
    return 0;
}

int main() {
    cout << "\nMain";

    //Launching Thread Using Function Pointer
    thread t1 (myThreadApi, "Buddy T1");


    thread t2 (myThreadApi, "Buddy T2");
    for (int i = 0; i < 10; i++) {
        cout << "\nI am in Main";
        std::this_thread::sleep_for(1000ms);
      //  Sleep(1);
    }
    t1.join();
    cout << "\nBack in Main T1";
    t2.join();
    cout << "\nBack in Main T2";
}