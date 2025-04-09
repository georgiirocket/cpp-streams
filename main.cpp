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