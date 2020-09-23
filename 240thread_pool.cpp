#include <iostream>
#include <cmath>
#include <iomanip>
#include <thread>
#include <future>
#include <chrono>
#include <vector>
#include <queue>
using namespace std;

mutex mtx;

template <typename E>
class blocking_queue
{
private:
    mutex mtx;
    condition_variable cond;
    queue<E> q;
    int maxSize;

public:
    blocking_queue(int size) : maxSize(size) {}
    void push(E elem)
    {
        // we have to lock before we change the shared resourced
        unique_lock<mutex> lock(mtx);
        // if item num reach the maximum, we wait till the consumer consume some
        cond.wait(lock, [this]() { return q.size() < maxSize; });
        q.push(elem);
        lock.unlock();
        cond.notify_one();
    }
    void pop()
    {
        unique_lock<mutex> lock(mtx);
        // same, consumer need to wait before producer make more items
        cond.wait(lock, [this]() { return q.size() > 0; });
        q.pop();
        lock.unlock();
        cond.notify_one();
    }
    E front()
    {
        unique_lock<mutex> lock(mtx);
        cond.wait(lock, [this]() { return q.size() > 0; });
        return q.front();
    }

    int size()
    {
        unique_lock<mutex> lock(mtx);
        return q.size();
    }
};

int work(int id)
{
    unique_lock<mutex>lock(mtx);
    cout << "starting id " << id << endl;
    lock.unlock();
    int second = int((rand() *5)/RAND_MAX + 3);
    this_thread::sleep_for(chrono::seconds(second));
    return id;
}
int main()
{
    blocking_queue<shared_future<int>> futures(2);
    thread t([&]() {
        for (int i = 0; i < 20; i++)
        {
            /*
            3 threads running at any given time. since only 2 is allowed to push into the queue, when the 
            third one is created and run, this thread will be send to CV and won't push
            */ 
            shared_future<int> f = async(launch::async, work, i);
            futures.push(f);
        }
    });
    for (int i = 0; i < 20; i++)
    {
        shared_future<int> f = futures.front();
        int val = f.get();
        futures.pop(); // pop the thread when finish
        cout << "returned " << val << endl;
    }
    // need main thread to wait all these finish
    t.join();
    return 0;
}