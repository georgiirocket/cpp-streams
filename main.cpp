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