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