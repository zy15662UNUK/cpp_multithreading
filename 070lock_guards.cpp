#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std;

const int ITERATIONS = 1E6;
void work(int &count, mutex &mt)
{
    for (int i = 0; i < ITERATIONS; i++)
    {
        // when entering this for loop scope, lock_guard will try to acquire the mutex. It will release the mutex when exit the scope
        lock_guard<mutex>guard(mt);
        // unique_lock does the same thing with more functionality
        // unique_lock<mutex>guard(mt);
        ++count;
        
    }
}
int main()
{
// using mutex directly is not safe since an exception could make the mutex never unlock
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
