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

## Lamda fn, return result

```c++
#include <iostream>
#include <string>
#include <memory> 
#include <thread>
#include <chrono>
using namespace std;

int Sum(int a, int b) {
    this_thread::sleep_for(chrono::milliseconds(2000));
    cout << "Id stream: " << this_thread::get_id() << " -----\t" << "DoWork started\t-----" << endl; 

    this_thread::sleep_for(chrono::milliseconds(5000));

    cout << "Id stream: " << this_thread::get_id() << " -----\t" << "DoWork stoped\t-----" << endl; 
    
    return a + b;
};

int main() {

    int result;
    thread t([&result]() {
        result = Sum(5,2);
    });


    for(size_t i = 0; i < 10; i++) {
        cout << "Id stream = " << this_thread::get_id() << "\tMain\t" << i << endl;

        this_thread::sleep_for(chrono::milliseconds(500));
    }

    t.join();
    cout << "Result: " << result << endl;

    return 0;
}
```

## Methods of class in streams

```c++
#include <iostream>
#include <string>
#include <memory> 
#include <thread>
#include <chrono>
using namespace std;


class MyClass {
    public:
        void DoWork() {
            this_thread::sleep_for(chrono::milliseconds(2000));
            cout << "Id stream: " << this_thread::get_id() << " -----\t" << "DoWork started\t-----" << endl; 

            this_thread::sleep_for(chrono::milliseconds(5000));
            cout << "Id stream: " << this_thread::get_id() << " -----\t" << "DoWork stoped\t-----" << endl; 
        }

        void DoWork2(int a) {
            this_thread::sleep_for(chrono::milliseconds(2000));
            cout << "Id stream: " << this_thread::get_id() << " -----\t" << "DoWork 2 started\t-----" << endl; 

            this_thread::sleep_for(chrono::milliseconds(5000));
            cout << "DoWork 2 value:\t" << a << endl;

            cout << "Id stream: " << this_thread::get_id() << " -----\t" << "DoWork 2 stoped\t-----" << endl; 
        }

        int Sum(int a, int b) {
            this_thread::sleep_for(chrono::milliseconds(2000));
            cout << "Id stream: " << this_thread::get_id() << " -----\t" << "Sum started\t-----" << endl; 

            this_thread::sleep_for(chrono::milliseconds(5000));

            cout << "Id stream: " << this_thread::get_id() << " -----\t" << "Sum stoped\t-----" << endl; 
    
            return a + b;
        }
};

int main() {
    int result;
    MyClass m;

    thread t(&MyClass::DoWork, m);

    thread t1(&MyClass::DoWork2, m, 10);

    thread t2([&result, &m]() {
        result = m.Sum(2, 5);
    });


    for(size_t i = 1; i <= 10; i++) {
        cout << "Id stream = " << this_thread::get_id() << "\tMain\t" << i << endl;

        this_thread::sleep_for(chrono::milliseconds(500));
    }

    t.join();
    t1.join();
    t2.join();

    cout << "Result\t" << result << endl;

    return 0;
}
```

## Mutex, sync streams

```c++
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
using namespace std;

mutex mtx;

void print(char ch) 
{
    this_thread::sleep_for(chrono::milliseconds(2000));

    mtx.lock();

    for(int i = 0; i < 5; i++) 
    {
        for(int j = 0; j < 10; j++) 
        {
            cout << ch;

            this_thread::sleep_for(chrono::milliseconds(20));
        }

        cout << endl;
    }

    mtx.unlock();

    this_thread::sleep_for(chrono::milliseconds(2000));
}


int main() {
    thread t1(print, '-');
    thread t2(print, '*');

    t1.join();
    t2.join();

    return 0;
}
```

## Lock guard

```c++
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
using namespace std;

mutex mtx;

void print(char ch) 
{
    this_thread::sleep_for(chrono::milliseconds(2000));

    //Scope lock_guard
    {
        lock_guard<mutex> guard(mtx); // = mutex.lock()

        for(int i = 0; i < 5; i++) 
        {
            for(int j = 0; j < 10; j++) 
            {
                cout << ch;

                this_thread::sleep_for(chrono::milliseconds(20));
            }

            cout << endl;
        }
    }

    this_thread::sleep_for(chrono::milliseconds(2000));
}


int main() {
    thread t1(print, '-');
    thread t2(print, '*');

    t1.join();
    t2.join();

    return 0;
}
```

## Deadlock

```c++
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
using namespace std;

mutex mtx1;
mutex mtx2;

void print() 
{

    mtx2.lock();

    this_thread::sleep_for(chrono::milliseconds(1));

    mtx1.lock();

    for(int i = 0; i < 5; i++) 
    {
        for(int j = 0; j < 10; j++) 
        {
            cout << '*';
            this_thread::sleep_for(chrono::milliseconds(10));
        }

        cout << endl;
    }

    cout << endl;

    mtx1.unlock();
    mtx2.unlock();
}

void print2() 
{

    mtx1.lock();

    this_thread::sleep_for(chrono::milliseconds(1));

    mtx2.lock();

    for(int i = 0; i < 5; i++) 
    {
        for(int j = 0; j < 10; j++) 
        {
            cout << '#';
            this_thread::sleep_for(chrono::milliseconds(10));
        }

        cout << endl;
    }

    cout << endl;

    mtx1.unlock();
    mtx2.unlock();
}


int main() {
    thread t1(print);
    thread t2(print2);

    t1.join();
    t2.join();

    return 0;
}
```

## Recursive mutex

```c++
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
using namespace std;

recursive_mutex rm;

void Foo(int a) 
{
    rm.lock();
    cout << a << " ";

    this_thread::sleep_for(chrono::milliseconds(300));

    if(a <= 1)
    {
        cout << endl;
        rm.unlock();

        return;
    }

    a--;

    Foo(a);
    rm.unlock();
}

int main() {
    thread t1(Foo, 10);
    thread t2(Foo, 10);

    t1.join();
    t2.join();

    return 0;
}
```

## Unique Lock

```c++
#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
using namespace std;

mutex mtx;

void print(char ch)
{
    unique_lock<mutex> ul(mtx, std::defer_lock);

    this_thread::sleep_for(chrono::milliseconds(2000));

    ul.lock();
    for(int i = 0; i < 5; i++) 
    {
        for (size_t j = 0; j < 10; j++)
        {
            cout << ch;

            this_thread::sleep_for(chrono::milliseconds(10));
        }
        cout << endl;
    }

    cout << endl;

    ul.unlock();

    this_thread::sleep_for(chrono::milliseconds(2000));
}

int main() {
    thread t(print, '*');
    thread t1(print, '#');

    t.join();
    t1.join();

    return 0;
}
```