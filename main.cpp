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