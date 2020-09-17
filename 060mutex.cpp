#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std;

/*
In this case the result of the count is not 2 million. since the count is copied by the thread, increment and copy back
*/ 
int main()
{
    int count = 0;
    const int ITERATIONS = 1E6;
    mutex mt;
    auto func = [&]() {
        for (int i = 0; i < ITERATIONS; i++)
        {
            mt.lock();
            ++count;
            mt.unlock();
        }
    };
    thread t1(func);
    thread t2(func);
    t1.join();
    t2.join();
    cout << count<< endl;
    return 0;
}
