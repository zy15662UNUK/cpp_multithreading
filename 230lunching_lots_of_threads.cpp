#include <iostream>
#include <cmath>
#include <iomanip>
#include <thread>
#include <future>
#include <chrono>
#include <vector>
using namespace std;

mutex mtx;
int work(int id)
{
    unique_lock<mutex>lock(mtx);
    cout << "starting id " << id << endl;
    lock.unlock();
    this_thread::sleep_for(chrono::milliseconds(3000));
    return id *7;
}
int main()
{
    vector<shared_future<int>> futures;
    for (int i = 0; i < thread::hardware_concurrency(); i ++) 
    {
        // future<int> f = async(launch::async, work, i); // inthis way thread is run sync. since future is not work when go out of scope
        // fucture is not copiable, cannot be push to vector, need to use the shared_future
        shared_future<int> f = async(launch::async, work, i);
        futures.push_back(f);
    }
    for (auto f : futures)
    {
        cout << "return " << f.get() <<endl;
    }
    return 0;
}