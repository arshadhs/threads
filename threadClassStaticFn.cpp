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

    int myFunc(string str) {
      s = str;
      static int sVar = 0;
      for (int i = 0; i < 10; i++) {
          GVAR++;
          sVar++;
          cout << "Hello: " << s << " GVAR: " << GVAR << " sVar: " << sVar << std::endl << std::flush;;
          std::this_thread::sleep_for(1000ms);
      }
      return 0;
    }
};

int myClass::sVar = 0;

int main() {
    cout << "\nMain";
    
    myClass myObj("My String");
    myClass myObj2("My String");

    // Launching Thread Using Non-Static Member Function
    thread t1 (&myClass::myFunc, &myObj, "Buddy T1");
    thread t2 (&myClass::myFunc, &myObj2, "Buddy T2");

    for (int i = 0; i < 10; i++) {
        cout << "I am in Main" << std::endl ;
        std::this_thread::sleep_for(1000ms);
    }

    t1.join();
    cout << "\nBack in Main T1";
    t2.join();
    cout << "\nBack in Main T2";
}