#include <iostream>
#include <mutex>
#include <thread>
#include <chrono>
using namespace std;

mutex mtx;

void AddName(string name, vector<string>& storage)
{
    unique_lock<mutex> ul(mtx, std::defer_lock);

    this_thread::sleep_for(chrono::milliseconds(2000));

    ul.lock();

    storage.push_back(name);

    ul.unlock();

    this_thread::sleep_for(chrono::milliseconds(2000));
}

int main() {
    vector<string> names;

    thread t(AddName, "Piter", std::ref(names));
    thread t1(AddName, "Patrik", std::ref(names));
    thread t2(AddName, "Stuart", std::ref(names));

    t.join();
    t1.join();
    t2.join();

    for(string name : names)
    {
        cout << "Name: " << name << endl;
    }


    return 0;
}