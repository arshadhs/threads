#include<iostream>
#include<thread>
#include<windows.h>

using namespace std;

int main() {
    cout << "\nMain";

    // Lambda
    auto f = [](string str) { cout << "\nHello: " << str; };

    //Launching Thread Using Lambda
    thread t1 (f, "Buddy T1");
    thread t2 (f, "Buddy T2");

    for (int i = 0; i < 5; i++) {
        cout << "\nI am in Main";
        std::this_thread::sleep_for(1000ms);
    }

    t1.join();
    cout << "\nBack in Main T1";
    t2.join();
    cout << "\nBack in Main T2";
}