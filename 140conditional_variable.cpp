#include <iostream>
#include <cmath>
#include <iomanip>
#include <thread>
#include <future>
#include <chrono>
using namespace std;

// using conditional variable to notify the main thread when the ready is changed
int main()
{
    condition_variable condition;
    mutex mtx;
    bool ready = false;
    thread t([&](){
        this_thread::sleep_for(chrono::milliseconds(2000));
        unique_lock<mutex> lock(mtx);
        ready = true;
        lock.unlock();
        // notify the change
        condition.notify_one();
    });
    
    unique_lock<mutex> lock(mtx);
    while (!ready)
    {
        // lock will be released when wait
        condition.wait(lock);
    }
    cout << "ready" << endl;
    t.join();
    return 0;
}