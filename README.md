## 2 streams

```c++
#include <iostream>
#include <string>
#include <memory> 
#include <thread>
#include <chrono>
using namespace std;

void DoWork() {
    for(size_t i = 0; i < 10; i++) {
        cout << "Id stream = " << this_thread::get_id() << "\tDoWork\t" << i << endl;

        this_thread::sleep_for(chrono::milliseconds(1000));
    }
};

int main() {
    thread th(DoWork);

    //th.detach(); Breaks the connection between threads

    for(size_t i = 0; i < 10; i++) {
        cout << "Id stream = " << this_thread::get_id() << "\tMain\t" << i << endl;

        this_thread::sleep_for(chrono::milliseconds(500));
    }


    //Wait the stream. (The base stream will be wait th)
    th.join();

    return 0;
}
```

## Params (Streams)

```c++
#include <iostream>
#include <string>
#include <memory> 
#include <thread>
#include <chrono>
using namespace std;

void DoWork(int a, int b) {
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "-----\t" << "DoWork started\t-----" << endl; 

    this_thread::sleep_for(chrono::milliseconds(2000));

    cout << "a+b = " << a + b << endl;

    this_thread::sleep_for(chrono::milliseconds(1000));

    cout << "-----\t" << "DoWork stoped\t-----" << endl; 
};

int main() {
    thread th(DoWork, 2, 3);

    for(size_t i = 0; true; i++) {
        cout << "Id stream = " << this_thread::get_id() << "\tMain\t" << i << endl;

        this_thread::sleep_for(chrono::milliseconds(500));
    }

    th.join();

    return 0;
}
```

## Ref

```c++
#include <iostream>
#include <string>
#include <memory> 
#include <thread>
#include <chrono>
using namespace std;

void DoWork(int& a) {
    this_thread::sleep_for(chrono::milliseconds(1000));
    cout << "Id stream: " << this_thread::get_id() << " -----\t" << "DoWork started\t-----" << endl; 

    this_thread::sleep_for(chrono::milliseconds(2000));

    a *= 2;

    cout << "Id stream: " << this_thread::get_id() << " -----\t" << "DoWork stoped\t-----" << endl; 
};

int main() {
    int a = 10;

    thread t(DoWork, std::ref(a));

    for(size_t i = 0; i < 10; i++) {
        cout << "Id stream = " << this_thread::get_id() << "\tMain\t" << i << endl;

        this_thread::sleep_for(chrono::milliseconds(500));
    }

    
    t.join();
    cout << a << endl;

    return 0;
}
```