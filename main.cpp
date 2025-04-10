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