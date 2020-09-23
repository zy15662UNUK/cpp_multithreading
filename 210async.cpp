#include <iostream>
#include <cmath>
#include <iomanip>
#include <thread>
#include <future>
#include <chrono>
using namespace std;
int work(int id)
{
    for (int i = 0; i < 5; i ++) {
        cout << "running " << id << endl;
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
    return id * 7;
}

int main()
{
    // if put launch::defer, it would start running when f1.get is called
    // even if we dont have a return value, we still need to use future here, otherwise the funtion would be sync
    future<int> f1 = async(launch::async, work, 0);
    future<int> f2 = async(launch::async, work, 1);
    cout << f1.get() << endl;
    cout << f2.get() << endl;
    return 0;
}