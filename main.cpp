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