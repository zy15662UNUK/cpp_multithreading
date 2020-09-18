#include <iostream>
#include <cmath>
#include <iomanip>
#include <thread>
#include <future>
#include <chrono>
#include <queue>
using namespace std;

template<typename E>
class blocking_queue
{
private:
    mutex mtx;
    condition_variable cond;
    queue<E> q;
    int maxSize;
public:
    blocking_queue(int size):maxSize(size){}
    void push(E elem)
    {
        // we have to lock before we change the shared resourced
        unique_lock<mutex> lock(mtx);
        // if item num reach the maximum, we wait till the consumer consume some 
        cond.wait(lock, [this](){return q.size() < maxSize;});
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


// using conditional variable to notify the main thread when the ready is changed
int main()
{
    blocking_queue<int> bq(2);
    thread t1([&](){
        for (int i = 0; i < 10; i ++)
        {
            bq.push(i);
            cout << "push item " << i << endl;
            cout << "size is " << bq.size() << endl;
        }
    });
    thread t2([&]() {
        for (int i = 0; i < 10; i++)
        {
            auto item = bq.front();
            cout << "consume item " <<  item << endl;
            bq.pop();
        }
    });
    t1.join();
    t2.join();
    return 0;
}