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