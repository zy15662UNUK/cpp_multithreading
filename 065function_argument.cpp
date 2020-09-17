#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std;

const int ITERATIONS = 1E6;
void work(int & count, mutex &mt)
{
    for (int i = 0; i < ITERATIONS; i++)
    {
        mt.lock();
        ++count;
        mt.unlock();
    }
}
int main()
{

    mutex mt;
    int count = 0;
    // must use ref here inorder to pass a ref
    thread t1(work, ref(count), ref(mt));
    thread t2(work, ref(count), ref(mt));
    t1.join();
    t2.join();
    cout << count << endl;
    return 0;
}
