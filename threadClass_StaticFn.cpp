#include<iostream>
#include<thread>
#include<windows.h>

using namespace std;

int GVAR = 0;

class myClass {
  string s;
  static int sVar;
  public:
    myClass(string x) : s(x) {}

    static int myFunc(string str) {
      static int sVar = 0;
      for (int i = 0; i < 10; i++) {
          GVAR++;
          sVar++;
          cout << "Hello: " << str << " GVAR: " << GVAR << " sVar: " << sVar << std::endl << std::flush;;
          std::this_thread::sleep_for(1000ms);
      }
      return 0;
    }
};

int myClass::sVar = 0;

int main() {
    cout << "\nMain";
    

    // Launching Thread Using Static Member Function

    // Note that the Object is not needed now !
    thread t1 (&myClass::myFunc, "Buddy T1");
    thread t2 (&myClass::myFunc, "Buddy T2");

    for (int i = 0; i < 10; i++) {
        cout << "I am in Main" << std::endl ;
        std::this_thread::sleep_for(1000ms);
    }

    t1.join();
    cout << "\nBack in Main T1";
    t2.join();
    cout << "\nBack in Main T2";
}