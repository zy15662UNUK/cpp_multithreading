#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

/*
In this case the result of the count is not 2 million. since the count is copied by the thread, increment and copy back
*/ 
int main()
{
    cout << "hello world" << endl;
    // int count = 0;
    atomic<int> count = 0; // make int atomic,it should now be 2 million
    const int ITERATIONS = 1E6;
    thread t1([&](){
        for (int i = 0; i < ITERATIONS; i ++) {
            ++count;
        }
    });
    thread t2([&]() {
        for (int i = 0; i < ITERATIONS; i++)
        {
            ++count;
        }
    });
    t1.join();
    t2.join();
    cout << count<< endl;
    return 0;
}
