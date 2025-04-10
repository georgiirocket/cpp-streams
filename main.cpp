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