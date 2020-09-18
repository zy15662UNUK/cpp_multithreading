#include <iostream>
#include <cmath>
#include <iomanip>
#include <thread>
#include <future>
#include <chrono>
using namespace std;

int main()
{
    atomic<bool> ready = false;
    thread t([&](){
        this_thread::sleep_for(chrono::milliseconds(2000));
        ready = true;
    });
    t.join();
    while (!ready)
    {
        this_thread::sleep_for(chrono::milliseconds(2000));
    }
    cout << "ready" << endl;
    return 0;
}