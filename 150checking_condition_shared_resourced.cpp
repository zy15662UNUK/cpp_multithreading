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
        cout << "t1 thread acquiring the lock " << endl;
        unique_lock<mutex> lock(mtx);
        cout << "t1 thread acquired the lock" << endl;
        ready = true;
        lock.unlock();
        cout << "t1 thread released the lock notifying" << endl;
        // notify the change
        condition.notify_one();
    });
    
    cout << "main thread acquiring the lock " << endl;
    unique_lock<mutex> lock(mtx);
    cout << "main thread acquired the lock, waiting" << endl;
    // here the while loop is replaced by the lambda expression
    condition.wait(lock, [&](){return ready;});
    cout << "main thread finished waiting" << endl;
    cout << "ready" << endl;
    t.join();
    return 0;
}